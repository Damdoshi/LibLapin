// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2019
//
// Lapin library

#include		"lapin_private.h"

t_bunny_tile_property	*bunny_tilemap_get_properties_from_px(const t_bunny_tilemap	*tmap,
							      const t_bunny_position	*pos,
							      int			z)
{
  int			tile = bunny_tilemap_get_tile_from_px(tmap, pos, z);
  t_bunny_tileset	*ts = bunny_get_tileset_for_tile(tmap, tile);

  return (&ts->tile_properties_id[tile - ts->first_tile]);
}

t_bunny_tile_property	*bunny_map_get_properties(const t_bunny_tilemap		*tmap,
						  const t_bunny_position	*pos,
						  int				z)
{
  int			tile = bunny_tilemap_get_tile(tmap, pos, z);
  t_bunny_tileset	*ts = bunny_get_tileset_for_tile(tmap, tile);

  return (&ts->tile_properties_id[tile - ts->first_tile]);
}

