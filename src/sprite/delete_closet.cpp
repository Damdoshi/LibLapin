// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

static void		delete_clothe(t_bunny_map		*nod,
				      void			*param)
{
  t_bunny_clothe	*clo;

  (void)param;
  if ((clo = bunny_map_data(nod, t_bunny_clothe*)) != NULL)
    {
      bunny_free((void*)clo->name);
      bunny_delete_clipable(&clo->sprite->clipable);
      bunny_free(clo);
    }
}


/**
 * @doc
 * @doc-symbol bunny_delete_closet
 * @doc-kind function
 * @doc-module sprite
 * @doc-order 440
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Deletes a closet and the clothes it owns.
 * @param closet Closet to delete.
 * @see bunny_load_closet
 *
 * @doc-lang fr
 * @brief Supprime un placard et les vêtements qu'il possède.
 * @param closet Placard à supprimer.
 * @see bunny_load_closet
 */
void			bunny_delete_closet(t_bunny_closet	*closet)
{
  bunny_map_foreach(closet->clothes, delete_clothe, NULL);
  bunny_delete_map(closet->clothes);
  if (closet->name)
    bunny_free((void*)closet->name);
  bunny_free(closet);
}

