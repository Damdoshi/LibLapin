
#include <assert.h>
#include <lapin.h>
#include <math.h>

t_bunny_network_info server;
t_bunny_network_info client;

static void close_network(void)
{
  bunny_network_close(client);
  bunny_network_close(server);
}

t_bunny_response handle_message(t_bunny_network_info inf,
                                void *buffer,
                                size_t size,
                                void *data)
{
  t_bunny_standard_command *cmd = (t_bunny_standard_command*)buffer;
  double delay;

  (void)inf;
  (void)data;

  assert(cmd->heartbeat_response.ciphered == false);
  assert(size == sizeof(cmd->heartbeat_response));
  assert(cmd->heartbeat_response.command == BSCT_HEARTBEAT_RESPONSE);
  delay = fabs(cmd->heartbeat_response.declared_sending_date - bunny_get_time() / 1e9);
  assert(delay < 0.2);
  return SWITCH_CONTEXT;
}

int main(void)
{
  float start = bunny_get_time() / 1e9 - 2;
  float mid = bunny_get_time() / 1e9 - 1;
  float end = bunny_get_time() / 1e9;
  float half = (end - start) / 2.0f;

  t_bunny_standard_command hb = {
    .heartbeat = {
      .ciphered = 0,
      .command = BSCT_HEARTBEAT,
      .declared_sending_date = 0
    }
  };
  t_bunny_standard_command hbr = {
    .heartbeat_response = {
      .ciphered = 0,
      .command = BSCT_HEARTBEAT_RESPONSE,
      .declared_sending_date = mid,
      .original_sending_date = start
    }
  };
  t_bunny_identity id = {
    .identity = "damdoshi",
    .secret = "0123456789",
    .validated = BIS_AWAITING_CONFIRMATION,
    .last_challenge = 0,
    .info = {},
    .usual_delay = 0,
    .estimated_clock_difference = 0,
    .last_exchange = 0
  };

  server = bunny_network_open(BP_TCP_IMMEDIATE, 0, 0, 1000, false, 6502, NULL);
  client = bunny_network_open(BP_TCP_IMMEDIATE, 0, 0, 1000, false, 6502, "127.0.0.1");
  assert(server.socklen != 0);
  assert(client.socklen != 0);
  atexit(close_network);

  id.info = client;
  assert(bunny_handle_standard_command(&id, &hb, sizeof(hb), BH_DJB2, BS_XOR) == BSCH_SUCCESS);
  assert(bunny_handle_standard_command(&id, &hbr, sizeof(hbr), BH_DJB2, BS_XOR) == BSCH_SUCCESS);

  bunny_set_message_response(handle_message);
  assert(bunny_loop(NULL, 50, &hb) == SWITCH_CONTEXT);

  assert(fabs(id.usual_delay - half) < 0.01);
  assert(fabs(id.estimated_clock_difference - ((mid - start) - half)) < 0.01);
  return EXIT_SUCCESS;
}
