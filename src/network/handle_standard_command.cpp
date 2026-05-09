// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
//
// Bibliotheque Lapin

#include		"lapin_private.h"

static t_bunny_standard_command	*handle_ciphering
  (const t_bunny_identity	*id, // Coté serveur: qui me parle. Coté client: moi.
   t_bunny_standard_command	*cmd,
   size_t			cmd_size,
   t_bunny_hash_algorithm	hash,
   t_bunny_ciphering		ciphering
   )
{
  size_t			offset = (size_t)&cmd->mask_source[sizeof(cmd->mask_source)] - (size_t)cmd;
  void				*data = &((char*)cmd)[offset];
  char				*mask;
  struct {
    int32_t			length;
    char			tmp[sizeof(id->secret) + sizeof(cmd->mask_source)];
  } key;

  if (!cmd->ciphered)
    return (cmd);
  if (cmd_size >= BUNNY_NETWORK_MAXIMUM_PACKET_SIZE || cmd_size < offset)
    return (NULL);
  cmd_size -= offset;

  if ((mask = (char*)malloc(cmd_size)) == NULL)
    return (NULL);
  key.length = sizeof(key.tmp);
  memcpy(key.tmp, id->secret, sizeof(id->secret));
  memcpy(&key.tmp[sizeof(id->secret)], cmd->mask_source, sizeof(cmd->mask_source));
  bunny_wide_hash(hash, key.tmp, key.length, mask, cmd_size);
  bunny_uncipher_data(data, cmd_size, ciphering, (t_bunny_cipher_key*)&key);

  cmd->ciphered = 0;
  for (size_t i = 0; i < sizeof(cmd->mask_source); ++i)
    cmd->mask_source[i] = 0;
  bunny_erase_and_free((void*)mask, cmd_size);
  return (cmd);
}


/**
 * @doc
 * @doc-symbol bunny_handle_standard_command
 * @doc-kind function
 * @doc-module network
 * @doc-order 720
 * @doc-since 12
 * @doc-until latest
 * @doc-level expert
 *
 * @doc-lang en
 * @brief Handles a LibLapin standard network command when possible.
 * @param id Identity context. Server side, this is the speaking peer; client side, this is the local identity.
 * @param cmd Command buffer to inspect and possibly handle.
 * @param cmd_size Command size in bytes.
 * @param hash Hash algorithm used for challenge responses.
 * @param ciphering Ciphering mode used by command handling.
 * @return-success Returns BSCH_SUCCESS if the command was handled, BSCH_TO_BE_DONE if user code must handle it, or BSCH_FAILURE on failure.
 * @see t_bunny_standard_command, t_bunny_standard_command_handling, bunny_cipher_standard_command
 *
 * @doc-lang fr
 * @brief Traite une commande réseau standard LibLapin lorsque c'est possible.
 * @param id Contexte d'identité. Côté serveur, c'est le pair qui parle ; côté client, c'est l'identité locale.
 * @param cmd Tampon de commande à inspecter et éventuellement traiter.
 * @param cmd_size Taille de la commande en octets.
 * @param hash Algorithme de hachage utilisé pour les réponses aux défis.
 * @param ciphering Mode de chiffrement utilisé par le traitement de commande.
 * @return-success Renvoie BSCH_SUCCESS si la commande a été traitée, BSCH_TO_BE_DONE si le code utilisateur doit la traiter, ou BSCH_FAILURE en cas d'échec.
 * @see t_bunny_standard_command, t_bunny_standard_command_handling, bunny_cipher_standard_command
 */
t_bunny_standard_command_handling bunny_handle_standard_command
  (t_bunny_identity		*id,
   t_bunny_standard_command	*cmd,
   size_t			cmd_size,
   t_bunny_hash_algorithm	hash,
   t_bunny_ciphering		ciphering
   )
{
  if (handle_ciphering(id, cmd, cmd_size, hash, ciphering) == NULL)
    return (BSCH_FAILURE);
  // On enregistre la dernière date de l'échange
  id->last_exchange = bunny_get_time() / 1e9;
  if (cmd->command >= BSCT_LAST_STANDARD_COMMAND)
    return (BSCH_TO_BE_DONE);
  switch (cmd->command)
    {
    case BSCT_HEARTBEAT:
      {
	t_bunny_heartbeat_response_command resp = {
	  0,
	  BSCT_HEARTBEAT_RESPONSE,
	  (float)(bunny_get_time() / 1e9),
	  cmd->heartbeat.declared_sending_date
	};

	if (bunny_network_write(id->info, &resp, sizeof(resp)) == false)
	  return (BSCH_FAILURE);
	return (BSCH_SUCCESS);
      }
    case BSCT_HEARTBEAT_RESPONSE:
      {
	float			start = cmd->heartbeat_response.original_sending_date;
	float			mid = cmd->heartbeat_response.declared_sending_date;
	float			end = (float)(bunny_get_time() / 1e9);
	float			half = (end - start) / 2.0f;

	id->usual_delay = half;
	id->estimated_clock_difference = (mid - start) - half;
	return (BSCH_SUCCESS);
      }
    case BSCT_CHALLENGE_REQUEST:
      {
	// On a recu une demande de reconnaissance d'identité
	// On enregistre l'identitée demandée
	id->validated = BIS_AWAITING_CONFIRMATION;
	strncpy(id->identity, (char*)cmd->challenge_request.identity, sizeof(id->identity));

	char			buffer[sizeof(id->secret) + sizeof(cmd->challenge.challenge)];
	t_bunny_challenge_command resp = {
	  0,
	  BSCT_CHALLENGE,
	  (float)(bunny_get_time() / 1e9),
	  {}
	};

	memcpy(buffer, id->secret, sizeof(id->secret));
	for (size_t i = 0; i < sizeof(resp.challenge); ++i)
	  {
	    resp.challenge[i] = rand() % 255;
	    buffer[sizeof(id->secret) + i] = resp.challenge[i];
	  }
	id->last_challenge = bunny_hash(hash, buffer, sizeof(buffer));

	// On envoit le défi
	if (bunny_network_write(id->info, &resp, sizeof(resp)) == false)
	  return (BSCH_FAILURE);
	return (BSCH_SUCCESS);
      }
    case BSCT_CHALLENGE:
      {
	// On a recu un défi à relever
	t_bunny_challenge_response_command resp = {
	  0,
	  BSCT_CHALLENGE_RESPONSE,
	  (float)(bunny_get_time() / 1e9),
	  {}
	};
	// On prépare le tampon pour relever le défi
	char			buffer[sizeof(id->secret) + sizeof(cmd->challenge.challenge)];

	memcpy(buffer, id->secret, sizeof(id->secret));
	memcpy(&buffer[sizeof(id->secret)], cmd->challenge.challenge, sizeof(cmd->challenge.challenge));
	resp.response = bunny_hash(hash, buffer, sizeof(buffer));

	if (bunny_network_write(id->info, &resp, sizeof(resp)) == false)
	  return (BSCH_FAILURE);
	return (BSCH_SUCCESS);
      }
    case BSCT_CHALLENGE_RESPONSE:
      {
	// On a recu une réponse au défi généré pour reconnaitre une identité
	// Si le résultat n'est pas celui attendu, on rejette l'authentification
	if (id->validated != BIS_AWAITING_CONFIRMATION)
	  return (BSCH_SUCCESS);
	if (id->last_challenge == cmd->challenge_response.response)
	  id->validated = BIS_IDENTITY_CONFIRMED;
	else
	  id->validated = BIS_IDENTITY_REFUSED;
	t_bunny_challenge_result_command resp = {
	  0,
	  BSCT_CHALLENGE_RESULT,
	  (float)(bunny_get_time() / 1e9),
	  id->validated == BIS_IDENTITY_CONFIRMED ? 1 : 0
	};

	if (bunny_network_write(id->info, &resp, sizeof(resp)) == false)
	  return (BSCH_FAILURE);
	return (BSCH_SUCCESS);
      }
    case BSCT_CHALLENGE_RESULT:
      {
	id->validated = cmd->challenge_result.result ? BIS_IDENTITY_CONFIRMED : BIS_IDENTITY_REFUSED;
	return (BSCH_SUCCESS);
      }
    default:
      return (BSCH_TO_BE_DONE);
    }
  return (BSCH_TO_BE_DONE);
}
