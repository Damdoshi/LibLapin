// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

/* cette fonction revient a faire un xor... c'est naze. Cette fonction de transformation
   devrait peut etre ne pas utiliser de clef... */
#warning lel, this is a manual xor. It sucks, remove it.
static bool		byte_digest(bool				original_byte,
				    uint8_t				local_key)
{
  size_t		i;

  for (i = 0; i < sizeof(local_key) * 8; ++i)
    if (bunny_auto_bitfield_get(local_key, i))
      original_byte = !original_byte;
  return (original_byte);
}

static bool		get_bit(char					*cnt,
				size_t					i,
				const t_bunny_cipher_key		*key)
{
  return (byte_digest(bunny_bitfield_get(cnt, i), key->key[i % key->length]));
}

void			*__bunny_switch(char				*cnt,
					size_t				len,
					const t_bunny_cipher_key	*key,
					bool				cipher)
{
  size_t		blen = len * 8;
  bool			first_bit;

  first_bit = get_bit(cnt, 0, key);
#warning not implemented
  return (NULL);
}

