// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include		<string.h>
#include		"lapin_private.h"

extern char		*ini_last_error;

char			*bunny_write_ini(const t_bunny_ini	*ini)
{
  return (bunny_write_configuration(BC_INI, ini));
}

