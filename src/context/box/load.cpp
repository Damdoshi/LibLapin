// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

bool			bunny_load_box(t_bunny_box_system	*bs,
				       const char		*file,
				       t_bunny_configuration	*env)
{
  t_bunny_configuration	*cnf;
  bool			ret;

  if ((cnf = bunny_open_configuration(file, env)) == NULL)
    return (false);
  ret = bunny_read_box(bs, cnf);
  if (!env)
    bunny_delete_configuration(cnf);
  return (ret);
}

