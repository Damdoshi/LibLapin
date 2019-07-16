// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

// Private function
// Does not free *ts itself!

void			bunny_delete_tileset(t_bunny_tileset		*ts)
{
  if (ts->tileset)
    bunny_delete_clipable(ts->tileset);

  if (ts->animated_tiles)
    {
      for (int i = 0; i < ts->nbr_animated_tiles; ++i)
	bunny_delete_clipable(&ts->animated_tiles[i]->clipable);
      bunny_free(ts->animated_tiles);
    }

  if (ts->tile_properties_id)
    {
      for (int i = 0; i < ts->nbr_tiles; ++i)
	if (ts->tile_properties_id[i].properties)
	  bunny_delete_string_map(ts->tile_properties_id[i].properties);
      bunny_free(ts->tile_properties_id);
    }
  if (ts->tile_properties)
    bunny_free(ts->tile_properties);

  if (ts->properties)
    bunny_delete_string_map(ts->properties);
}

