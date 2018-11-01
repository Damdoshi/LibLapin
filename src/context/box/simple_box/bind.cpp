// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

bool			bunny_bind_simple_box(t_bunny_gui_box		*box)
{
  if (bunny_accurate_position_bind_configuration
      ("Position", &box->position, box->configuration) == false)
    return (false);

  if (bunny_accurate_position_bind_configuration
      ("Size", &box->size, box->configuration) == false)
    return (false);

  if (bunny_color_bind_configuration
      ("Color", &box->color, box->configuration) == BD_ERROR)
    return (false);

  if (bunny_color_bind_configuration
      ("MouseOverColor", &box->hovered_color, box->configuration) == BD_ERROR)
    return (false);

  if (bunny_color_bind_configuration
      ("MouseDownColor", &box->clicked_color, box->configuration) == BD_ERROR)
    return (false);

  if (bunny_color_bind_configuration
      ("FocusedColor", &box->focused_color, box->configuration) == BD_ERROR)
    return (false);

  if (bunny_configuration_bindf_bool(box->configuration, &box->inactive, "Inactive") == false)
    return (false);

  if (bunny_configuration_bindf_bool(box->configuration, &box->hidden, "Hidden") == false)
    return (false);

  return (true);

}

