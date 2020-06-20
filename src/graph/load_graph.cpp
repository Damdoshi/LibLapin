// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2020
//
// LibLapin

#include		"lapin_private.h"

t_bunny_graph		*bunny_load_graph(const char		*file)
{
  t_bunny_configuration	*cnf;
  t_bunny_graph		*grp;

  if ((cnf = bunny_open_configuration(file, NULL)) == NULL)
    return (NULL);
  if ((grp = bunny_read_graph(cnf)) == NULL)
    bunny_delete_configuration(cnf);
  else
    grp->own_configuration = true;
  return (grp);
}

