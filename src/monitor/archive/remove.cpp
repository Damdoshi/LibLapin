// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin Library

#include		"lapin_private.h"

bool			bunny_remove_monitored_value(const char		*name)
{
  std::map<std::string, struct bunny_monitored_value>::iterator		it;

  if (name == NULL)
    {
      gl_monitor.clear();
      return (true);
    }
  if ((it = gl_monitor.find(std::string(name))) == gl_monitor.end())
    {
      bunny_errno = BE_CANNOT_FIND_ELEMENT;
      return (false);
    }
  gl_monitor.erase(it);
  return (true);
}

