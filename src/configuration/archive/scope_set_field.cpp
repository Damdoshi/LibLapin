// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include		"lapin_private.h"

#define			PATTERN		"%p scope, %s field, %d index, %s value"

void			bunny_ini_scope_set_field(t_bunny_ini_scope		*sc,
						  const char			*field,
						  unsigned int			index,
						  const char			*value)
{
  t_bunny_configuration	*cnf = (t_bunny_configuration*)sc;
  bool			create = SmallConf::create_mode;

  SmallConf::create_mode = true;
  if ((cnf = bunny_configuration_get_child(cnf, field)) == NULL)
    {
      SmallConf::create_mode = create;
      scream_error_if(return, bunny_errno, PATTERN, "configuration", sc, field, index, value);
    }
  if ((cnf = bunny_configuration_get_case(cnf, index)) == NULL)
    {
      SmallConf::create_mode = create;
      scream_error_if(return, bunny_errno, PATTERN, "configuration", sc, field, index, value);
    }
  if (value == NULL)
    bunny_delete_configuration(cnf);
  else
    bunny_configuration_set_string(cnf, value);
  SmallConf::create_mode = create;
  scream_log_if(PATTERN, "configuration", sc, field, index, value);
}

