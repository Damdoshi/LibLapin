// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_delete_key
 * @doc-kind function
 * @doc-module security
 * @doc-order 280
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Releases a key allocated by bunny_new_key.
 * @param key The key to release. Passing NULL is accepted by the underlying allocator.
 * @log This function writes a log entry in the "security" log domain.
 * @see bunny_new_key, t_bunny_cipher_key
 *
 * @doc-lang fr
 * @brief Libère une clé allouée par bunny_new_key.
 * @param key La clé à libérer. Transmettre NULL est accepté par l'allocateur sous-jacent.
 * @log Cette fonction écrit une entrée de log dans le domaine "security".
 * @see bunny_new_key, t_bunny_cipher_key
 */
void			bunny_delete_key(t_bunny_cipher_key	*key)
{
  bunny_free(key);
  scream_log_if("%p", "security", key);
}

