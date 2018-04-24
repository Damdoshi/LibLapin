/*
**
**
**
**
**
*/

#include	<stdio.h>
#include	<lapin.h>

int		main(void)
{
  double	init;

  init = -5.2;
  while (bunny_reach(&init, 10.3, 0.07) == false);
  printf("%f -> %f\n", -5.2, init);

  init = 7.6;
  while (bunny_reach(&init, -3.2, 0.14) == false);
  printf("%f -> %f\n", 7.6, init);

  return (EXIT_SUCCESS);
}

