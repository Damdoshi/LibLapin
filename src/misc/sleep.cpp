// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		<time.h>
#include		"lapin_private.h"

unsigned long long	bunny_usleep(unsigned long long	delay)
{
  return (bunny_sleep(delay * 1e3));
}

t_bunny_time		bunny_sleep(t_bunny_time	delay)
{
  struct timespec	duration;
  struct timespec	remain;

  duration.tv_sec = delay / 1000000000;
  duration.tv_nsec = delay % 1000000000;
  if (nanosleep(&duration, &remain))
    return (remain.tv_sec * 1e9 + remain.tv_nsec);
  return (0);
}
