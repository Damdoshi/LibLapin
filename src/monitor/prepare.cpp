// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin Library

#include		<string.h>
#include		"lapin_private.h"

ssize_t			_bunny_monitor_prepare_buffer(char		*buf,
						      ssize_t		len,
						      const char	*n)
{
  std::map<std::string, struct bunny_monitored_value>::iterator		it;
  ssize_t		acc;
  ssize_t		i;

  if (n == NULL)
    {
      for (it = gl_monitor.begin(), acc = 0; it != gl_monitor.end(); ++it)
	switch (it->second.type)
	  {
	  case BMT_INTEGER:
	    acc += snprintf(&buf[acc], len - acc, "%s: %d\n",
			    it->first.c_str(), *(int*)it->second.data);
	    break ;
	  case BMT_DOUBLE:
	    acc += snprintf(&buf[acc], len - acc, "%s: %lf\n",
			    it->first.c_str(), *(double*)it->second.data);
	    break ;
	  case BMT_STRING:
	    acc += snprintf(&buf[acc], len - acc, "%s: %s\n",
			    it->first.c_str(), (const char*)it->second.data);
	    break ;
	  }
      return (acc);
    }

  for (i = 0; n[i]; ++i);
  if (i == 0 || n[i - 1] == '*')
    {
      i = (i == 0 ? 0 : i - 1);
      for (it = gl_monitor.begin(), acc = 0; it != gl_monitor.end(); ++it)
	if (strncmp(it->first.c_str(), n, i) == 0)
	  switch (it->second.type)
	    {
	    case BMT_INTEGER:
	      acc += snprintf(&buf[acc], len - acc, "%s: %d\n",
			      it->first.c_str(), *(int*)it->second.data);
	      break ;
	    case BMT_DOUBLE:
	      acc += snprintf(&buf[acc], len - acc, "%s: %lf\n",
			      it->first.c_str(), *(double*)it->second.data);
	      break ;
	    case BMT_STRING:
	      acc += snprintf(&buf[acc], len - acc, "%s: %s\n",
			      it->first.c_str(), (const char*)it->second.data);
	      break ;
	    }
      return (acc);
    }

  if ((it = gl_monitor.find(n)) == gl_monitor.end())
    return (0);
  acc = 0;
  switch (it->second.type)
    {
    case BMT_INTEGER:
      acc += snprintf(&buf[acc], len - acc, "%s: %d\n",
		      it->first.c_str(), *(int*)it->second.data);
      break ;
    case BMT_DOUBLE:
      acc += snprintf(&buf[acc], len - acc, "%s: %lf\n",
		      it->first.c_str(), *(double*)it->second.data);
      break ;
    case BMT_STRING:
      acc += snprintf(&buf[acc], len - acc, "%s: %s\n",
		      it->first.c_str(), (const char*)it->second.data);
      break ;
    }
  return (acc);
}
