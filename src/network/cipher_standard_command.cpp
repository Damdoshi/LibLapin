// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
//
// Bibliotheque Lapin

#include		"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_cipher_standard_command
 * @doc-kind function
 * @doc-module network
 * @doc-order 730
 * @doc-since 12
 * @doc-until latest
 * @doc-level expert
 *
 * @doc-lang en
 * @brief Applies LibLapin standard-command ciphering in place.
 * @param id Identity context. Server side, this is the target peer; client side, this is the local identity.
 * @param cmd Command buffer to cipher.
 * @param cmd_size Command size in bytes.
 * @param hash Hash algorithm used to derive command masks.
 * @param ciphering Ciphering algorithm to apply.
 * @return-success Returns true if the command was ciphered.
 * @return-failure Returns false on error.
 * @see t_bunny_standard_command, bunny_handle_standard_command
 *
 * @doc-lang fr
 * @brief Applique sur place le chiffrement des commandes standard LibLapin.
 * @param id Contexte d'identité. Côté serveur, c'est le pair cible ; côté client, c'est l'identité locale.
 * @param cmd Tampon de commande à chiffrer.
 * @param cmd_size Taille de la commande en octets.
 * @param hash Algorithme de hachage utilisé pour dériver les masques de commande.
 * @param ciphering Algorithme de chiffrement à appliquer.
 * @return-success Renvoie true si la commande a été chiffrée.
 * @return-failure Renvoie false en cas d'erreur.
 * @see t_bunny_standard_command, bunny_handle_standard_command
 */
bool			bunny_cipher_standard_command
  (t_bunny_identity		*id, // Server side, the target. Client side: me
   t_bunny_standard_command	*cmd,
   size_t			cmd_size,
   t_bunny_hash_algorithm	hash,
   t_bunny_ciphering		ciphering
   )
{
  if (cmd->command < BSCT_LAST_STANDARD_COMMAND)
    return (true);
  size_t			offset = (size_t)&cmd->mask_source[sizeof(cmd->mask_source)] - (size_t)cmd;
  void				*data = &((char*)cmd)[offset];
  char				*mask;
  struct {
    int32_t			length;
    char			tmp[sizeof(id->secret) + sizeof(cmd->mask_source)];
  }				key;

  if (cmd_size < offset)
    return (true);
  cmd_size -= offset;
  cmd->ciphered = true;
  if ((mask = (char*)malloc(cmd_size)) == NULL)
    return (false);
  for (size_t i = 0; i < sizeof(cmd->mask_source); ++i)
    cmd->mask_source[i] = rand() % 256;
  key.length = sizeof(key.tmp);
  memcpy(key.tmp, id->secret, sizeof(id->secret));
  memcpy(&key.tmp[sizeof(id->secret)], cmd->mask_source, sizeof(cmd->mask_source));
  bunny_wide_hash(hash, key.tmp, key.length, mask, cmd_size);
  
  bunny_cipher_data(data, cmd_size, ciphering, (t_bunny_cipher_key*)&key);
  bunny_erase_and_free((void*)mask, cmd_size);
  return (true);
}
