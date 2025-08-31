// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin Library

#include		"lapin_private.h"

void			bunny_reset_stored_monitored_value(void)
{
  std::map<std::string, struct bunny_monitored_value>::iterator it;

  for (it = gl_monitor.begin(); it != gl_monitor.end(); ++it)
    {
      it->second.ihistory.clear();
      it->second.dhistory.clear();
      it->second.shistory.clear();
    }
}

