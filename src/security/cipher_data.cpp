// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include			"lapin_private.h"

void				bunny_cipher_data(void			*cnt,
						  size_t		len,
						  t_bunny_ciphering	cip,
						  const t_bunny_key	*key)
{
  bool				ret;

  switch (cip)
    {
    case BS_XOR:
      __bunny_xor(cnt, len, key);
      return ;
    case BS_CAESAR:
      __bunny_caesar(cnt, len, key, true);
      return ;
    case BS_SHAKER:      
      __bunny_shaker(cnt, len, key, true);
      return ;
    default:
      gl_bunny_my_cipher(cnt, len, key);
    }
}

