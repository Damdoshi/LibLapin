// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include			<string.h>
#include			"lapin_private.h"

/*
** Turn:
** Oribyt: 01234567 01234567 01234567 01234567 01234567 01234567 01234567 01234567
** Into:
** Tarbyt: 00000000 11111111 22222222 33333333 44444444 55555555 66666666 77777777
**
** A variation may do:
** 01234567 ABCDEFGH IJKLMNOP QRTSUVWX YZabcdef ghijklmn opqrstuv wxyz_()'
** Into:
** 0BKSclu' 1CLUdmvw 2DMVenox etc.
*/

void				__bunny_bytbit(char			*cnt,
					       size_t			len,
					       const t_bunny_cipher_key	*key,
					       bool			cipher)
{
  uint8_t			buf[8];
  size_t			dit;
  size_t			tarbyt;
  size_t			oribyt;

  for (dit = 0; dit + 8 < len; dit += 8)
    {
      memset(&buf[0], 0, sizeof(buf));
      for (tarbyt = 0; tarbyt < 8; ++tarbyt)
	for (oribyt = 0; oribyt < 8; ++oribyt)
	  buf[tarbyt] |= (cnt[oribyt + dit] & (1 << tarbyt)) ? 1 << oribyt : 0;
      memcpy(&cnt[dit], &buf[0], sizeof(buf));
    }
}
