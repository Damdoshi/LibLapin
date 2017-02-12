// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include			"lapin_private.h"

bool				bunny_uncipher_file(const char			*file,
						    t_bunny_ciphering		cip,
						    const t_bunny_cipher_key	*key)
{
  char				*cnt;
  size_t			len;
  bool				ret;

  if (bunny_load_file(file, &cnt, &len) == false)
    return (false);
  bunny_uncipher_data(cnt, len, cip, key);
  ret = bunny_save_file(file, cnt, len);
  bunny_free(cnt);
  return (ret);
}

