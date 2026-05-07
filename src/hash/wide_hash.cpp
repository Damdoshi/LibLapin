// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
//
// Lapin library

#include		"lapin_private.h"

static uint8_t		squash(t_bunny_hash		h)
{
  uint8_t		*ptr = (uint8_t*)&h;
  uint8_t		res = 0;

  for (size_t i = 0; i < sizeof(h); ++i)
    res ^= ptr[i];
  return (res);
}

/**
 * @doc
 * @doc-symbol bunny_wide_hash
 * @doc-kind function
 * @doc-module hash
 * @doc-order 180
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Computes a weak digest of arbitrary output size.
 * @description The function repeatedly derives bytes from bunny_hash and writes storage_len bytes into storage. It is useful when a fixed 64-bit digest is not large enough, but it remains a weak hash and must not be used for security.
 * @param hash The hash algorithm to use.
 * @param to_hash The data to hash.
 * @param to_hash_len The length of to_hash in bytes.
 * @param storage The memory area where the digest is written.
 * @param storage_len The number of bytes to write into storage.
 * @see t_bunny_hash_algorithm, t_bunny_hash, bunny_hash
 *
 * @doc-lang fr
 * @brief Calcule un condensat faible d'une taille de sortie arbitraire.
 * @description La fonction dérive répétitivement des octets depuis bunny_hash et écrit storage_len octets dans storage. Elle est utile lorsqu'un condensat fixe de 64 bits n'est pas assez grand, mais elle reste un hachage faible et ne doit pas être utilisée pour la sécurité.
 * @param hash L'algorithme de hachage à utiliser.
 * @param to_hash Les données à hacher.
 * @param to_hash_len La longueur de to_hash en octets.
 * @param storage La zone mémoire dans laquelle le condensat est écrit.
 * @param storage_len Le nombre d'octets à écrire dans storage.
 * @see t_bunny_hash_algorithm, t_bunny_hash, bunny_hash
 */
void			bunny_wide_hash(t_bunny_hash_algorithm hash,
					const void	*to_hash,
					size_t		hlen,
					void		*storage,
					size_t		slen)
{
  char			*out = (char*)storage;
  t_bunny_hash		ohash[2];
  size_t		i;

  ohash[0] = ohash[1] = bunny_hash(hash, to_hash, hlen);
  for (i = 0; i < slen; ++i)
    {
      out[i] = squash(ohash[0]);
      ohash[0] = bunny_hash(hash, ohash, sizeof(ohash));
      if ((i & 7) == 7 || (out[i] & 3) == 3)
	ohash[1] ^= ohash[0];
    }
}

