// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin Library

#include		<string.h>
#include		"lapin_private.h"

static void		enqueue_values(std::stringstream		&ss,
				       const std::string		&s,
				       struct bunny_monitored_value	&v)
{
  char			buffer[9];

  ss << s << ": ";
  switch (v.type)
    {
    case BMT_INTEGER:
      for (auto it = v.ihistory.begin(); it != v.ihistory.end(); ++it)
	{
	  snprintf(&buffer[0], sizeof(buffer), "% 8d", *it);
	  ss << &buffer[0] << ", ";
	}
      snprintf(&buffer[0], sizeof(buffer), "% 8d", *(int*)v.data);
      ss << '[' << &buffer[0] << ']' << std::endl;
      break ;
    case BMT_DOUBLE:
      for (auto it = v.dhistory.begin(); it != v.dhistory.end(); ++it)
	{
	  snprintf(&buffer[0], sizeof(buffer), "% 4.3f", *it);
	  ss << &buffer[0] << ", ";
	}
      snprintf(&buffer[0], sizeof(buffer), "% 4.3f", *(double*)v.data);
      ss << '[' << &buffer[0] << ']' << std::endl;
      break ;
    case BMT_STRING:
      for (auto it = v.shistory.begin(); it != v.shistory.end(); ++it)
	{
	  snprintf(&buffer[0], sizeof(buffer), "% 8.8s", (const char*)v.data);
	  ss << '"' << &buffer[0] << "\", ";
	}
      snprintf(&buffer[0], sizeof(buffer), "% 8.8s", (const char*)v.data);
      ss << '[' << &buffer[0] << ']' << std::endl;
      break ;
    }
}

ssize_t			_bunny_monitor_prepare_buffer(char		*buf,
						      ssize_t		len,
						      const char	*n)
{
  std::stringstream	ss;
  std::map<std::string, struct bunny_monitored_value>::iterator		it;
  ssize_t		acc;
  ssize_t		i;

  if (n == NULL || strcmp(n, "*") == 0)
    {
      for (it = gl_monitor.begin(), acc = 0; it != gl_monitor.end(); ++it)
	enqueue_values(ss, it->first, it->second);
      snprintf(buf, len, "%s", ss.str().c_str());
      return (acc);
    }

  for (i = 0; n[i]; ++i);
  if (i == 0 || n[i - 1] == '*')
    {
      i = (i == 0 ? 0 : i - 1);
      for (it = gl_monitor.begin(), acc = 0; it != gl_monitor.end(); ++it)
	if (strncmp(it->first.c_str(), n, i) == 0)
	  enqueue_values(ss, it->first, it->second);
      snprintf(buf, len, "%s", ss.str().c_str());
      return (acc);
    }

  if ((it = gl_monitor.find(n)) == gl_monitor.end())
    return (0);

  enqueue_values(ss, it->first, it->second);
  snprintf(buf, len, "%s", ss.str().c_str());
  return (acc);
}

