// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include			"lapin_private.h"

void				__bunny_caesar(char			*cnt,
					       size_t			len,
					       const t_bunny_key	*key,
					       bool			cipher)
{
  int				i;

  if (cipher)
    for (i = 0; i < len; ++i)
      cnt[i] += key->key[i % key->length];
  else
    for (i = 0; i < len; ++i)
      cnt[i] -= key->key[i % key->length];
}

