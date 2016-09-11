// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include		"lapin_private.h"

char			*ini_last_error;

const char		*bunny_ini_get_error(void)
{
  return (ini_last_error);
}

