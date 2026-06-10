// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include			"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_cipher_data
 * @doc-kind function
 * @doc-module security
 * @doc-order 340
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Ciphers a memory buffer in place.
 * @description The selected algorithm is applied directly to data for datalen bytes. The buffer size is not changed. If ciphering is BS_CUSTOM or any greater value, gl_bunny_my_cipher is called.
 * @param data The buffer to cipher.
 * @param datalen The length of data in bytes.
 * @param ciphering The ciphering algorithm to use.
 * @param key The key used by the algorithm. Some algorithms ignore it.
 * @log This function writes a log entry in the "security" log domain.
 * @see bunny_uncipher_data, bunny_cipher_file, t_bunny_ciphering, gl_bunny_my_cipher
 *
 * @doc-lang fr
 * @brief Chiffre un tampon mémoire sur place.
 * @description L'algorithme sélectionné est appliqué directement à data pendant datalen octets. La taille du tampon n'est pas modifiée. Si ciphering vaut BS_CUSTOM ou une valeur supérieure, gl_bunny_my_cipher est appelé.
 * @param data Le tampon à chiffrer.
 * @param datalen La longueur de data en octets.
 * @param ciphering L'algorithme de chiffrement à utiliser.
 * @param key La clé utilisée par l'algorithme. Certains algorithmes l'ignorent.
 * @log Cette fonction écrit une entrée de log dans le domaine "security".
 * @see bunny_uncipher_data, bunny_cipher_file, t_bunny_ciphering, gl_bunny_my_cipher
 */
void				bunny_cipher_data(void				*cnt,
						  size_t			len,
						  t_bunny_ciphering		cip,
						  const t_bunny_cipher_key	*key)
{
  scream_log_if("%p data, %zu data length, %d ciphering algorithm, %p key", "security", cnt, len, cip, key);
  switch (cip)
    {
    case BS_XOR:
      __bunny_xor((char*)cnt, len, key);
      return ;
    case BS_CAESAR:
      __bunny_caesar((char*)cnt, len, key, true);
      return ;
    case BS_SHAKER:
      __bunny_shaker((char*)cnt, len, key, true);
      return ;
    case BS_SWITCH:
      __bunny_switch((char*)cnt, len, key, true);
      return ;
    case BS_BYTBIT:
      __bunny_bytbit((char*)cnt, len, key, true);
      return ;
    case BS_BITSHAKE:
      __bunny_bitshake((char*)cnt, len, key, true);
      return ;
    case BS_BITROTATE:
      __bunny_bitrotate((char*)cnt, len, key, true);
      return ;
    default:
      gl_bunny_my_cipher(cip, (char*)cnt, len, key);
    }
}
