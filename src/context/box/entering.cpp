// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

t_bunny_response	bunny_box_entering(void			*_box)
{
  t_bunny_box_system	*box = (t_bunny_box_system*)_box;

  (void)box;
  return (GO_ON);
}

