// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

/*
t_bunny_configuration	*bunny_load_configuration(t_bunny_configuration_type		type,
						  t_bunny_configuration			*config,
						  bool					overwrite,
						  ...)
{
  struct bunny_configuration *cnf;
  va_list		lst;

  va_start(lst, overwrite);
  if (config != NULL)
    cnf = (struct bunny_configuration*)config;
  else if ((cnf = __bunny_new_configuration(type, lst)) == NULL)
    return (NULL);
  try
    {
      switch (type)
	{
	case BC_INI:
	  ;
	case BC_DABSIC:
	  ;
	case BC_XML:
	  ;
	case BC_LUA:
	  ;
	case BC_CRUNCH:
	  ;
	  break ;
	case BC_CARROT_SQL:
	  ;
	  break ;
	default:
	  if ((cnf = gl_bunny_my_load_configuration(type, cnf, lst)) == NULL)
	    throw 0;
	  return (cnf);
	}
    }
  catch (...)
    {
      if (config == NULL)
	bunny_delete_configuration(cnf);
    }
  return (cnf);
}

*/

