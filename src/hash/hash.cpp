// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

t_bunny_my_hash		gl_bunny_my_hash;

static uint64_t		multiplier(const void			*ptr,
				   size_t			len)
{
  int64_t		hashout;
  uint8_t		*data;
  size_t		i;

  data = (uint8_t*)ptr;
  hashout = 0xDEADBEEFB15B00B5;
  for (i = 0; i < len; ++i)
    hashout = hashout * 37 + data[i];
  return (hashout);
}

static uint64_t		fnv(const void				*ptr,
			    size_t				len)
{
  int64_t		hashout;
  uint8_t		*data;
  size_t		i;

  data = (uint8_t*)ptr;
  hashout = 0xDEADBEEFB15B00B5;
  for (i = 0; i < len; ++i)
    {
      hashout *= 0xE12381F5387C3214;
      hashout ^= data[i];
    }
  return (hashout);
}

static uint64_t		fnva(const void				*ptr,
			     size_t				len)
{
  int64_t		hashout;
  uint8_t		*data;
  size_t		i;

  data = (uint8_t*)ptr;
  hashout = 0xDEADBEEFB15B00B5;
  for (i = 0; i < len; ++i)
    {
      hashout ^= data[i];
      hashout *= 0xE12381F5387C3214;
    }
  return (hashout);
}

static uint64_t		djb2(const void				*ptr,
			     size_t				len)
{
  uint64_t		hashout;
  uint8_t		*data;
  size_t		i;

  data = (uint8_t*)ptr;
  hashout = 5381;
  for (i = 0; i < len; ++i)
    hashout = ((hashout << 5) + hashout) + data[i];
  return (hashout);
}

static uint64_t		sdbm(const void				*ptr,
			     size_t				len)
{
  uint64_t		hashout;
  uint8_t		*data;
  size_t		i;

  data = (uint8_t*)ptr;
  hashout = 0;
  for (i = 0; i < len; ++i)
    hashout = data[i] + (hashout << 6) + (hashout << 16) - hashout;
  return (hashout);
}

static uint64_t		loselose(const void			*ptr,
				 size_t				len)
{
  uint64_t		hashout;
  uint8_t		*data;
  size_t		i;

  data = (uint8_t*)ptr;
  hashout = 0;
  for (i = 0; i < len; ++i)
    hashout += data[i];
  return (hashout);
}

typedef uint64_t	(*t_bunny_bh_hash)(const void		*ptr,
					   size_t		len);

/**
 * @doc
 * @doc-symbol bunny_hash
 * @doc-kind function
 * @doc-module hash
 * @doc-order 120
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Computes a 64-bit weak hash of a memory block.
 * @description The selected algorithm is applied to ptr for len bytes. If hash is BH_CUSTOM or any greater value, bunny_hash delegates the operation to gl_bunny_my_hash.
 * @param hash The hash algorithm to use.
 * @param ptr The data to hash.
 * @param len The length of ptr in bytes.
 * @return-success The computed digest.
 * @log This function writes a log entry in the "hash" log domain.
 * @see t_bunny_hash_algorithm, t_bunny_hash, bunny_wide_hash, gl_bunny_my_hash
 *
 * @doc-lang fr
 * @brief Calcule un hachage faible de 64 bits sur un bloc mémoire.
 * @description L'algorithme sélectionné est appliqué à ptr pendant len octets. Si hash vaut BH_CUSTOM ou une valeur supérieure, bunny_hash délègue l'opération à gl_bunny_my_hash.
 * @param hash L'algorithme de hachage à utiliser.
 * @param ptr Les données à hacher.
 * @param len La longueur de ptr en octets.
 * @return-success Le condensat calculé.
 * @log Cette fonction écrit une entrée de log dans le domaine "hash".
 * @see t_bunny_hash_algorithm, t_bunny_hash, bunny_wide_hash, gl_bunny_my_hash
 */
uint64_t		bunny_hash(t_bunny_hash_algorithm	hash,
				   const void			*ptr,
				   size_t			len)
{
  static const t_bunny_bh_hash bh_list[BH_CUSTOM] =
    {
      &multiplier,
      &fnv,
      &fnva,
      &djb2,
      &sdbm,
      &loselose
    };
  uint64_t		res;

  if (hash < BH_CUSTOM)
    res = (bh_list[hash](ptr, len));
  else
    res = (gl_bunny_my_hash(hash, ptr, len));
  scream_log_if("%d hash algorithm, %p data, %zu data length -> %lX", "hash", hash, ptr, len, res);
  return (res);
}

