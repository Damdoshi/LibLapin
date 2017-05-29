// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2017
//
// Lapin library

#include		"lapin.h"

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

uint64_t		bunny_hash(t_bunny_hash			hash,
				   const void			*ptr,
				   size_t			len)
{
  if (hash == BH_MULTIPLIER)
    return (multiplier(ptr, len));
  if (hash == BH_FNV)
    return (fnv(ptr, len));
  return (gl_bunny_my_hash(hash, ptr, len));
}

