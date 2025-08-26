/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2025
** Pentacle Technologie 2008-2025
** EFRITS 2022-2025
**
** Bibliothèque Lapin
*/

#include			<assert.h>
#include			<lapin.h>
#include			<math.h>

const t_bunny_network_info	*server;
const t_bunny_network_info	*client;

static void			close_network(void)
{
  bunny_network_close(client);
  bunny_network_close(server);
}

t_bunny_response		handle_message(t_bunny_network_info inf,
					       void		*buffer,
					       size_t		size,
					       void		*data)
{
  t_bunny_standard_command	*cmd = buffer;
  double			delay;

  (void)inf;
  (void)data;
  
  assert(cmd->heartbeat.ciphered == false);

  assert(size == sizeof(cmd->heartbeat_response));
  delay = fabs(cmd->heartbeat_response.declared_sending_date - bunny_get_time() / 1e9);
  assert(cmd->heartbeat_response.command == BSCT_HEARTBEAT_RESPONSE);
  assert(delay < 0.2);
  return (SWITCH_CONTEXT);
}

int				main(void)
{
  float			start = bunny_get_time() / 1e9 - 2;
  float			mid = bunny_get_time() / 1e9 - 1;
  float			end = bunny_get_time() / 1e9;
  float			half = (end - start) / 2.0;

  t_bunny_standard_command	hb = {
    .heartbeat = {
      .ciphered = 0,
      .command = BSCT_HEARTBEAT,
      .declared_sending_date = 0
    }
  };
  t_bunny_standard_command	hbr = {
    .heartbeat_response = {
      .ciphered = 0,
      .command = BSCT_HEARTBEAT_RESPONSE,
      .declared_sending_date = mid,
      .original_sending_date = start
    }
  };
  t_bunny_identity		id = {
    .identity = "damdoshi",
    .secret = "0123456789",
    .validated = false,
    .last_challenge = 0,
    .info = {},
    .usual_delay = 0,
    .estimated_clock_difference = 0,
    .last_exchange = 0
  };

  assert((server = bunny_network_open(BP_IMMEDIATE_RETRIEVE, 0, 0, 6502, NULL)));
  assert((client = bunny_network_open(BP_IMMEDIATE_RETRIEVE, 0, 0, 6502, "127.0.0.1")));
  atexit(close_network);
  id.info = *client;
  assert(bunny_handle_standard_command(&id, &hb, sizeof(hb), BH_DJB2, BS_XOR) == BSCH_SUCCESS);
  assert(bunny_handle_standard_command(&id, &hbr, sizeof(hbr), BH_DJB2, BS_XOR) == BSCH_SUCCESS);

  bunny_set_message_response(handle_message);
  assert(bunny_loop(NULL, 50, &hb) == SWITCH_CONTEXT);

  // On vérifie que la réponse est bien admise
  assert(fabs(id.usual_delay - half) < 0.01);
  assert(fabs(id.estimated_clock_difference - ((mid - start) - half)) < 0.01);
  return (EXIT_SUCCESS);
}
