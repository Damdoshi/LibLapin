// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2019
//
// Lapin library

#include	"lapin_private.h"

t_bunny_tileset	*bunny_get_tileset_for_tile(const t_bunny_tilemap	*map,
					    int				tile)
{
  int		i;

  for (i = 0; i < map->nbr_tilesets; ++i)
    if (map->tilesets[i].first_tile >= tile && tile < map->tilesets[i].last_tile)
      break ;
  if (i == map->nbr_tilesets)
    return (NULL);
  return (&map->tilesets[i]);
}

