// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2019
//
// Lapin library

#define			__LAPIN_H__
#include		"private2/logs.hpp"

t_bunny_log_verbosity	bunny_set_log_verbosity(t_bunny_log_verbosity	verbosity)
{
  t_bunny_log_verbosity	prev = (t_bunny_log_verbosity)bunny::LogVerbosity;

  bunny::LogVerbosity = (int)verbosity;
  return (prev);
}

t_bunny_log_verbosity	bunny_get_log_verbosity(void)
{
  return (t_bunny_log_verbosity)bunny::LogVerbosity;
}

