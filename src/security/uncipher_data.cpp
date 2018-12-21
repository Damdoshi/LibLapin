// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include			"lapin_private.h"

void				bunny_uncipher_data(void			*cnt,
						    size_t			len,
						    t_bunny_ciphering		cip,
						    const t_bunny_cipher_key	*key)
{
  scream_log_if
    ("%p data, %zu data length, %d ciphering algorithm, %p key",
     "security",
     cnt, len, cip, key);
  switch (cip)
    {
    case BS_XOR:
      __bunny_xor((char*)cnt, len, key);
      return ;
    case BS_CAESAR:
      __bunny_caesar((char*)cnt, len, key, false);
      return ;
    case BS_SHAKER:
      __bunny_shaker((char*)cnt, len, key, false);
      return ;
    case BS_SWITCH:
      __bunny_switch((char*)cnt, len, key, false);
      return ;
    case BS_BYTBIT:
      __bunny_bytbit((char*)cnt, len, key, false);
      return ;
    case BS_BITSHAKE:
      __bunny_bitshake((char*)cnt, len, key, false);
      return ;
    default:
      gl_bunny_my_uncipher(cip, (char*)cnt, len, key);
    }
}
