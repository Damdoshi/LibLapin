// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2019
//
// Lapin library

#define			__LAPIN_H__
#include		"private2/logs.hpp"

t_bunny_log_length	bunny_set_log_length(t_bunny_log_length	length)
{
  t_bunny_log_length	prev = bunny::LogLength;

  bunny::LogLength = length;
  return (prev);
}

t_bunny_log_length	bunny_get_log_length(void)
{
  return (bunny::LogLength);
}

