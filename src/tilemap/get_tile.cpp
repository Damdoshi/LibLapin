// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

int			bunny_tilemap_get_tile_from_px(const t_bunny_tilemap	*tmap,
						       const t_bunny_position	*pos,
						       int			z)
{
  int			index;

  index = pos->x / tmap->tile_size.x + (pos->y / tmap->tile_size.y) * tmap->map_size.x;
  return (tmap->layers[z].tiles[index]);
}

int			bunny_tilemap_get_tile(const t_bunny_tilemap	*tmap,
					       const t_bunny_position	*pos,
					       int			z)
{
  return (tmap->layers[z].tiles[pos->x + pos->y * tmap->map_size.x]);
}

