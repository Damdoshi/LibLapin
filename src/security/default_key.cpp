// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include				<string.h>
#include				<stdint.h>
#include				"lapin_private.h"

typedef struct				s_bunny_default_key
{
  int32_t				length;
  char					key[128];
}					t_bunny_default_key;

t_bunny_default_key			gl_bunny_default_key[2] =
  {
    {
      128,
      {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
      }
    },
    {
      128,
      {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
      }
    }
  };

static void				funk_shift(char			*b,
						   char			shift)
{
  uint32_t				c;

  c = ((uint32_t)*b) << 8;
  if (shift > 0)
    {
      c <<= shift;
      c &= 0x00FF0000;
      c >>= 16;
      *b = (((uint32_t)(*b << shift)) & 0xFF) | c;
    }
  else if (shift < 0)
    {
      c >>= -shift;
      c &= 0x000000FF;
      *b = (((uint32_t)(*b >> -shift)) & 0xFF) | c;
    }
}

static void				funk_swap(char			*a,
						  char			*b,
						  bool			z)
{
  char					c, d;
  
  if (z == false)
    {
      c = (*a & 0xF0) >> 4;
      *a &= 0x0F;
      
      d = (*b & 0x0F) << 4;
      *b &= 0xF0;

      *a |= d;
      *b |= c;
    }
  else
    funk_swap(b, a, false);
}

static const t_bunny_default_key	*twist_key(t_bunny_default_key	*inkey,
						   t_bunny_default_key	*outkey)
{
  size_t				pass;
  int					i;

  if (gl_bunny_my_key_twist != NULL)
    return ((t_bunny_default_key*)gl_bunny_my_key_twist((t_bunny_cipher_key*)inkey, (t_bunny_cipher_key*)outkey));
  memcpy(&outkey->key[0], &inkey->key[0], outkey->length);
  for (pass = 2; pass < 6; ++pass)
    for (i = 0; i < inkey->length; ++i)
      {
	funk_swap(&outkey->key[i], &outkey->key[(i * pass) % outkey->length], i % 2);
	funk_shift(&outkey->key[i], i % 4);
      }
  return (outkey);
}

const t_bunny_cipher_key		*bunny_default_key(void)
{
  int					i;

  for (i = 0; i < gl_bunny_default_key[0].length; ++i)
    if (gl_bunny_default_key[0].key[i] != 0)
      return ((t_bunny_cipher_key*)twist_key(&gl_bunny_default_key[0], &gl_bunny_default_key[1]));
  return ((t_bunny_cipher_key*)&gl_bunny_default_key[0]);
}
