// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2019
//
// Lapin Library

#include		"lapin_private.h"

void			bunny_store_monitored_value(void)
{
  std::map<std::string, struct bunny_monitored_value>::iterator it;

  for (it = gl_monitor.begin(); it != gl_monitor.end(); ++it)
    switch (it->second.type)
      {
      case BMT_INTEGER:
	it->second.ihistory.push_back(*(int*)it->second.data);
	break ;
      case BMT_DOUBLE:
	it->second.dhistory.push_back(*(double*)it->second.data);
	break ;
      case BMT_STRING:
	it->second.shistory.push_back((const char*)it->second.data);
	break ;
      }
}

