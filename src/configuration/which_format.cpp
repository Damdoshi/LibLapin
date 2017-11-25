// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

static const char	*gl_extension[BC_CUSTOM] =
  {
    ".ini",
    ".dab",
    ".dabseq",
    ".dabfun",
    ".expr",
    ".xml",
    ".lua",
    ".csv",
    ".json"
    //
  };

t_bunny_configuration_type bunny_which_format(const char		*file)
{
  int			i, j, k, len;

  for (len = 0; file[len]; ++len);
  for (j = 0; j < BC_CUSTOM; ++j)
    {
      for (k = 0; gl_extension[j][k]; ++k);
      for (i = len; i >= 0 && k >= 0 && gl_extension[j][k] == file[i]; --k, --i);
      if (k < 0)
	break ;
    }
  return ((t_bunny_configuration_type)j);
}

