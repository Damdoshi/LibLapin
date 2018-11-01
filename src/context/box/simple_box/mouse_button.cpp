// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

t_bunny_response	bunny_click_simple_box_dabsic(t_bunny_box_system	*sys,
						      t_bunny_gui_box		*box);

t_bunny_response	bunny_mbutton_simple_box_transfer(t_bunny_event_state	state,
							  t_bunny_position	pos,
							  t_bunny_mouse_button	button,
							  t_bunny_box_system	*sys,
							  t_bunny_gui_box	*box)
{
  t_bunny_response	ret;

  (void)state;
  (void)pos;
  (void)button;
  if (state == GO_DOWN)
    {
      if (box->focus)
	sys->focus = box;
      sys->down_clicked = box;
    }
  else if (state == GO_UP)
    {
      if (sys->down_clicked == box && box->click)
	if ((ret = bunny_click_simple_box_dabsic(sys, box)) != GO_ON)
	  return (ret);
      sys->down_clicked = NULL;
    }
  return (GO_ON);
}

static t_bunny_response	bunny_mbutton_simple_box_dabsic(t_bunny_event_state	state,
							t_bunny_position	pos,
							t_bunny_mouse_button	button,
							t_bunny_box_system	*sys,
							t_bunny_gui_box		*box)
{
  t_bunny_configuration	*params;
  t_bunny_response	ret;

  if (state == GO_DOWN)
    {
      if (box->focus)
	sys->focus = box;
      sys->down_clicked = box;
    }
  else if (state == GO_UP)
    {
      if (sys->down_clicked == box && box->click)
	if ((ret = bunny_click_simple_box_dabsic(sys, box)) != GO_ON)
	  return (ret);
      sys->down_clicked = NULL;
    }
  if ((params = bunny_new_configuration()) == NULL)
    return (EXIT_ON_ERROR);
  if (bunny_configuration_setf_int(params, (int)state, "[0]") == false ||
      bunny_configuration_setf_int(params, (int)pos.x, "[1]") == false ||
      bunny_configuration_setf_int(params, (int)pos.y, "[2]") == false ||
      bunny_configuration_setf_int(params, (int)button, "[3]") == false ||
      bunny_configuration_execute(box->mouse_button_node, false, params) == false)
    {
      bunny_delete_configuration(params);
      return (EXIT_ON_ERROR);
    }
  bunny_delete_configuration(params);
  return (GO_ON);
}

bool			bunny_box_set_mbutton_callback(t_bunny_gui_box		*nw)
{
  nw->mouse_button = NULL;
  nw->mouse_button_node = NULL;
  if (bunny_configuration_getf_node(nw->configuration, &nw->mouse_button_node, "OnMouseButton") == false)
    {
      nw->mouse_button = bunny_mbutton_simple_box_transfer;
      return (true);
    }
  SmallConf		&cnf = *(SmallConf*)nw->mouse_button_node;
  SmallConf		&prot = cnf[".parameters"];

  if (prot.Size() != 4)
    return (false);
  if (prot[0].last_type != SmallConf::INTEGER ||
      prot[1].last_type != SmallConf::INTEGER ||
      prot[2].last_type != SmallConf::INTEGER ||
      prot[3].last_type != SmallConf::INTEGER)
    return (false);

  nw->mouse_button = bunny_mbutton_simple_box_dabsic;
  return (true);
}
