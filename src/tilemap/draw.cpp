// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include	"lapin_private.h"

bool		__bunny_draw_flat_tilemap(struct bunny_tilemap		*tmap);
bool		__bunny_draw_layer_tilemap(struct bunny_tilemap		*tmap);
bool		__bunny_draw_vector_tilemap(struct bunny_tilemap	*tmap)
{
  (void)tmap;
  return (false);
}

bool		__bunny_draw_tilemap(struct bunny_tilemap		*tmap)
{
  if (tmap->method == BTM_FLAT)
    return (__bunny_draw_flat_tilemap(tmap));
  if (tmap->method == BTM_LAYER)
    return (__bunny_draw_layer_tilemap(tmap));
  if (tmap->method == BTM_VECTOR)
    return (__bunny_draw_vector_tilemap(tmap));
  return (false);
}

