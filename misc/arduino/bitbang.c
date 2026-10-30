#include <avr/io.h>
#include <stdint.h>

/* Bunny-UNO wire protocol v3: requests A5 cmd a b c xor;
 * replies 5A cmd status lo hi xor. XOR includes the first 5 bytes.
 * Pins 0 and 1 are always reserved for UART.
 */
enum { HELLO=1, MODE=2, DIGITAL_READ=3, DIGITAL_WRITE=4,
       ANALOG_READ=5, PWM_WRITE=6, SNAPSHOT=7, SYNC=8, DIGITAL_WRITE_ALL=9, BARRIER=10, PWM_STREAM=11 };
enum { OK=0, BAD_PIN=1, BAD_ARG=2, BAD_CMD=3 };

static uint8_t receive(void)
{
  while (!(UCSR0A & _BV(RXC0))) {}
  return UDR0;
}
static void transmit(uint8_t byte)
{
  while (!(UCSR0A & _BV(UDRE0))) {}
  UDR0 = byte;
}
static void reply(uint8_t cmd, uint8_t status, uint16_t data)
{
  uint8_t frame[6] = {0x5a, cmd, status, (uint8_t)data,
                      (uint8_t)(data >> 8), 0};
  for (uint8_t i=0; i<5; ++i) frame[5] ^= frame[i];
  for (uint8_t i=0; i<6; ++i) transmit(frame[i]);
}
static uint8_t mask_for(uint8_t pin)
{
  return _BV(pin < 8 ? pin : pin < 14 ? pin-8 : pin-14);
}
static volatile uint8_t *ddr_for(uint8_t pin)
{
  return pin < 8 ? &DDRD : pin < 14 ? &DDRB : &DDRC;
}
static volatile uint8_t *port_for(uint8_t pin)
{
  return pin < 8 ? &PORTD : pin < 14 ? &PORTB : &PORTC;
}
static volatile uint8_t *pin_for(uint8_t pin)
{
  return pin < 8 ? &PIND : pin < 14 ? &PINB : &PINC;
}
static uint8_t valid(uint8_t pin) { return pin >= 2 && pin <= 19; }

/* PWM on D3, D5, D6, D9, D10, D11. Hardware timers in fast-PWM 8-bit mode. */
static uint8_t pwm(uint8_t pin, uint8_t duty)
{
  switch (pin)
    {
    case 3:  TCCR2A |= _BV(WGM20)|_BV(WGM21)|_BV(COM2B1);
             TCCR2B = (TCCR2B & ~7) | _BV(CS22); OCR2B=duty; break;
    case 5:  TCCR0A |= _BV(WGM00)|_BV(WGM01)|_BV(COM0B1);
             TCCR0B = (TCCR0B & ~7) | _BV(CS01)|_BV(CS00); OCR0B=duty; break;
    case 6:  TCCR0A |= _BV(WGM00)|_BV(WGM01)|_BV(COM0A1);
             TCCR0B = (TCCR0B & ~7) | _BV(CS01)|_BV(CS00); OCR0A=duty; break;
    case 9:  TCCR1A |= _BV(WGM10)|_BV(COM1A1);
             TCCR1B = (TCCR1B & ~(_BV(WGM13)|_BV(WGM12)|7)) | _BV(CS11)|_BV(CS10);
             OCR1A=duty; break;
    case 10: TCCR1A |= _BV(WGM10)|_BV(COM1B1);
             TCCR1B = (TCCR1B & ~(_BV(WGM13)|_BV(WGM12)|7)) | _BV(CS11)|_BV(CS10);
             OCR1B=duty; break;
    case 11: TCCR2A |= _BV(WGM20)|_BV(WGM21)|_BV(COM2A1);
             TCCR2B = (TCCR2B & ~7) | _BV(CS22); OCR2A=duty; break;
    default: return 0;
    }
  *ddr_for(pin) |= mask_for(pin);
  return 1;
}
static void disable_pwm(uint8_t pin)
{
  switch(pin)
    {
    case 3: TCCR2A &= ~_BV(COM2B1); break;
    case 5: TCCR0A &= ~_BV(COM0B1); break;
    case 6: TCCR0A &= ~_BV(COM0A1); break;
    case 9: TCCR1A &= ~_BV(COM1A1); break;
    case 10:TCCR1A &= ~_BV(COM1B1); break;
    case 11:TCCR2A &= ~_BV(COM2A1); break;
    }
}
static uint16_t adc_read(uint8_t channel)
{
  ADMUX = _BV(REFS0) | channel;
  ADCSRA |= _BV(ADSC);
  while (ADCSRA & _BV(ADSC)) {}
  return ADC;
}

/* V3 extended response: marker, command, status, 2-byte digital snapshot,
 * 6 x 10-bit ADC values as little endian uint16, XOR of preceding bytes.
 * Sent only for SYNC, preserving v1 responses for all older commands.
 */
static void reply_snapshot(uint8_t status)
{
  uint8_t frame[20] = {0x5a, SYNC, status};
  extern uint16_t executed_writes;
  frame[3] = executed_writes; frame[4] = executed_writes >> 8;
  uint16_t value = ((uint16_t)(PINB & 0x3f) << 8) | (PIND & 0xfc);
  frame[5] = value; frame[6] = value >> 8;
  for (uint8_t i = 0; i < 6; ++i)
    {
      value = adc_read(i);
      frame[7 + i * 2] = value;
      frame[8 + i * 2] = value >> 8;
    }
  for (uint8_t i = 0; i < 19; ++i) frame[19] ^= frame[i];
  for (uint8_t i = 0; i < 20; ++i) transmit(frame[i]);
}

static void write_all(uint16_t value)
{
  /* Only currently configured output pins; never touch UART D0/D1.
   * PWM timer compare output overrides PORT, so it remains active.
   */
  uint8_t mask_d = DDRD & 0xfc;
  uint8_t mask_b = DDRB & 0x3f;
  PORTD = (PORTD & ~mask_d) | ((uint8_t)value & mask_d);
  PORTB = (PORTB & ~mask_b) | ((uint8_t)(value >> 8) & mask_b);
}
uint16_t executed_writes;
static void command(uint8_t cmd, uint8_t a, uint8_t b, uint8_t c)
{
  (void)c;
  uint16_t value=0;
  uint8_t status=OK;
  uint8_t mask=mask_for(a);
  switch(cmd)
    {
    case HELLO: value=0x0303; break; /* protocol 2, UNO R3 */
    case DIGITAL_WRITE_ALL:
      write_all((uint16_t)a | ((uint16_t)b << 8));
      ++executed_writes;
      return; /* Streaming GPIO: no per-write acknowledgement. */
    case PWM_STREAM:
      (void)pwm(a, b);
      return; /* Streaming PWM, no individual reply. */
    case BARRIER: value=executed_writes; break;
    case SYNC:
      if (c > 1) { reply_snapshot(BAD_ARG); return; }
      if (c) write_all((uint16_t)a | ((uint16_t)b << 8));
      reply_snapshot(OK);
      return; /* protocol 1, board ID 3 = UNO R3 */
    case MODE:
      if (!valid(a)) { status=BAD_PIN; break; }
      if (b>2) { status=BAD_ARG; break; }
      disable_pwm(a);
      if (b==2) { *ddr_for(a) &= ~mask; *port_for(a) |= mask; }
      else if (b==1) { *port_for(a) &= ~mask; *ddr_for(a) |= mask; }
      else { *ddr_for(a) &= ~mask; *port_for(a) &= ~mask; }
      break;
    case DIGITAL_READ:
      if (!valid(a)) { status=BAD_PIN; break; }
      value=((*pin_for(a) & mask) != 0); break;
    case DIGITAL_WRITE:
      if (!valid(a)) { status=BAD_PIN; break; }
      disable_pwm(a);
      if (b) *port_for(a) |= mask;
      else *port_for(a) &= ~mask;
      break;
    case ANALOG_READ:
      if (a>5) { status=BAD_PIN; break; }
      value=adc_read(a); break;
    case PWM_WRITE:
      if (!pwm(a,b)) status=BAD_PIN;
      break;
    case SNAPSHOT:
      /* Bits 0..13 correspond to digital pins 0..13, D0/D1 cleared. */
      value=((uint16_t)(PINB & 0x3f)<<8) | (PIND & 0xfc);
      break;
    default: status=BAD_CMD;
    }
  reply(cmd,status,value);
}
int main(void)
{
  /* 2,000,000 baud at 16 MHz: UBRR=0, U2X=1. */
  UCSR0A=_BV(U2X0);
  UBRR0H=0; UBRR0L=0;
  UCSR0B=_BV(RXEN0)|_BV(TXEN0);
  UCSR0C=_BV(UCSZ01)|_BV(UCSZ00);
  ADCSRA=_BV(ADEN)|_BV(ADPS2)|_BV(ADPS1)|_BV(ADPS0);
  for (;;) {
    if (receive()!=0xa5) continue;
    uint8_t frame[5]; frame[0]=0xa5;
    for (uint8_t i=1; i<5; ++i) frame[i]=receive();
    uint8_t checksum=receive();
    for (uint8_t i=0; i<5; ++i) checksum ^= frame[i];
    if (checksum) continue;
    command(frame[1],frame[2],frame[3],frame[4]);
  }
}
