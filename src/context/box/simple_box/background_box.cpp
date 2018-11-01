// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

static bool		set_image(t_bunny_gui_box				*box,
				  const char					*field,
				  t_bunny_picture				**pic)
{
  const char		*str;
  t_bunny_configuration	*cnf;

  *pic = NULL;
  if (bunny_configuration_getf_node(box->configuration, &cnf, field) == false)
    return (true);
  if (bunny_configuration_getf_string(cnf, &str, "."))
    {
      if ((*pic = bunny_load_picture(str)) == NULL)
	return (false);
    }
  else if (bunny_set_clipable_attribute(NULL, pic, &cnf, BCT_PICTURE) == false)
    return (false);
  return (true);
}

bool			bunny_set_background_image(t_bunny_gui_box		*box)
{
  if (set_image(box, "Picture", &box->background) == false)
    return (false);
  if (set_image(box, "MouseOverPicture", &box->hovered_background) == false)
    goto MouseOver;
  if (set_image(box, "MouseDownPicture", &box->clicked_background) == false)
    goto MouseDown;
  if (set_image(box, "FocusedPicture", &box->focused_background) == false)
    goto FocusedPicture;

  return (true);

 FocusedPicture:
  bunny_delete_clipable(box->clicked_background);
 MouseDown:
  bunny_delete_clipable(box->hovered_background);
 MouseOver:
  bunny_delete_clipable(box->background);
  return (false);
}
