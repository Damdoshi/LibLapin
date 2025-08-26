/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2025
** Pentacle Technologie 2008-2025
** EFRITS 2022-2025
**
** Bibliothèque Lapin
*/

/*
** Le probleme actuel est qu'une seule socket UDP crée un descirptor et UN SEUL PEER
** alors qu'il y a un nombre de PEER indeterminé sur une socket UDP.
** LA reception d'un packet UDP doit automatiquement provoquer l'inspection des Peer actuels et la
** création d'un nouveau s'il n'existe pas
*/

#include			<assert.h>
#include			<lapin.h>
#include			<math.h>

const t_bunny_network_info	*server;
const t_bunny_network_info	*client;

t_bunny_identity		srv_id[3] = {
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
t_bunny_identity		clt_id = {
  .identity = "damdoshi",
  .secret = "0123456789",
  .validated = BIS_AWAITING_CONFIRMATION,
  .last_challenge = 0,
  .info = {},
  .usual_delay = 0,
  .estimated_clock_difference = 0,
  .last_exchange = 0
};

static void			close_network(void)
{
  bunny_network_close(client);
  bunny_network_close(server);
}

t_bunny_response		handle_connect(t_bunny_network_info inf,
					       t_bunny_event_state state,
					       void		*data)
{
  (void)inf;
  (void)state;
  (void)data;
  return (GO_ON);
}

t_bunny_response		handle_message(t_bunny_network_info inf,
					       void		*buffer,
					       size_t		size,
					       void		*data)
{
  static size_t			counter = 0;
  t_bunny_standard_command	*cmd = buffer;
  t_bunny_identity		*id;

  (void)data;
  counter += 1;
  bunny_network_dump(1);
  if (counter == 1)
    { // Receiving CHALLENGE REQUEST as server
      assert(cmd->ciphered == 0);
      assert(cmd->command == BSCT_CHALLENGE_REQUEST);
      assert(size == sizeof(cmd->challenge_request));
      id = NULL;
      for (size_t i = 0; srv_id[i].identity[0]; ++i)
	if (strcasecmp(cmd->challenge_request.identity, srv_id[i].identity) == 0)
	  {
	    id = &srv_id[i];
	    break ;
	  }
      assert(id);
      assert(id->validated == BIS_AWAITING_CONFIRMATION);
      if (id->validated != BIS_IDENTITY_CONFIRMED)
	{
	  // Si on a pas deja quelqu'un qui s'est déclaré.
	  id->info = inf;
	  assert(bunny_handle_standard_command
		 (id, buffer, size, BH_DJB2, BS_XOR) == BSCH_SUCCESS);
	}
      else
	{
	  // Si on a déjà quelqu'un qui est déclaré.
	  // envoyer un paquet CHALLENGE_RESULT avec REFUSED
	}
      return (GO_ON);
    }
  if (counter == 2)
    { // Receiving CHALLENGE as client
      assert(cmd->ciphered == 0);
      assert(cmd->command == BSCT_CHALLENGE);
      assert(size == sizeof(cmd->challenge));
      //
      assert(clt_id.validated == BIS_AWAITING_CONFIRMATION);
      assert(bunny_handle_standard_command
	     (&clt_id, buffer, size, BH_DJB2, BS_XOR) == BSCH_SUCCESS);
      return (GO_ON);
    }
  if (counter == 3)
    { // Receiving CHALLENGE_RESPONSE as server
      assert(cmd->ciphered == 0);
      assert(cmd->command == BSCT_CHALLENGE_RESPONSE);
      assert(size == sizeof(cmd->challenge_response));
      //
      assert((id = bunny_resolve_identity(srv_id, &inf)));
      assert(id->validated == BIS_AWAITING_CONFIRMATION);
      //
      assert(bunny_handle_standard_command
	     (id, buffer, size, BH_DJB2, BS_XOR) == BSCH_SUCCESS);
      assert(id->validated == BIS_IDENTITY_CONFIRMED);
      return (GO_ON);
    }
  if (counter == 4)
    { // Receiving CHALLENGE RESULT as client
      assert(cmd->ciphered == 0);
      assert(cmd->command == BSCT_CHALLENGE_RESPONSE);
      assert(size == sizeof(cmd->challenge_result));
      //
      assert(clt_id.validated == BIS_AWAITING_CONFIRMATION);
      assert(bunny_handle_standard_command
	     (&clt_id, buffer, size, BH_DJB2, BS_XOR) == BSCH_SUCCESS);
      assert(clt_id.validated == BIS_IDENTITY_CONFIRMED);
      return (SWITCH_CONTEXT);
    }
  return (EXIT_ON_ERROR);
}
int				main(void)
{
  t_bunny_standard_command	request = {
    .challenge_request = {
      .ciphered = 0,
      .command = BSCT_CHALLENGE_REQUEST,
      .declared_sending_date = 0,
      .identity = "damdoshi"
    }
  };

  clt_id = srv_id[1];

  assert((server = bunny_network_open(BP_IMMEDIATE_RETRIEVE, 0, 0, 6502, NULL)));
  assert((client = bunny_network_open(BP_IMMEDIATE_RETRIEVE, 0, 0, 6502, "127.0.0.1")));
  bunny_set_connect_response(handle_connect);
  bunny_set_message_response(handle_message);
  atexit(close_network);

  // Quand on est client, on sait qui on est, donc on s'établit direct
  clt_id.info = *client;

  // Execution of challenge request
  assert(bunny_network_write(client, &request, sizeof(request)));
  assert(bunny_loop(NULL, 50, NULL) == SWITCH_CONTEXT);

  return (EXIT_SUCCESS);
}
