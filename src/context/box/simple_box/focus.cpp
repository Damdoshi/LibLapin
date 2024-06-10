// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

static t_bunny_response	bunny_focus_simple_box_dabsic(t_bunny_event_state	state,
						      t_bunny_box_system	*sys,
						      t_bunny_gui_box		*box)
{
  t_bunny_configuration	*cnf;

  (void)sys;
  if ((cnf = bunny_new_configuration()) == NULL)
    return (EXIT_ON_ERROR);
  if (bunny_configuration_setf_int(cnf, (int)state, "[0]") == false ||
      bunny_configuration_execute(box->focus_node, false, cnf) == false)
    {
      bunny_delete_configuration(cnf);
      return (EXIT_ON_ERROR);
    }
  bunny_delete_configuration(cnf);
  return (GO_ON);
}

bool			bunny_box_set_focus_callback(t_bunny_gui_box		*nw)
{
  nw->focus = NULL;
  nw->focus_node = NULL;
  if (bunny_configuration_getf_node(nw->configuration, &nw->focus_node, "OnFocusChange") == false)
    return (true);
  SmallConf		&cnf = *(SmallConf*)nw->focus_node;
  SmallConf		&prot = cnf[".prototype"];

  if (prot.Size() != 1)
    return (false);
  if (prot[0].last_type != SmallConf::INTEGER)
    return (false);
  nw->focus = bunny_focus_simple_box_dabsic;
  return (true);
}

