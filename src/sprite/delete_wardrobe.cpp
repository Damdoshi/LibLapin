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


/**
 * @doc
 * @doc-symbol bunny_delete_wardrobe
 * @doc-kind function
 * @doc-module sprite
 * @doc-order 460
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Deletes a wardrobe map and its closets.
 * @param wardrobe Wardrobe map to delete.
 * @see bunny_new_wardrobe
 *
 * @doc-lang fr
 * @brief Supprime une map de garde-robe et ses placards.
 * @param wardrobe Map de garde-robe à supprimer.
 * @see bunny_new_wardrobe
 */
void			bunny_delete_wardrobe(t_bunny_map	*w)
{
  bunny_map_foreach(w, delete_wardrobe, NULL);
  bunny_delete_map(w);
}

