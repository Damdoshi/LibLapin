// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2019
//
// Lapin library

#define			__LAPIN_H__
#include		"private2/logs.hpp"

/*?{
  "type": "function",
  "name": "bunny_set_log_descriptor",
  "order": 1000,
  "desc": "blah",

  "parameters" : [
    {"name": "fd", "desc": "blah"}
  ],

  "return": "",

  "log"
  }
*/
int			bunny_set_log_descriptor(int		fd)
{
  int			prev = bunny::LogDescriptor;

  bunny::LogDescriptor = fd;
  return (prev);
}

int			bunny_set_fail_descriptor(int		fd)
{
  int			prev = bunny::FailDescriptor;

  bunny::FailDescriptor = fd;
  return (prev);
}

int			bunny_set_critical_descriptor(int	fd)
{
  int			prev = bunny::CriticalDescriptor;

  bunny::CriticalDescriptor = fd;
  return (prev);
}

int			bunny_get_log_descriptor(void)
{
  return (bunny::LogDescriptor);
}

int			bunny_get_fail_descriptor(void)
{
  return (bunny::FailDescriptor);
}

int			bunny_get_critical_descriptor(void)
{
  return (bunny::CriticalDescriptor);
}

