// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2020
//
// LibLapin

#include		"lapin_private.h"

void			bunny_delete_historic_element(t_bunny_historic_element	*elem)
{
  bunny_free(elem->status);
  bunny_free(elem);
}
