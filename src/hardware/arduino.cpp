// Bunny UNO R3: version 3, raw GPIO over a 2 Mbaud UART.
#include "lapin.h"
#include <cerrno>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <poll.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

// One connection is used by one thread at a time.
struct ArduinoConnection
{
  int fd;
  uint16_t outputs;
  uint16_t pwm;
  int pwm_duty[14];
  uint8_t queue[4096];
  size_t begin;
  size_t end;
  uint16_t submitted;
};

static void encode(uint8_t *p, uint8_t command, uint8_t a, uint8_t b, uint8_t c)
{
  p[0] = 0xa5; p[1] = command; p[2] = a;
  p[3] = b; p[4] = c;
  p[5] = 0;
  for (unsigned i = 0; i < 5; ++i) p[5] ^= p[i];
}

static int ready(int fd, short events, int milliseconds)
{
  struct pollfd pfd = {fd, events, 0};
  int ret;
  do { ret = poll(&pfd, 1, milliseconds); }
  while (ret < 0 && errno == EINTR);
  if (ret == 0) { errno = ETIMEDOUT; return -1; }
  if (ret < 0) return -1;
  if (pfd.revents & (POLLHUP | POLLERR | POLLNVAL))
    { errno = EIO; return -1; }
  return (pfd.revents & events) ? 0 : (errno = EIO, -1);
}

static bool pump(ArduinoConnection *conn)
{
  while (conn->begin < conn->end)
    {
      ssize_t n = ::write(conn->fd, conn->queue + conn->begin,
                          conn->end - conn->begin);
      if (n > 0) { conn->begin += (size_t)n; continue; }
      if (n < 0 && errno == EINTR) continue;
      if (n < 0 && (errno == EAGAIN || errno == EWOULDBLOCK))
        return true;
      if (n == 0) errno = EIO;
      return false;
    }
  conn->begin = conn->end = 0;
  return true;
}

static bool enqueue_bytes(ArduinoConnection *conn, const uint8_t *data,
                          size_t size)
{
  if (!pump(conn)) return false;
  if (sizeof(conn->queue) - conn->end < size && conn->begin)
    {
      memmove(conn->queue, conn->queue + conn->begin,
              conn->end - conn->begin);
      conn->end -= conn->begin;
      conn->begin = 0;
    }
  if (sizeof(conn->queue) - conn->end < size)
    { errno = EAGAIN; return false; }
  memcpy(conn->queue + conn->end, data, size);
  conn->end += size;
  return pump(conn);
}

static bool enqueue(ArduinoConnection *conn, const uint8_t *frame)
{
  return enqueue_bytes(conn, frame, 6);
}

static bool drain(ArduinoConnection *conn)
{
  while (conn->begin < conn->end)
    {
      if (!pump(conn)) return false;
      if (conn->begin < conn->end && ready(conn->fd, POLLOUT, 1000) < 0)
        return false;
    }
  return true;
}

static bool receive(ArduinoConnection *conn, uint8_t *reply, size_t length,
                    uint8_t command)
{
  size_t pos = 0;
  while (pos < length)
    {
      if (ready(conn->fd, POLLIN, 1000) < 0) return false;
      ssize_t n = ::read(conn->fd, reply + pos, length - pos);
      if (n < 0 && errno == EINTR) continue;
      if (n < 0 && (errno == EAGAIN || errno == EWOULDBLOCK)) continue;
      if (n <= 0) { errno = EIO; return false; }
      pos += (size_t)n;
    }
  uint8_t check = 0;
  for (size_t i = 0; i < length; ++i) check ^= reply[i];
  if (check || reply[0] != 0x5a || reply[1] != command || reply[2] != 0)
    { errno = EPROTO; return false; }
  return true;
}

static bool request(ArduinoConnection *conn, uint8_t command,
                    uint8_t a, uint8_t b, uint8_t c, uint16_t *value)
{
  uint8_t frame[6], reply[6];
  encode(frame, command, a, b, c);
  if (!enqueue(conn, frame) || !drain(conn) ||
      !receive(conn, reply, sizeof(reply), command)) return false;
  if (value) *value = (uint16_t)reply[3] | ((uint16_t)reply[4] << 8);
  return true;
}

// Barrier: confirms that every write submitted before this call has executed.
static bool barrier(ArduinoConnection *conn)
{
  uint16_t executed;
  if (!request(conn, 10, 0, 0, 0, &executed)) return false;
  if (executed != conn->submitted) { errno = EPROTO; return false; }
  return true;
}

static uint16_t digital_outputs(const t_bunny_arduino *board,
                                const ArduinoConnection *conn)
{
  uint16_t value = 0;
  for (unsigned i = 2; i < 14; ++i)
    if ((conn->outputs & (1u << i)) && !(conn->pwm & (1u << i)) &&
        board->digital_outputs[i]) value |= (uint16_t)(1u << i);
  return value;
}

static void store_snapshot(t_bunny_arduino *board, const uint8_t *reply)
{
  uint16_t digital = (uint16_t)reply[5] | ((uint16_t)reply[6] << 8);
  for (unsigned i = 2; i < 14; ++i)
    board->digital_inputs[i] = !!(digital & (1u << i));
  for (unsigned i = 0; i < 6; ++i)
    {
      uint16_t v = (uint16_t)reply[7 + i * 2] |
                   ((uint16_t)reply[8 + i * 2] << 8);
      board->analog_inputs[i] = v / 1023.0;
    }
}

// The snapshot is ordered after all previous writes and acknowledges them.
static bool snapshot(t_bunny_arduino *board, bool with_write)
{
  ArduinoConnection *conn = (ArduinoConnection*)board->_private;
  uint8_t frame[6], reply[20];
  uint16_t outputs = digital_outputs(board, conn);
  encode(frame, 8, (uint8_t)outputs, (uint8_t)(outputs >> 8), with_write);
  if (!enqueue(conn, frame) || !drain(conn) ||
      !receive(conn, reply, sizeof(reply), 8)) return false;
  uint16_t executed = (uint16_t)reply[3] | ((uint16_t)reply[4] << 8);
  if (executed != conn->submitted) { errno = EPROTO; return false; }
  store_snapshot(board, reply);
  return true;
}

static bool write_pwm(const t_bunny_arduino *board, ArduinoConnection *conn)
{
  for (unsigned i = 2; i < 14; ++i)
    if (conn->pwm & (1u << i))
      {
        double value = board->pwm_outputs[i];
        if (!std::isfinite(value) || value < 0 || value > 1)
          { errno = EINVAL; return false; }
        uint8_t duty = (uint8_t)(value * 255.0 + 0.5);
        if (conn->pwm_duty[i] != (int)duty)
          {
            if (!request(conn, 6, (uint8_t)i, duty, 0, NULL)) return false;
            conn->pwm_duty[i] = duty;
          }
      }
  return true;
}

static bool pwm_pin(size_t pin)
{
  return pin == 3 || pin == 5 || pin == 6 ||
         pin == 9 || pin == 10 || pin == 11;
}

t_bunny_arduino *bunny_new_arduino(const char *device)
{
  if (!device) { errno = EINVAL; return NULL; }
  int fd = open(device, O_RDWR | O_NOCTTY | O_CLOEXEC | O_NONBLOCK);
  if (fd < 0) return NULL;
  struct termios term;
  if (tcgetattr(fd, &term) < 0) { close(fd); return NULL; }
  cfmakeraw(&term);
  if (cfsetispeed(&term, B2000000) < 0 ||
      cfsetospeed(&term, B2000000) < 0)
    { close(fd); return NULL; }
  term.c_cflag |= CLOCAL | CREAD;
  term.c_cc[VMIN] = term.c_cc[VTIME] = 0;
  if (tcsetattr(fd, TCSANOW, &term) < 0) { close(fd); return NULL; }
  t_bunny_arduino *board = (t_bunny_arduino*)calloc(1, sizeof(*board));
  ArduinoConnection *conn = (ArduinoConnection*)calloc(1, sizeof(*conn));
  if (!board || !conn)
    { free(board); free(conn); close(fd); return NULL; }
  conn->fd = fd;
  for (unsigned i = 0; i < 14; ++i) conn->pwm_duty[i] = -1;
  board->_private = conn;
  struct timespec delay = {2, 0};
  while (nanosleep(&delay, &delay) < 0 && errno == EINTR) {}
  tcflush(fd, TCIOFLUSH);
  uint16_t identity = 0;
  if (!request(conn, 1, 0, 0, 0, &identity) || identity != 0x0303)
    { if (identity != 0x0303) errno = EPROTO;
      bunny_delete_arduino(board); return NULL; }
  return board;
}

void bunny_delete_arduino(t_bunny_arduino *board)
{
  if (!board) return;
  ArduinoConnection *conn = (ArduinoConnection*)board->_private;
  if (conn)
    { (void)drain(conn); close(conn->fd); free(conn); }
  free(board);
}

bool bunny_arduino_wait_ack(t_bunny_arduino *board)
{
  if (!board) { errno = EINVAL; return false; }
  return barrier((ArduinoConnection*)board->_private);
}

bool bunny_arduino_pin_mode(t_bunny_arduino *board, size_t pin,
                            t_bunny_arduino_mode mode)
{
  if (!board || pin < 2 || pin > 13 || mode > BUNNY_ARDUINO_INPUT_PULLUP)
    { errno = EINVAL; return false; }
  ArduinoConnection *conn = (ArduinoConnection*)board->_private;
  if (!barrier(conn) || !request(conn, 2, (uint8_t)pin, (uint8_t)mode, 0, NULL))
    return false;
  uint16_t mask = (uint16_t)(1u << pin);
  conn->pwm &= (uint16_t)~mask;
  conn->pwm_duty[pin] = -1;
  if (mode == BUNNY_ARDUINO_OUTPUT) conn->outputs |= mask;
  else conn->outputs &= (uint16_t)~mask;
  return true;
}

bool bunny_arduino_pwm(t_bunny_arduino *board, size_t pin)
{
  if (!board || !pwm_pin(pin)) { errno = EINVAL; return false; }
  ArduinoConnection *conn = (ArduinoConnection*)board->_private;
  if (!barrier(conn) || !request(conn, 6, (uint8_t)pin, 0, 0, NULL))
    return false;
  uint16_t mask = (uint16_t)(1u << pin);
  conn->outputs |= mask;
  conn->pwm |= mask;
  conn->pwm_duty[pin] = 0;
  return true;
}

bool bunny_arduino_write(const t_bunny_arduino *board)
{
  if (!board) { errno = EINVAL; return false; }
  ArduinoConnection *conn = (ArduinoConnection*)board->_private;
  // PWM changes and the GPIO image form one atomic submission to the queue.
  uint8_t frames[7 * 6];
  size_t count = 0;
  int new_duty[14];
  memcpy(new_duty, conn->pwm_duty, sizeof(new_duty));
  for (unsigned i = 2; i < 14; ++i)
    if (conn->pwm & (1u << i))
      {
        double v = board->pwm_outputs[i];
        if (!std::isfinite(v) || v < 0 || v > 1)
          { errno = EINVAL; return false; }
        int duty = (int)(v * 255.0 + 0.5);
        if (new_duty[i] != duty)
          {
            encode(frames + count, 11, (uint8_t)i, (uint8_t)duty, 0);
            count += 6;
            new_duty[i] = duty;
          }
      }
  uint16_t outputs = digital_outputs(board, conn);
  encode(frames + count, 9, (uint8_t)outputs, (uint8_t)(outputs >> 8), 0);
  count += 6;
  if (!enqueue_bytes(conn, frames, count)) return false;
  memcpy(conn->pwm_duty, new_duty, sizeof(new_duty));
  ++conn->submitted;
  return true;
}

bool bunny_arduino_read(t_bunny_arduino *board)
{
  if (!board) { errno = EINVAL; return false; }
  return snapshot(board, false);
}

bool bunny_arduino_sync(t_bunny_arduino *board)
{
  if (!board) { errno = EINVAL; return false; }
  ArduinoConnection *conn = (ArduinoConnection*)board->_private;
  if (!write_pwm(board, conn)) return false;
  return snapshot(board, true);
}
