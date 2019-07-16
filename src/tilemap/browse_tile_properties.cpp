// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include			"lapin_private.h"

bool			bunny_browse_tile_properties(t_bunny_tilemap		*tmap,
						     t_bunny_tile_property_func	f,
						     void			*data)
{
  int			i;

  for (i = 0; i < tmap->nbr_tilesets; ++i)
    {
      t_bunny_tileset	*set = &tmap->tilesets[i];
      int		j;

      for (j = 0; j < set->nbr_tile_properties; ++j)
	{
	  t_bunny_tile_property	*prop = set->tile_properties[j];

	  if (f(tmap, set, prop, data) == false)
	    return (false);
	}
    }
  return (true);
}
