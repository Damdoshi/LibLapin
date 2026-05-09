// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

static void		_bunny_delete_box_rec(t_bunny_map		*map,
					      void			*d)
{
  t_bunny_gui_box	*box = bunny_map_data(map, t_bunny_gui_box*);

  (void)d;
  if (box)
/**
 * @doc
 * @doc-symbol bunny_delete_box
 * @doc-kind function
 * @doc-module context
 * @doc-order 530
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Deletes a GUI box and its children.
 * @param box Box to destroy.
 * @return-success The box tree is released.
 * @see t_bunny_box_system
 *
 * @doc-lang fr
 * @brief Détruit une boîte GUI et ses enfants.
 * @param box Box to destroy.
 * @return-success L’arbre de boîtes est libéré.
 * @see t_bunny_box_system
 */
    bunny_delete_box(box);
}

void			bunny_delete_box(t_bunny_gui_box	*box)
{
  if (box->id)
    bunny_free((char*)box->id);
  if (box->children)
    {
      bunny_map_foreach(box->children, _bunny_delete_box_rec, NULL);
      bunny_delete_map(box->children);
    }

  if (box->focused_background)
    bunny_delete_clipable(box->focused_background);
  if (box->clicked_background)
    bunny_delete_clipable(box->clicked_background);
  if (box->hovered_background)
    bunny_delete_clipable(box->hovered_background);
  if (box->background)
    bunny_delete_clipable(box->background);

  if (box->destructor)
    box->destructor(box);
  bunny_free(box);
}

