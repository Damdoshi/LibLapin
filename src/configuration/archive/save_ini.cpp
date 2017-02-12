// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include		"lapin_private.h"

bool			bunny_save_ini(t_bunny_ini		*ini,
				       const char		*file)
{
  return (bunny_save_configuration(BC_INI, file, ini));
}

