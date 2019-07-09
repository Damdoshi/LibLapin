// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include	"lapin_private.h"

void		bunny_tilemap_set_camera(t_bunny_tilemap		*map,
					 t_bunny_accurate_position	pos)
{
  map->camera.x = pos.x * map->tile_size.x;
  map->camera.y = pos.y * map->tile_size.y;
}

