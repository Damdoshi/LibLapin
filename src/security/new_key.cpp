// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include			"lapin_private.h"

#define				PATTERN		"%zu -> %p"

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

