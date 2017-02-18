// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliothèque Lapin

#include			"lapin_private.h"

void				bunny_ini_field_set_value(t_bunny_ini_field	*field,
							  unsigned int		index,
							  const char		*value)
{
  t_bunny_configuration		*cnf = (t_bunny_configuration*)field;
  bool				create = SmallConf::create_mode;

  SmallConf::create_mode = true;
  if ((cnf = bunny_configuration_get_case(cnf, index)) == NULL)
    {
      SmallConf::create_mode = create;
      return ;
    }
  if (value == NULL)
    bunny_delete_configuration(cnf);
  else
    bunny_configuration_set_string(cnf, value);
  SmallConf::create_mode = create;
}

