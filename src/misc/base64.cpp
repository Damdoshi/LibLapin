// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<stdint.h>
#include		"lapin_private.h"

static const char	*gl_dictionnary =
  "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
  ;
static unsigned char	gl_id[256];

bool			bunny_base64_encode(const void		*_data,
					    size_t		len,
					    char		**out,
					    size_t		*outlen)
{
  static const size_t	terminator[] = {0, 2, 1};
  const char		*data = (const char*)_data;
  size_t		outrep;
  size_t		i, j;
  uint32_t		a, b, c;
  uint32_t		merge;

  if (outlen == NULL)
    {
      outlen = &outrep;
      outrep = 0;
    }

  if (*out != NULL && *outlen >= 4 * ((len + 2) / 3) + 1)
    *outlen = 4 * ((len + 2) / 3);
  else if ((*out = (char*)bunny_malloc((merge = 4 * ((len + 2) / 3)) + 1)) == NULL)
    return (false);
  else
    *outlen = merge;

  for (i = 0, j = 0; i < len; )
    {
      a = i < len ? data[i] & 0xFF : 0;
      i += 1;
      b = i < len ? data[i] & 0xFF : 0;
      i += 1;
      c = i < len ? data[i] & 0xFF : 0;
      i += 1;

      // Generate a 24 bit integer
      merge = a << 16 | b << 8 | c;

      // 0x3F = 0011 1111
      (*out)[j++] = gl_dictionnary[(merge >> 18) & 0x3F];
      (*out)[j++] = gl_dictionnary[(merge >> 12) & 0x3F];
      (*out)[j++] = gl_dictionnary[(merge >>  6) & 0x3F];
      (*out)[j++] = gl_dictionnary[merge & 0x3F];
    }
  for (i = 0; i < terminator[len % 3]; i++)
    (*out)[*outlen - 1 - i] = '=';
  (*out)[*outlen] = '\0';
  return (true);
}

bool			bunny_base64_decode(const char		*data,
					    size_t		len,
					    void		**_out,
					    size_t		*outlen)
{
  static bool		id_ok = 0;
  char			**out = (char**)_out;
  size_t		outrep;
  size_t		i, j;
  uint32_t		a, b, c, d;
  uint32_t		merge;

  // Generate reverse dictionnary map
  if (id_ok == 0)
    {
      id_ok = 1;
      for (i = 0, j = strlen(gl_dictionnary); i < j; ++i)
	gl_id[(int)gl_dictionnary[i]] = i;
    }

  if (outlen == NULL)
    {
      outlen = &outrep;
      outrep = 0;
    }

  if (*out != NULL && *outlen >= len / 4 * 3 + 1)
    *outlen = len / 4 * 3;
  else if ((*out = (char*)bunny_malloc((merge = len / 4 * 3) + 1)) == NULL)
    return (false);
  else
    *outlen = merge;

  for (i = 0, j = 0; i < len && j < *outlen && data[i] && data[i] != '='; )
    if (data[i] != '\n' && data[i] != '\r')
      {
	a = data[i] != '=' ? gl_id[(int)data[i]] : 0;
	i += 1;

	b = data[i] != '=' ? gl_id[(int)data[i]] : 0;
	i += 1;

	c = data[i] != '=' ? gl_id[(int)data[i]] : 0;
	i += 1;

	d = data[i] != '=' ? gl_id[(int)data[i]] : 0;
	i += 1;

	// Generate a 24 bit integer
	merge = a << 18 | b << 12 | c << 6 | d;

	if (j < *outlen)
	  (*out)[j++] = (merge >> 16) & 0xFF;
	if (j < *outlen)
	  (*out)[j++] = (merge >>  8) & 0xFF;
	if (j < *outlen)
	  (*out)[j++] = (merge      ) & 0xFF;
      }
    else
      i += 1;
  (*out)[j] = '\0';
  a = 0;
  while (data[len - a - 1] == '=')
    a += 1;
  *outlen = j - a;
  return (true);
}

bool			bunny_base64_check(const char		*data,
					   size_t		len)
{
  size_t		i, j;

  for (i = 0, j = 0; data[i] && i < len && data[i] != '='; ++i)
    if (
	(data[i] >= 'A' && data[i] <= 'Z')
	||
	(data[i] >= 'a' && data[i] <= 'z')
	||
	(data[i] >= '0' && data[i] <= '9')
	||
	data[i] == '+'
	||
	data[i] == '/'
	)
      j += 1;
    else if (data[i] != '\n' && data[i] != '\r')
      return (false);
  while (j % 4 != 0)
    if (data[i++] != '=')
      return (false);
    else
      j += 1;
  return (true);
}

bool				bunny_read_base64(const char		*data,
						  ssize_t		*i,
						  void			**out,
						  size_t		*outlen)
{
  ssize_t			j = *i;
  ssize_t			k;

  if (bunny_check_text(data, &j, "b64_") == false)
    return (false);
  k = j;
  if (readchar(data, j, gl_dictionnary) == false)
    return (false);
  if (readchar(data, j, "\"") == false)
    return (false);
  bool				ret;

  if ((ret = bunny_base64_decode(data, j - k, out, outlen)) != false)
    *i = k;
  return (ret);
}
