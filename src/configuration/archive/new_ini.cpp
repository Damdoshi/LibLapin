// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include		"lapin_private.h"

t_bunny_ini		*bunny_new_ini(void)
{
  t_bunny_ini		*ini = NULL;

  if ((ini = bunny_new_configuration()) == NULL)
    scream_error_if(return (NULL), bunny_errno, "[] -> %p", ini);
  scream_log_if("[] -> %p", ini);
  return (ini);
}

