// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include		<string.h>
#include		"lapin_private.h"

extern char		*ini_last_error;

#define			PATTERN		"%p -> %s"

char			*bunny_write_ini(const t_bunny_ini	*ini)
{
  char			*str;

  if ((str = bunny_write_configuration(BC_INI, ini)) == NULL)
    scream_error_if(return (NULL), bunny_errno, PATTERN, "ressource,configuration", ini, str);
  scream_log_if(PATTERN, "ressource,configuration", ini, str);
  return (str);
}

