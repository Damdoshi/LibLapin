// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

//
// 111100001100 => 100010001010
//

void			__bunny_switch(char				*cnt,
				       size_t				len,
				       const t_bunny_cipher_key		*key,
				       bool				cipher)
{
  size_t		blen = len * 8;
  size_t		i;
  bool			previous_bit;

  (void)key;
  if (len == 0)
    return ;
  previous_bit = bunny_bitfield_get(cnt, 0);
  if (cipher)
    for (i = 1; i < blen; ++i)
      if (previous_bit != bunny_bitfield_get(cnt, i))
	{
	  previous_bit = bunny_bitfield_get(cnt, i);
	  bunny_bitfield_set(cnt, i);
	}
      else
	bunny_bitfield_clr(cnt, i);
  else
    for (i = 1; i < blen; ++i)
      {
	if (bunny_bitfield_get(cnt, i) == 1)
	  previous_bit = !previous_bit;
	if (previous_bit)
	  bunny_bitfield_set(cnt, i);
	else
	  bunny_bitfield_clr(cnt, i);
      }
}

