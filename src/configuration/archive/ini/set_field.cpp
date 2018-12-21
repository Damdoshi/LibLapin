// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include		<string.h>
#include		"lapin_private.h"

#define			PATTERN		"%p ini, %s scope, %s field, %u index, %s value"

void			bunny_ini_set_field(t_bunny_ini		*ini,
					    const char		*scope,
					    const char		*field,
					    unsigned int	index,
					    const char		*value)
{
  t_bunny_configuration	*cnf = (t_bunny_configuration*)ini;
  bool			create = SmallConf::create_mode;

  SmallConf::create_mode = true;

  if (strcmp(scope, "") != 0)
    {
      if ((cnf = bunny_configuration_get_child(cnf, scope)) == NULL)
	{
	  SmallConf::create_mode = create;
	  scream_error_if
	    (return, bunny_errno, PATTERN,
	     "configuration", ini, scope, field, index, value);
	}
    }
  if ((cnf = bunny_configuration_get_child(cnf, field)) == NULL)
    {
      SmallConf::create_mode = create;
      scream_error_if
	(return, bunny_errno, PATTERN,
	 "configuration", ini, scope, field, index, value);
    }
  if ((cnf = bunny_configuration_get_case(cnf, index)) == NULL)
    {
      SmallConf::create_mode = create;
      scream_error_if
	(return, bunny_errno, PATTERN,
	 "configuration", ini, scope, field, index, value);
    }
  if (value == NULL)
    bunny_delete_configuration(cnf);
  else
    bunny_configuration_set_string(cnf, value);
  SmallConf::create_mode = create;
  scream_log_if(PATTERN, "configuration", ini, scope, field, index, value);
}

