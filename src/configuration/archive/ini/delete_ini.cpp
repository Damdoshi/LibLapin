// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include		"lapin_private.h"

void			bunny_delete_ini(t_bunny_ini	*ini)
{
  scream_log_if("%p", "configuration", ini);
  bunny_delete_configuration((t_bunny_configuration*)ini);
}

