// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include			"lapin_private.h"

void				__bunny_xor(char			*cnt,
					    size_t			len,
					    const t_bunny_cipher_key	*key)
{
  size_t			i;

  for (i = 0; i < len; ++i)
    cnt[i] ^= key->key[i % key->length];
}

