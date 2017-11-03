/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** LibLapin Test
*/

#include		<assert.h>
#include		<time.h>
#include		<signal.h>
#include		<stdio.h>
#include		<lapin.h>

static void		sighandler(int		sig)
{
  (void)sig;
  exit(EXIT_FAILURE);
}

int			main(int		argc,
			     char		**argv)
{
  float			flt;
  uint16_t		_16;
  uint8_t		_8;

  (void)argv;
  srand(time(NULL));
  signal(SIGALRM, sighandler);
  if (argc == 2)
    alarm(2);

  flt = 3.5;
  _16 = bunny_to_fixed_decimal(flt, 8, 16);
  if (abs(bunny_to_floating_decimal(_16, 8) - flt) < 0.025)
    printf("%f -> %X OK\n", flt, _16);
  else
    {
      printf("%f -> %X KO\n", flt, _16);
      return (EXIT_FAILURE);
    }

  flt = 3.5;
  _8 = bunny_to_fixed_decimal(flt, 6, 8);
  if (abs(bunny_to_floating_decimal(_8, 6) - flt) < 0.025)
      printf("%f -> %X OK\n", flt, _8);
  else
    {
      printf("%f -> %X KO\n", flt, _8);
      return (EXIT_FAILURE);
    }
  
  printf("OK!\n");
  return (EXIT_SUCCESS);
}

