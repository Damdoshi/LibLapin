// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

const char		*bunny_ini_scope_name(const t_bunny_ini		*in,
					      const t_bunny_ini_scope	*sc)
{
  const char		*ret;

  (void)in;
  if (strcmp(ret = bunny_configuration_get_name(sc), "@") == 0)
    ret = "";
  scream_log_if("%p ini, %p scope -> %s", "configuration", in, sc, ret);
  return (ret);
}

