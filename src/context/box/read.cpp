// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

t_bunny_response	bunny_mbutton_simple_box_transfer(t_bunny_event_state	state,
							  t_bunny_position	pos,
							  t_bunny_mouse_button	button,
							  t_bunny_box_system	*sys,
							  t_bunny_gui_box	*box);

static bool		_bunny_read_box(t_bunny_box_system	*bs,
					t_bunny_configuration	*cnf,
					t_bunny_gui_box		*parent)
{
  t_bunny_configuration	*children;
  t_bunny_gui_box	*nw;
  t_bunny_configuration	*n;
  const char		*str;
  int			i;

  for (bunny_configuration_all_children(cnf, n))
    {
      // Ignore the screen node
      if (n == bs->screen.configuration)
	continue ;
      // Ignore what is not a box.
      if (bunny_configuration_getf_string(n, &str, "Type") == false)
	continue ;

      for (i = 0; i < BBT_CUSTOM_BOX && bunny_strcasecmp(gl_bunny_box_type[i], str); ++i);
      if (i == BBT_CUSTOM_BOX)
	nw = gl_bunny_custom_new_box(parent, n);
      else
	nw = gl_bunny_new_box[i](parent, n);

      if (nw == NULL)
	return (false);
      if (bunny_map_set_data(parent->children, nw->id, nw, void*) == NULL)
	return (false);
      if (bunny_configuration_getf_node(n, &children, "Children"))
	if (_bunny_read_box(bs, children, nw) == false)
	  return (false);
    }
  return (true);
}

/**
 * @doc
 * @doc-symbol bunny_read_box
 * @doc-kind function
 * @doc-module context
 * @doc-order 510
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Builds a GUI box system from an already loaded configuration tree.
 * @param bs Box system to fill.
 * @param cnf Configuration tree describing boxes.
 * @return-success Returns $Ctrue@ on success.
 * @return-failure Returns $Cfalse@ on error.
 * @see t_bunny_box_system
 *
 * @doc-lang fr
 * @brief Construit un système de boîtes GUI depuis un arbre de configuration déjà chargé.
 * @param bs Box system to fill.
 * @param cnf Configuration tree describing boxes.
 * @return-success Renvoie $Ctrue@ en cas de succès.
 * @return-failure Renvoie $Cfalse@ en cas d’erreur.
 * @see t_bunny_box_system
 */
bool			bunny_read_box(t_bunny_box_system	*bs,
				       t_bunny_configuration	*cnf)
{
  struct bunny_box_system *sys = (struct bunny_box_system*)bs;

  if (bunny_configuration_getf_node(cnf, &bs->screen.configuration, "Screen") == false)
    return (false);
  bs->screen.size.x = 0;
  bs->screen.size.y = 0;
  for (size_t i = 0; i < bs->head.nbr_screen; ++i)
    {
      bs->screen.size.x += bs->head.screens[i]->width;
      if (bs->screen.size.y < bs->head.screens[i]->height)
	bs->screen.size.y = bs->head.screens[i]->height;
    }
  if ((sys->picture = bunny_new_picture(bs->screen.size.x, bs->screen.size.y)) == NULL)
    return (false);
  if ((bs->screen.id = bunny_strdup("Screen")) == NULL)
    {
      bunny_delete_clipable(sys->picture);
      return (false);
    }
  if ((bs->screen.children = bunny_new_map(string_map)) == NULL)
    {
      bunny_delete_clipable(sys->picture);
      bunny_free((char*)bs->screen.id);
      return (false);
    }
  bs->screen.type = BBT_SIMPLE_BOX;
  bs->screen.parent = NULL;
  bs->screen.display = NULL;
  bs->screen.destructor = NULL;
  bs->screen.position.x = 0;
  bs->screen.position.y = 0;
  
  bs->screen.color.full = 0;
  bs->focus = NULL;
  bs->hovered = NULL;
  bs->down_clicked = NULL;
  if (_bunny_read_box(bs, cnf, &bs->screen) == false)
    {
      t_bunny_map **node;

      for (bunny_map_all(bs->screen.children, node))
	bunny_delete_box(bunny_map_data(*node, t_bunny_gui_box*));
      bunny_delete_clipable(sys->picture);
      bunny_delete_map(bs->screen.children);
      bunny_free((void*)bs->screen.id);
      return (false);
    }
  return (true);
}

