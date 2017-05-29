/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** LibLapin Test
*/

#include		<string.h>
#include		<stdio.h>
#include		<time.h>
#include		<signal.h>
#include		<assert.h>
#include		<stdlib.h>
#include		<lapin.h>

static void		sighandler(int		sig)
{
  (void)sig;
  exit(EXIT_FAILURE);
}

static void		display(char		*a,
				char		*b,
				size_t		l )
{
  size_t		i;

  printf("Got:\t");
  for (i = 0; i < l ; ++i)
    {
      if (i % 8 == 0 && i)
	printf(",");
      if (i % 4 == 0 && i)
	printf(" ");

      if (bunny_bitfield_get(a, i))
	printf("1");
      else
	printf("0");
    }
  printf("\n");

  printf("Exp:\t");
  for (i = 0; i < l; ++i)
    {
      if (i % 8 == 0 && i)
	printf(",");
      if (i % 4 == 0 && i)
	printf(" ");

      if (bunny_bitfield_get(b, i))
	printf("1");
      else
	printf("0");

    }
  printf("\n");
}

static void		test(void)
{
  // Simple test to debug the function
  char			simple[2] = {0xF0, 0xCA};   // 0000 1111 , 0101 0011
  char			expected[2] = {0x10, 0x5F}; // 0000 1000 , 1111 1010

  bunny_cipher_data(simple, sizeof(simple), BS_SWITCH, NULL);
  display(simple, expected, sizeof(simple) * 8);
  assert(simple[0] == expected[0]);
  assert(simple[1] == expected[1]);

  // Massive test to explore corner case
  size_t		nbr;

  for (nbr = 0; nbr < 100; ++nbr)
    {
      char		buffer[256];
      char		duplicate[256];
      size_t		i, max;

      max = rand() % (sizeof(buffer) - 1) + 1;
      for (i = 0; i < max; ++i)
	buffer[i] = duplicate[i] = rand();
      bunny_cipher_data(&buffer[0], max, BS_SWITCH, NULL);
      bunny_uncipher_data(&buffer[0], max, BS_SWITCH, NULL);
      display(buffer, duplicate, sizeof(simple) * 8);
      for (i = 0; i < max; ++i)
	assert(buffer[i] == duplicate[i]);
    }
}

int			main(int		argc,
			     char		**argv)
{
  (void)argv;
  srand(time(NULL));
  signal(SIGALRM, sighandler);
  if (argc == 2)
    alarm(2);

  test();
  return (EXIT_SUCCESS);
}

