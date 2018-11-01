// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

t_bunny_response	bunny_display_simple_box(t_bunny_box_system		*sys,
						 t_bunny_gui_box		*box,
						 const t_bunny_accurate_position *off);
bool			bunny_bind_simple_box(t_bunny_gui_box			*box);
t_bunny_response	bunny_mmove_simple_box_transfer(t_bunny_position	pos,
							t_bunny_box_system	*sys,
							t_bunny_gui_box		*box);
t_bunny_response	bunny_mmove_simple_box_dabsic(t_bunny_position		pos,
						      t_bunny_box_system	*sys,
						      t_bunny_gui_box		*box);
bool			bunny_box_set_mmove_callback(t_bunny_gui_box		*nw);
t_bunny_response	bunny_mbutton_simple_box_transfer(t_bunny_event_state	state,
							  t_bunny_position	pos,
							  t_bunny_mouse_button	button,
							  t_bunny_box_system	*sys,
							  t_bunny_gui_box	*box);
t_bunny_response	bunny_mbutton_simple_box_dabsic(t_bunny_event_state	state,
							t_bunny_position	pos,
							t_bunny_mouse_button	button,
							t_bunny_box_system	*sys,
							t_bunny_gui_box		*box);
bool			bunny_box_set_mbutton_callback(t_bunny_gui_box		*nw);
bool			bunny_box_set_mout_callback(t_bunny_gui_box		*nw);
bool			bunny_box_set_min_callback(t_bunny_gui_box		*nw);
bool			bunny_set_background_image(t_bunny_gui_box		*box);
bool			bunny_box_set_click_callback(t_bunny_gui_box		*nw);
bool			bunny_box_set_focus_callback(t_bunny_gui_box		*nw);
bool			bunny_box_set_loop_callback(t_bunny_gui_box		*nw);

t_bunny_gui_box		*bunny_new_simple_box(t_bunny_gui_box			*parent,
					      t_bunny_configuration		*cnf)
{
  t_bunny_gui_box	*nw;

  if ((nw = (t_bunny_gui_box*)bunny_new_gui_box(sizeof(*nw), cnf)) == NULL)
    return (NULL);
  nw->type = BBT_SIMPLE_BOX;

  nw->display = bunny_display_simple_box;
  nw->destructor = NULL;

  nw->parent = parent;
  nw->configuration = cnf;

  if (bunny_box_set_mbutton_callback(nw) == false)
    goto Error;
  if (bunny_box_set_mmove_callback(nw) == false)
    goto Error;
  if (bunny_box_set_min_callback(nw) == false)
    goto Error;
  if (bunny_box_set_mout_callback(nw) == false)
    goto Error;
  if (bunny_box_set_focus_callback(nw) == false)
    goto Error;
  if (bunny_box_set_click_callback(nw) == false)
    goto Error;
  if (bunny_box_set_loop_callback(nw) == false)
    goto Error;
  if (bunny_set_background_image(nw) == false)
    goto Error;
  nw->inactive = bunny_configuration_declarativef(nw->configuration, "Inactive");
  nw->hidden = bunny_configuration_declarativef(nw->configuration, "Hidden");

  if (bunny_bind_simple_box(nw) == false)
    goto Error;
  return (nw);

 Error:
  if (nw->background)
    bunny_delete_clipable(nw->background);
  bunny_delete_box(nw);
  return (NULL);
}

