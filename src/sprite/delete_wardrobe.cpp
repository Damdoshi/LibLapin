// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

static void		delete_wardrobe(t_bunny_map		*map,
					void			*d)
{
  (void)d;
  bunny_delete_closet(bunny_map_data(map, t_bunny_closet*));
}

void			bunny_delete_wardrobe(t_bunny_map	*w)
{
  bunny_map_foreach(w, delete_wardrobe, NULL);
  bunny_delete_map(w);
}

