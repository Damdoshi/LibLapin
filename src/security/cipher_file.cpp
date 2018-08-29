// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include			"lapin_private.h"

#define				PATTERN		"%s file, %d ciphering algorithm, %p key -> %s"

bool				bunny_cipher_file(const char			*file,
						  t_bunny_ciphering		cip,
						  const t_bunny_cipher_key	*key)
{
  char				*cnt;
  size_t			len;
  bool				ret;

  if (bunny_load_file(file, (void**)&cnt, &len) == false)
    scream_error_if(return (false), bunny_errno, PATTERN, "security", file, cip, key, "false");
  bunny_cipher_data(cnt, len, cip, key);
  ret = bunny_save_file(file, cnt, len);
  len = bunny_errno;
  bunny_free(cnt);
  if (ret == false)
    scream_error_if(return (false), len, PATTERN, "security", file, cip, key, "false");
  scream_log_if(PATTERN, "security", file, cip, key, "true");
  return (true);
}

