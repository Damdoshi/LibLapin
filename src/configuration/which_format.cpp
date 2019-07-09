// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

static const char	*gl_extension[BC_CUSTOM][8] =
  {
    {".ini", NULL},
    {".dab", ".sic", ".dabsic", NULL},
    {".dabseq", NULL},
    {".dabfun", NULL},
    {".expr", NULL},
    {".xml", ".tmx", NULL},
    {".lua", NULL},
    {".csv", NULL},
    {".json", NULL},
    {".lisp", ".el", NULL}
    //
  };

t_bunny_configuration_type bunny_which_format(const char		*file)
{
  size_t		flen, elen;
  size_t		i, j;

  flen = strlen(file);
  for (i = 0; i < NBRCELL(gl_extension); ++i)
    for (j = 0; j < NBRCELL(gl_extension[i]) && gl_extension[i][j]; ++j)
      {
	elen = strlen(gl_extension[i][j]);
	if (flen < elen)
	  continue ;
	if (strcmp(&file[flen - elen], gl_extension[i][j]))
	  continue ;
	return ((t_bunny_configuration_type)i);
      }
  return (BC_CUSTOM);
}

