// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include		<string.h>
#include		"lapin_private.h"

extern char		*ini_last_error;

t_bunny_ini		*bunny_load_ini(const char		*file)
{
  return (bunny_load_configuration(BC_INI, file, NULL));
}

