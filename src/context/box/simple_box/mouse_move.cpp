// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

t_bunny_response	bunny_min_simple_box_dabsic(t_bunny_box_system		*sys,
						    t_bunny_gui_box		*box);
t_bunny_response	bunny_mout_simple_box_dabsic(t_bunny_box_system		*sys,
						     t_bunny_gui_box		*box);

static t_bunny_response	bunny_mmove_simple_box_transfer(t_bunny_position	pos,
							t_bunny_box_system	*sys,
							t_bunny_gui_box		*box)
{
  t_bunny_response	ret;

  (void)pos;
  if (sys->hovered != box)
    {
      if (sys->hovered && sys->hovered->mouse_out)
	if ((ret = bunny_mout_simple_box_dabsic(sys, sys->hovered)) != GO_ON)
	  return (ret);
      if (box->mouse_in)
	if ((ret = bunny_min_simple_box_dabsic(sys, box)) != GO_ON)
	  return (ret);
      sys->hovered = box;
    }
  return (GO_ON);
}

static t_bunny_response	bunny_mmove_simple_box_dabsic(t_bunny_position		pos,
						      t_bunny_box_system	*sys,
						      t_bunny_gui_box		*box)
{
  t_bunny_configuration	*params;
  t_bunny_response	ret;

  if (sys->hovered != box)
    {
      if (sys->hovered && sys->hovered->mouse_out)
	if ((ret = bunny_mout_simple_box_dabsic(sys, sys->hovered)) != GO_ON)
	  return (ret);
      if (box->mouse_in)
	if ((ret = bunny_min_simple_box_dabsic(sys, box)) != GO_ON)
	  return (ret);
      sys->hovered = box;
    }
  if ((params = bunny_new_configuration()) == NULL)
    return (EXIT_ON_ERROR);
  if (bunny_configuration_setf_int(params, (int)pos.x, "[0]") == false ||
      bunny_configuration_setf_int(params, (int)pos.y, "[1]") == false ||
      bunny_configuration_execute(box->mouse_move_node, params, NULL) == false)
    {
      bunny_delete_configuration(params);
      return (EXIT_ON_ERROR);
    }
  bunny_delete_configuration(params);
  return (GO_ON);
}

bool			bunny_box_set_mmove_callback(t_bunny_gui_box		*nw)
{
  nw->mouse_move = NULL;
  nw->mouse_move_node = NULL;
  if (bunny_configuration_getf_node(nw->configuration, &nw->mouse_move_node, "OnMouseMove") == false)
    {
      nw->mouse_move = bunny_mmove_simple_box_transfer;
      return (true);
    }
  SmallConf		&cnf = *(SmallConf*)nw->mouse_move_node;
  SmallConf		&prot = cnf[".prototype"];

  if (prot.Size() != 2)
    return (false);
  if (prot[0].last_type != SmallConf::INTEGER ||
      prot[1].last_type != SmallConf::INTEGER)
    return (false);

  nw->mouse_move = bunny_mmove_simple_box_dabsic;
  return (true);
}
