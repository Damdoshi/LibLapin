// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

// Private function
// Does not free *ts itself!

void			bunny_delete_properties(t_bunny_map	*map)
{
  t_bunny_map		**nodmap;

  for (bunny_map_all(map, nodmap))
    bunny_free(bunny_map_data(*nodmap, char*));
  bunny_delete_map(map);
}

