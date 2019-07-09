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
  if (!ts->animated_tiles)
    return ;
  for (int i = 0; i < ts->nbr_animated_tiles; ++i)
    bunny_delete_clipable(&ts->animated_tiles[i]->clipable);
  bunny_free(ts->animated_tiles);
  if (ts->properties)
    bunny_delete_properties(ts->properties);
}

