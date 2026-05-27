
#include <assert.h>
#include <lapin.h>
#include <strings.h>

t_bunny_network_info server;
t_bunny_network_info client;

t_bunny_identity srv_id[3] = {
  {
    .identity = "mordanis",
    .secret = "",
    .validated = BIS_AWAITING_CONFIRMATION,
    .last_challenge = 0,
    .info = {},
    .usual_delay = 0,
    .estimated_clock_difference = 0,
    .last_exchange = 0
  },
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
  {
    .identity = ""
  }
};
t_bunny_identity clt_id = {
  .identity = "damdoshi",
  .secret = "0123456789",
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
      assert(cmd->ciphered == 0);
      assert(cmd->command == BSCT_CHALLENGE_REQUEST);
      assert(size == sizeof(cmd->challenge_request));
      id = NULL;
      for (size_t i = 0; srv_id[i].identity[0]; ++i)
        if (strcasecmp(cmd->challenge_request.identity, srv_id[i].identity) == 0)
          { id = &srv_id[i]; break; }
      assert(id);
      assert(id->validated == BIS_AWAITING_CONFIRMATION);
      id->info = inf;
      assert(bunny_handle_standard_command(id, cmd, size, BH_DJB2, BS_XOR) == BSCH_SUCCESS);
      return GO_ON;
    }
  if (counter == 2)
    {
      assert(cmd->ciphered == 0);
      assert(cmd->command == BSCT_CHALLENGE);
      assert(size == sizeof(cmd->challenge));
      assert(clt_id.validated == BIS_AWAITING_CONFIRMATION);
      assert(bunny_handle_standard_command(&clt_id, cmd, size, BH_DJB2, BS_XOR) == BSCH_SUCCESS);
      return GO_ON;
    }
  if (counter == 3)
    {
      assert(cmd->ciphered == 0);
      assert(cmd->command == BSCT_CHALLENGE_RESPONSE);
      assert(size == sizeof(cmd->challenge_response));
      id = bunny_resolve_identity(srv_id, inf);
      assert(id);
      assert(id->validated == BIS_AWAITING_CONFIRMATION);
      assert(bunny_handle_standard_command(id, cmd, size, BH_DJB2, BS_XOR) == BSCH_SUCCESS);
      assert(id->validated == BIS_IDENTITY_CONFIRMED);
      return GO_ON;
    }
  if (counter == 4)
    {
      assert(cmd->ciphered == 0);
      assert(cmd->command == BSCT_CHALLENGE_RESULT);
      assert(size == sizeof(cmd->challenge_result));
      assert(clt_id.validated == BIS_AWAITING_CONFIRMATION);
      assert(bunny_handle_standard_command(&clt_id, cmd, size, BH_DJB2, BS_XOR) == BSCH_SUCCESS);
      assert(clt_id.validated == BIS_IDENTITY_CONFIRMED);
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

  clt_id = srv_id[1];

  server = bunny_network_open(BP_TCP_IMMEDIATE, 0, 0, 1000, false, 6502, NULL);
  client = bunny_network_open(BP_TCP_IMMEDIATE, 0, 0, 1000, false, 6502, "127.0.0.1");
  assert(server.socklen != 0);
  assert(client.socklen != 0);
  bunny_set_connect_response(handle_connect);
  bunny_set_message_response(handle_message);
  atexit(close_network);

  clt_id.info = client;

  assert(bunny_network_write(client, &request, sizeof(request)));
  assert(bunny_loop(NULL, 50, NULL) == SWITCH_CONTEXT);
  return EXIT_SUCCESS;
}
