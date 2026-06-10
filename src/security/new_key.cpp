// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include			"lapin_private.h"

#define				PATTERN		"%zu -> %p"

/**
 * @doc
 * @doc-symbol bunny_new_key
 * @doc-kind function
 * @doc-module security
 * @doc-order 260
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Allocates and fills a new ciphering key.
 * @description The requested length is rounded up to the next even value because some algorithms read the key by pairs of bytes. The key bytes are filled with rand().
 * @param len The requested key length in bytes. It must be greater than zero.
 * @return-success A newly allocated t_bunny_cipher_key. It must be released with bunny_delete_key.
 * @return-failure NULL if len is zero or if allocation fails.
 * @error EINVAL len is zero.
 * @error ENOMEM The key could not be allocated.
 * @log This function writes log entries in the "security" log domain.
 * @see bunny_delete_key, t_bunny_cipher_key
 *
 * @doc-lang fr
 * @brief Alloue et remplit une nouvelle clé de chiffrement.
 * @description La longueur demandée est arrondie à la valeur paire supérieure car certains algorithmes lisent la clé par paires d'octets. Les octets de clé sont remplis avec rand().
 * @param len La longueur de clé demandée en octets. Elle doit être supérieure à zéro.
 * @return-success Une nouvelle t_bunny_cipher_key allouée. Elle doit être libérée avec bunny_delete_key.
 * @return-failure NULL si len vaut zéro ou si l'allocation échoue.
 * @error EINVAL len vaut zéro.
 * @error ENOMEM La clé n'a pas pu être allouée.
 * @log Cette fonction écrit des entrées de log dans le domaine "security".
 * @see bunny_delete_key, t_bunny_cipher_key
 */
t_bunny_cipher_key		*bunny_new_key(size_t		len)
{
  t_bunny_cipher_key		*key;
  size_t			i;

  len = len % 2 ? len + 1 : len;
  if (len == 0)
    scream_error_if(return (NULL), EINVAL, PATTERN, "security", len, (void*)NULL);
  if ((key = (t_bunny_cipher_key*)bunny_malloc(sizeof(key->length) + len)) == NULL)
    scream_error_if(return (NULL), bunny_errno, PATTERN, "security", len, (void*)NULL);
  key->length = len;
  for (i = 0; i < len; ++i)
    key->key[i] = rand() % 256;
  scream_log_if(PATTERN, "security", len, key);
  return (key);
}

