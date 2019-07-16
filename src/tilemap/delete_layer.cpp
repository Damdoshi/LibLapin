// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

// Private function
// Does not free *ts itself!

void			bunny_delete_layer(t_bunny_tile_layer		*ts)
{
  if (ts->name)
    bunny_free((char*)ts->name);
  if (ts->tiles)
    bunny_free(ts->tiles);
  if (ts->properties)
    bunny_delete_string_map(ts->properties);
}

