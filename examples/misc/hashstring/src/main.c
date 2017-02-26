/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Hash test program
*/

#include		<stdio.h>
#include		<string.h>
#include		<time.h>
#include		<lapin.h>

int			main(void)
{
  const char		*a = "ThisIsALongStringXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXxx";
  const char		*b = "ThisIsALongStringXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXxy";
  struct timespec	bef, aft;
  int			i;

  clock_gettime(CLOCK_MONOTONIC, &bef);
  for (i = 0; i < 1000000; ++i)
    if (strcmp(a, b)) {}
  clock_gettime(CLOCK_MONOTONIC, &aft);

  printf("%ld %ld\n", aft.tv_sec - bef.tv_sec, aft.tv_nsec - bef.tv_nsec);

  int64_t		hs1, hs2;

  clock_gettime(CLOCK_MONOTONIC, &bef);
  hs1 = bunny_hash(BH_MULTIPLIER, a, strlen(a));
  hs2 = bunny_hash(BH_MULTIPLIER, b, strlen(b));


  for (i = 0; i < 1000000; ++i)
    if (hs1 == hs2) {}
  clock_gettime(CLOCK_MONOTONIC, &aft);
  printf("%ld %ld\n", aft.tv_sec - bef.tv_sec, aft.tv_nsec - bef.tv_nsec);

  return (0);
}

