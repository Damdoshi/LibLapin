// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

static void		tretval(t_bunny_value				*target,
				const void * const			&ret,
				size_t					s)
{
  memcpy(target, &ret, s);
}

static void		do_call(const t_bunny_prototype			*function,
				t_bunny_value				*return_value,
				size_t					nbr,
				t_bunny_value				*params)
{

  if (nbr == 0)
    {
      void		*(*func)() = (void *(*)())function->function_ptr;

      tretval(return_value, func(), sizeof(*return_value));
      return ;
    }
  else if (nbr == 1)
    {
      void		*(*funci)(int) = (void *(*)(int))function->function_ptr;
      void		*(*funcr)(double) = (void *(*)(double))function->function_ptr;
      void		*(*funcv)(void*) = (void *(*)(void*))function->function_ptr;

      switch (function->parameters[0])
	{
	default:
	case VOID:
	  return ;
	case INTEGER:
	  tretval(return_value, funci(params->integer), sizeof(*return_value)); return ;
	case DOUBLE:
	  tretval(return_value, funcr(params->real), sizeof(*return_value)); return ;
	case STRING:
	case POINTER:
	  tretval(return_value, funcv(params->any), sizeof(*return_value)); return ;
	}
    }
  else if (nbr == 2)
    {
      switch (function->parameters[0])
	{
	default:
	case VOID:
	  return ;
	case INTEGER:
	  {
	    void	*(*funci)(int, int) = (void *(*)(int, int))function->function_ptr;
	    void	*(*funcr)(int, double) = (void *(*)(int, double))function->function_ptr;
	    void	*(*funcv)(int, void*) = (void *(*)(int, void*))function->function_ptr;

	    switch (function->parameters[1])
	      {
	      default:
	      case VOID:
		return ;
	      case INTEGER:
		tretval(return_value, funci(params->integer, params[1].integer), sizeof(*return_value)); return ;
	      case DOUBLE:
		tretval(return_value, funcr(params->integer, params[1].real), sizeof(*return_value)); return ;
	      case POINTER:
	      case STRING:
		tretval(return_value, funcv(params->integer, params[1].any), sizeof(*return_value)); return ;
	      }
	  }
	case DOUBLE:
	  {
	    void	*(*funci)(double, int) = (void *(*)(double, int))function->function_ptr;
	    void	*(*funcr)(double, double) = (void *(*)(double, double))function->function_ptr;
	    void	*(*funcv)(double, void*) = (void *(*)(double, void*))function->function_ptr;

	    switch (function->parameters[1])
	      {
	      default:
	      case VOID:
		return ;
	      case INTEGER:
		tretval(return_value, funci(params->real, params[1].integer), sizeof(*return_value)); return ;
	      case DOUBLE:
		tretval(return_value, funcr(params->real, params[1].real), sizeof(*return_value)); return ;
	      case STRING:
	      case POINTER:
		tretval(return_value, funcv(params->real, params[1].any), sizeof(*return_value)); return ;
	      }
	  }
	case POINTER:
	case STRING:
	  {
	    void	*(*funci)(void*, int) = (void *(*)(void*, int))function->function_ptr;
	    void	*(*funcr)(void*, double) = (void *(*)(void*, double))function->function_ptr;
	    void	*(*funcv)(void*, void*) = (void *(*)(void*, void*))function->function_ptr;

	    switch (function->parameters[1])
	      {
	      default:
	      case VOID:
		return ;
	      case INTEGER:
		tretval(return_value, funci(params->any, params[1].integer), sizeof(*return_value)); return ;
	      case DOUBLE:
		tretval(return_value, funcr(params->any, params[1].real), sizeof(*return_value)); return ;
	      case POINTER:
	      case STRING:
		tretval(return_value, funcv(params->any, params[1].any), sizeof(*return_value)); return ;
	      }
	  }
	}  
    }
}

bool			bunny_plugin_call(t_bunny_plugin		*plugin,
					  const char			*func,
					  t_bunny_value			*return_value,
					  size_t			arrlen,
					  t_bunny_value			*params)
{
  size_t		i;

  for (i = 0; i < plugin->nbr_functions; ++i)
    if (strcmp(plugin->prototypes[i].name, func) == 0)
      {
	if (plugin->prototypes[i].nbrparam != arrlen)
	  return (false);
	do_call(&plugin->prototypes[i], return_value, arrlen, params);
	return (true);
      }
  return (false);
}
					  

bool			bunny_plugin_callv(t_bunny_plugin		*plugin,
					   const char			*func,
					   t_bunny_value		*return_value,
					   ...)
{
  va_list		lst;
  t_bunny_value		val[sizeof(plugin->prototypes[0].parameters) / sizeof(t_bunny_value_type)];
  size_t		i, j;
  size_t		len;

  va_start(lst, return_value);
  for (i = 0; i < plugin->nbr_functions; ++i)
    if (strcmp(plugin->prototypes[i].name, func) == 0)
      {
	for (j = 0, len = plugin->prototypes[i].nbrparam; j < len; ++j)
	  memcpy(&val[i], va_arg(lst, t_bunny_value*), sizeof(val[i]));
	va_end(lst);
	do_call(&plugin->prototypes[i], return_value, len, &val[0]);
	return (true);
      }
  va_end(lst);
  return (false);
}
