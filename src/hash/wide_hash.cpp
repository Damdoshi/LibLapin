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

