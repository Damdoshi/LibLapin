// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<time.h>
#include		"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_get_time
 * @doc-kind function
 * @doc-module asynclock
 * @doc-order 110
 * @doc-since 12
 * @doc-until latest
 * @doc-level 10
 *
 * @doc-lang en
 * @brief Returns the system time as a nanosecond timestamp.
 * @description bunny_get_time returns a system timestamp expressed in nanoseconds. It is intended for measuring elapsed time, especially with bunny_delta_time.
 * @return-case success On $Bsuccess@, returns the current system timestamp in nanoseconds.
 * @see bunny_delta_time
 *
 * @doc-lang fr
 * @brief Renvoie le temps système sous forme de timestamp en nanosecondes.
 * @description bunny_get_time renvoie un timestamp système exprimé en nanosecondes. Elle sert à mesurer du temps écoulé, notamment avec bunny_delta_time.
 * @return-case success En cas de $Bsuccès@, renvoie le timestamp système courant en nanosecondes.
 * @see bunny_delta_time
 */
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
