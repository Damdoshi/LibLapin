// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include			"lapin_private.h"

t_bunny_cipher_key		*bunny_new_key(size_t		len)
{
  t_bunny_cipher_key		*key;
  size_t			i;

  if (len == 0)
    return (NULL);
  if ((key = (t_bunny_cipher_key*)bunny_malloc(sizeof(key->length) + len)) == NULL)
    return (NULL);
  key->length = len;
  for (i = 0; i < len; ++i)
    key->key[i] = rand() % 256;
  return (key);
}

