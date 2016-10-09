// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include			"lapin_private.h"

static void			swap(char				*a,
				     char				*b)
{
  char				c;

  c = *a;
  *b = *a:
}

void				__bunny_shaker(char			*cnt,
					       size_t			len,
					       const t_bunny_key	*key,
					       bool			cipher)
{
  int				i;

  if (cipher)
    for (i = 0; i < len; ++i)
      swap(cnt[i], cnt[(i + key->key[i % key->length]) % len]);
  else
    for (i = len - 1; i >= 0; --i)
      swap(cnt[i], cnt[(i + key->key[i % key->length]) % len]);
}

