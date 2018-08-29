// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<time.h>
#include		"lapin_private.h"

t_bunny_time		bunny_get_time(void)
{
#if			defined(__linux__) || defined(__APPLE__) || defined(__GNUC__)
  struct timespec	x;

  clock_gettime(CLOCK_MONOTONIC, &x);
  return (x.tv_sec * 1e9 + x.tv_nsec);
#else
  FILETIME		ft;
  unsigned long long	tt;

  GetSystemTimeAsFileTime(&ft);
  tt = ft.dwHighDateTime;
  tt <<= 32;
  tt |= ft.dwLowDateTime;
  tt /= 10;
  tt -= 11644473600000000ULL;
  return (tt * 1e3);
#endif
}

