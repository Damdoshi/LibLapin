// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin Library

#include		"lapin_private.h"

bool			_bunny_add_monitored_value(const char		*name,
						   t_bunny_monitored_type type,
						   const void		*ptr)
{
  struct bunny_monitored_value v;

  try
    {
      v.type = type;
      v.data = ptr;
      gl_monitor[std::string(name)] = v;
    }
  catch (...)
    {
      return (false);
    }
  return (true);
}

