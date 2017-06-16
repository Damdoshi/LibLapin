// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		<avcall.h>
#include		"lapin_private.h"

void			_real_call(const t_bunny_prototype	*function,
				   t_bunny_value		*return_value,
				   size_t			nbr,
				   t_bunny_value		*params)
{
  av_alist		lst;
  size_t		i;

  switch (function->return_value)
    {
    case VOID:
      av_start_void(lst, function->function_ptr);
      break ;
    case INTEGER:
      av_start_longlong(lst, function->function_ptr, &return_value->integer);
      break ;
    case DOUBLE:
      av_start_double(lst, function->function_ptr, &return_value->real);
      break ;
    case STRING:
      av_start_ptr(lst, function->function_ptr, char*, &return_value->any);
      break ;
    case POINTER:
      av_start_ptr(lst, function->function_ptr, void*, &return_value->any);
      break ;
    }
  for (i = 0; i < nbr; ++i)
    switch (function->parameters[i])
      {
      case INTEGER:
	av_longlong(lst, params[i].integer);
	break ;
      case DOUBLE:
	av_double(lst, params[i].real);
	break ;
      case STRING:
	av_ptr(lst, char*, params[i].string);
	break ;
      case POINTER:
	av_ptr(lst, void*, params[i].any);
	break ;
      default:
	break ;
      }
  av_call(lst);
}

