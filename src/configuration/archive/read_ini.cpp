// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include		<string.h>
#include		"lapin_private.h"

extern char		*ini_last_error;

t_bunny_ini		*bunny_read_ini(const char		*str)
{
  return (bunny_read_configuration(BC_INI, str, NULL));
}
