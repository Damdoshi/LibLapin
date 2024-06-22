// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

t_bunny_response	bunny_loop_simple_box_dabsic(t_bunny_box_system		*sys,
						     t_bunny_gui_box		*box,
						     double			delay)
{
  t_bunny_configuration	*cnf;

  (void)sys;
  if ((cnf = bunny_new_configuration()) == NULL)
    return (EXIT_ON_ERROR);
  if (bunny_configuration_setf_double(cnf, delay, "[0]") == false ||
      bunny_configuration_execute(box->loop_node, cnf, NULL) == false)
    {
      bunny_delete_configuration(cnf);
      return (EXIT_ON_ERROR);
    }
  bunny_delete_configuration(cnf);
  return (GO_ON);
}

bool			bunny_box_set_loop_callback(t_bunny_gui_box		*nw)
{
  nw->loop = NULL;
  nw->loop_node = NULL;
  if (bunny_configuration_getf_node(nw->configuration, &nw->loop_node, "Loop") == false)
    return (true);
  SmallConf		&cnf = *(SmallConf*)nw->loop_node;
  SmallConf		&prot = cnf[".prototype"];

  if (prot.Size() != 1)
    return (false);
  if (prot[0].last_type != SmallConf::DOUBLE)
    return (false);
  nw->loop = bunny_loop_simple_box_dabsic;
  return (true);
}
