// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2017
//
// Lapin library

#include		<stdlib.h>
#include		"lapin_private.h"

void			bunny_foreach_map_bunny_free(t_bunny_map *nod,
						     void	*d)
{
  (void)d;
  bunny_free(bunny_map_data(nod, void*));
}

