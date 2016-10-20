// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library
/*
#include		"lapin_private.h"

t_bunny_configuration	*__bunny_new_configuration(t_bunny_configuration_type		type,
						   va_list				lst)
{
  struct bunny_configuration *cnf;
  int			i;
  
  if ((cnf = bunny_calloc(1, sizeof(*cnf))) == NULL)
    return (NULL);
  try
    {
      switch ((cnf->type = type))
	{
	case BC_DABSIC:
	  cnf->configuration = new hbs::Dabsic;
	  break ;
	case BC_LUA:
	  cnf->configuration = new hbs::Lua;
	  break ;
	case BC_CARROT_SQL:
	  cnf->configuration = new hbs::Configuration;
	  for (i = 0; i < sizeof(cnf->data) / sizeof(cnf->data[i]); ++i)
	    if ((cnf->data[i] = strdup(va_arg(lst, char*))) == NULL)
	      throw 0;
	  break ;
	default:
	  cnf->configuration = new hbs::Configuration;
	  break ;
	}
    }
  catch (...)
    {
      for (i = 0; i < sizeof(cnf->data) / sizeof(cnf->data[i]); ++i)
	if (cnf->data[i] != NULL)
	  free(cnf->data[i]);
      if (cnt->configuration != NULL)
	delete cnf->configuration;
      bunny_free(cnf);
      return (NULL);
    }
  cnf->name = NULL;
  cnf->value = NULL;
  return ((t_bunny_configuration*)cnf);
}

t_bunny_configuration	*bunny_new_configuration(t_bunny_configuration_type		type,
						 ...)
{
  t_bunny_configuration	*cnf;
  va_list		lst;

  va_start(lst, type);
  cnf = __bunny_new_configuration(type, lst);
  va_end(lst);
  return (cnf);
}

*/
