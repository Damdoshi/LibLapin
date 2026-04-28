
#include <assert.h>
#include <lapin.h>
#include <strings.h>

t_bunny_network_info server;
t_bunny_network_info client;

t_bunny_identity srv_id[2] = {
  {
    .identity = "damdoshi",
    .secret = "0123456789",
    .validated = BIS_AWAITING_CONFIRMATION,
    .last_challenge = 0,
    .info = {},
    .usual_delay = 0,
    .estimated_clock_difference = 0,
    .last_exchange = 0
  },
  { .identity = "" }
};

t_bunny_identity clt_id = {
  .identity = "damdoshi",
  .secret = "WRONG_SECRET",
  .validated = BIS_AWAITING_CONFIRMATION,
  .last_challenge = 0,
  .info = {},
  .usual_delay = 0,
  .estimated_clock_difference = 0,
  .last_exchange = 0
};

static void close_network(void)
{
  bunny_network_close(client);
  bunny_network_close(server);
}

t_bunny_response handle_connect(t_bunny_network_info inf,
                                t_bunny_event_state state,
                                void *data)
{
  (void)inf; (void)state; (void)data;
  return GO_ON;
}

t_bunny_response handle_message(t_bunny_network_info inf,
                                void *buffer,
                                size_t size,
                                void *data)
{
  static size_t counter = 0;
  t_bunny_standard_command *cmd = (t_bunny_standard_command*)buffer;
  t_bunny_identity *id;

  (void)data;
  counter += 1;
  if (counter == 1)
    {
      assert(cmd->command == BSCT_CHALLENGE_REQUEST);
      id = &srv_id[0];
      id->info = inf;
      assert(bunny_handle_standard_command(id, cmd, size, BH_DJB2, BS_XOR) == BSCH_SUCCESS);
      return GO_ON;
    }
  if (counter == 2)
    {
      assert(cmd->command == BSCT_CHALLENGE);
      assert(bunny_handle_standard_command(&clt_id, cmd, size, BH_DJB2, BS_XOR) == BSCH_SUCCESS);
      return GO_ON;
    }
  if (counter == 3)
    {
      assert(cmd->command == BSCT_CHALLENGE_RESPONSE);
      id = bunny_resolve_identity(srv_id, inf);
      assert(id == &srv_id[0]);
      assert(bunny_handle_standard_command(id, cmd, size, BH_DJB2, BS_XOR) == BSCH_SUCCESS);
      assert(id->validated == BIS_IDENTITY_REFUSED);
      return GO_ON;
    }
  if (counter == 4)
    {
      assert(cmd->command == BSCT_CHALLENGE_RESULT);
      assert(size == sizeof(cmd->challenge_result));
      assert(cmd->challenge_result.result == 0);
      assert(bunny_handle_standard_command(&clt_id, cmd, size, BH_DJB2, BS_XOR) == BSCH_SUCCESS);
      assert(clt_id.validated == BIS_IDENTITY_REFUSED);
      return SWITCH_CONTEXT;
    }
  return EXIT_ON_ERROR;
}

int main(void)
{
  t_bunny_standard_command request = {
    .challenge_request = {
      .ciphered = 0,
      .command = BSCT_CHALLENGE_REQUEST,
      .declared_sending_date = 0,
      .identity = "damdoshi"
    }
  };

  server = bunny_network_open(BP_TCP_IMMEDIATE, 0, 0, 1000, false, 6503, NULL);
  client = bunny_network_open(BP_TCP_IMMEDIATE, 0, 0, 1000, false, 6503, "127.0.0.1");
  assert(server.socklen != 0);
  assert(client.socklen != 0);
  atexit(close_network);
  bunny_set_connect_response(handle_connect);
  bunny_set_message_response(handle_message);
  clt_id.info = client;

  assert(bunny_network_write(client, &request, sizeof(request)));
  assert(bunny_loop(NULL, 50, NULL) == SWITCH_CONTEXT);
  return EXIT_SUCCESS;
}
