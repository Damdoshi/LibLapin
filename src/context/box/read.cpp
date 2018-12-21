// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

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
      if (bunny_map_set_data(parent->children, nw->id, nw, NULL) == NULL)
	return (false);
      if (bunny_configuration_getf_node(n, &children, "Children"))
	if (_bunny_read_box(bs, children, nw) == false)
	  return (false);
    }
  return (true);
}

bool			bunny_read_box(t_bunny_box_system	*bs,
				       t_bunny_configuration	*cnf)
{
  if (bunny_configuration_getf_node(cnf, &bs->screen.configuration, "Screen") == false)
    return (false);
  if ((bs->screen.id = bunny_strdup("Screen")) == NULL)
    return (false);
  if ((bs->screen.children = bunny_new_map(string_map)) == NULL)
    {
      bunny_free((char*)bs->screen.id);
      return (false);
    }
  bs->screen.type = BBT_SIMPLE_BOX;
  bs->screen.parent = NULL;
  bs->screen.display = NULL;
  bs->screen.destructor = NULL;
  bs->screen.position.x = 0;
  bs->screen.position.y = 0;
  bs->screen.size.x = bs->head.screen->width;
  bs->screen.size.y = bs->head.screen->height;
  bs->screen.color.full = 0;
  if (_bunny_read_box(bs, cnf, &bs->screen) == false)
    {
      bunny_delete_box(&bs->screen);
      return (false);
    }
  return (true);
}
