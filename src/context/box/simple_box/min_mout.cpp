// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

t_bunny_response	bunny_min_simple_box_dabsic(t_bunny_box_system		*sys,
						    t_bunny_gui_box		*box)
{
  t_bunny_configuration	*cnf;

  (void)sys;
  if ((cnf = bunny_new_configuration()) == NULL)
    return (EXIT_ON_ERROR);
  if (bunny_configuration_execute(box->mouse_in_node, false, cnf) == false)
    {
      bunny_delete_configuration(cnf);
      return (EXIT_ON_ERROR);
    }
  bunny_delete_configuration(cnf);
  return (GO_ON);
}

bool			bunny_box_set_min_callback(t_bunny_gui_box		*nw)
{
  nw->mouse_in = NULL;
  nw->mouse_in_node = NULL;
  if (bunny_configuration_getf_node(nw->configuration, &nw->mouse_in_node, "OnMouseIn") == false)
    return (true);
  SmallConf		&cnf = *(SmallConf*)nw->mouse_in_node;
  SmallConf		&prot = cnf[".parameters"];

  if (prot.Size() != 0)
    return (false);
  nw->mouse_in = bunny_min_simple_box_dabsic;
  return (true);
}

t_bunny_response	bunny_mout_simple_box_dabsic(t_bunny_box_system		*sys,
						     t_bunny_gui_box		*box)
{
  t_bunny_configuration	*cnf;

  (void)sys;
  if ((cnf = bunny_new_configuration()) == NULL)
    return (EXIT_ON_ERROR);
  if (bunny_configuration_execute(box->mouse_out_node, false, cnf) == false)
    {
      bunny_delete_configuration(cnf);
      return (EXIT_ON_ERROR);
    }
  bunny_delete_configuration(cnf);
  return (GO_ON);
}

bool			bunny_box_set_mout_callback(t_bunny_gui_box		*nw)
{
  nw->mouse_out = NULL;
  nw->mouse_out_node = NULL;
  if (bunny_configuration_getf_node(nw->configuration, &nw->mouse_out_node, "OnMouseOut") == false)
    return (true);
  SmallConf		&cnf = *(SmallConf*)nw->mouse_out_node;
  SmallConf		&prot = cnf[".parameters"];

  if (prot.Size() != 0)
    return (false);
  nw->mouse_out = bunny_mout_simple_box_dabsic;
  return (true);
}

