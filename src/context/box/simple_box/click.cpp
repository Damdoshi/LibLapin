// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

t_bunny_response	bunny_click_simple_box_dabsic(t_bunny_box_system	*sys,
						      t_bunny_gui_box		*box)
{
  t_bunny_configuration	*cnf;

  (void)sys;
  if ((cnf = bunny_new_configuration()) == NULL)
    return (EXIT_ON_ERROR);
  if (bunny_configuration_execute(box->click_node, false, cnf) == false)
    {
      bunny_delete_configuration(cnf);
      return (EXIT_ON_ERROR);
    }
  bunny_delete_configuration(cnf);
  return (GO_ON);
}

bool			bunny_box_set_click_callback(t_bunny_gui_box		*nw)
{
  nw->click = NULL;
  nw->click_node = NULL;
  if (bunny_configuration_getf_node(nw->configuration, &nw->click_node, "OnClick") == false)
    return (true);
  SmallConf		&cnf = *(SmallConf*)nw->click_node;
  SmallConf		&prot = cnf[".parameters"];

  if (prot.Size() != 0)
    return (false);
  nw->click = bunny_click_simple_box_dabsic;
  return (true);
}
