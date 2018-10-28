// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

static t_bunny_response	display_simple_box(t_bunny_box_system		*sys,
					   t_bunny_gui_box		*box,
					   const t_bunny_accurate_position *off)
{
  if (box->color.full == 0)
    return (GO_ON);
  t_bunny_accurate_position n = {off->x + box->position.x, off->y + box->position.y};
  t_bunny_vertex_array	*vx;

  vx = (t_bunny_vertex_array*)bunny_alloca(sizeof(vx->length) + 4 * sizeof(vx->vertex[0]));
  vx->length = 4;

  vx->vertex[0].pos.x = n.x;
  vx->vertex[0].pos.y = n.y;
  vx->vertex[0].color = box->color.full;

  vx->vertex[1].pos.x = n.x + box->size.x;
  vx->vertex[1].pos.y = n.y;
  vx->vertex[1].color = box->color.full;

  vx->vertex[2].pos.x = n.x + box->size.x;
  vx->vertex[2].pos.y = n.y + box->size.y;
  vx->vertex[2].color = box->color.full;

  vx->vertex[3].pos.x = n.x;
  vx->vertex[3].pos.y = n.y + box->size.y;
  vx->vertex[3].color = box->color.full;

  bunny_set_geometry(sys->head.screen, BGY_QUADS, vx, NULL);
  bunny_freea(vx);

  return (GO_ON);
}

static bool		bind_simple_box(t_bunny_gui_box		*box)
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

  return (true);

}

static t_bunny_response	mbutton_simple_box_dabsic(t_bunny_event_state	state,
						  t_bunny_position	pos,
						  t_bunny_mouse_button	button,
						  t_bunny_box_system	*sys,
						  t_bunny_gui_box	*box)
{
  t_bunny_configuration	*params;

  if ((params = bunny_new_configuration()) == NULL)
    return (EXIT_ON_ERROR);
  if (state == GO_DOWN)
    sys->focus = box;
  if (bunny_configuration_setf_int(params, (int)state, "[0]") == false ||
      bunny_configuration_setf_int(params, (int)pos.x, "[1]") == false ||
      bunny_configuration_setf_int(params, (int)pos.y, "[2]") == false ||
      bunny_configuration_setf_int(params, (int)button, "[3]") == false ||
      bunny_configuration_execute(box->mouse_button_node, false, params) == false)
    return (EXIT_ON_ERROR);
  return (GO_ON);
}

static t_bunny_response	mmove_simple_box_dabsic(t_bunny_position	pos,
						t_bunny_box_system	*sys,
						t_bunny_gui_box		*box)
{
  t_bunny_configuration	*params;

  (void)sys;
  if ((params = bunny_new_configuration()) == NULL)
    return (EXIT_ON_ERROR);
  if (bunny_configuration_setf_int(params, (int)pos.x, "[0]") == false ||
      bunny_configuration_setf_int(params, (int)pos.y, "[1]") == false ||
      bunny_configuration_execute(box->mouse_move_node, false, params) == false)
    return (EXIT_ON_ERROR);
  return (GO_ON);
}

static bool		set_mbutton_callback(t_bunny_gui_box		*nw)
{
  nw->mouse_button = NULL;
  nw->mouse_button_node = NULL;
  if (bunny_configuration_getf_node(nw, &nw->mouse_button_node, "OnMouseButton") == false)
    return (true);
  SmallConf		&cnf = *(SmallConf*)nw->mouse_button_node;
  SmallConf		&prot = cnf[".parameters"];

  if (prot.Size() != 4)
    return (false);
  if (prot[0].last_type != SmallConf::INTEGER ||
      prot[1].last_type != SmallConf::INTEGER ||
      prot[2].last_type != SmallConf::INTEGER ||
      prot[3].last_type != SmallConf::INTEGER)
    return (false);

  nw->mouse_button = mbutton_simple_box_dabsic;
  return (true);
}

static bool		set_mmove_callback(t_bunny_gui_box		*nw)
{
  nw->mouse_move = NULL;
  nw->mouse_move_node = NULL;
  if (bunny_configuration_getf_node(nw, &nw->mouse_move_node, "OnMouseMove") == false)
    return (true);
  SmallConf		&cnf = *(SmallConf*)nw->mouse_move_node;
  SmallConf		&prot = cnf[".parameters"];

  if (prot.Size() != 2)
    return (false);
  if (prot[0].last_type != SmallConf::INTEGER ||
      prot[1].last_type != SmallConf::INTEGER)
    return (false);

  nw->mouse_move = mmove_simple_box_dabsic;
  return (true);
}

t_bunny_gui_box		*bunny_new_simple_box(t_bunny_gui_box		*parent,
					      t_bunny_configuration	*cnf)
{
  t_bunny_gui_box	*nw;

  if ((nw = (t_bunny_gui_box*)bunny_new_gui_box(sizeof(*nw), cnf)) == NULL)
    return (NULL);
  nw->type = BBT_SIMPLE_BOX;

  nw->display = display_simple_box;
  nw->destructor = NULL;

  nw->parent = parent;
  nw->configuration = cnf;
  if (set_mbutton_callback(nw) == false)
    goto Error;
  if (set_mmove_callback(nw) == false)
    goto Error;

  if (bind_simple_box(nw) == false)
    goto Error;
  return (nw);

 Error:
  bunny_delete_box(nw);
  return (NULL);
}

