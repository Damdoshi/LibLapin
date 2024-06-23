/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** LibLapin Test
*/

#include	<lapin.h>
#include	<string.h>
#include	<unistd.h>

int		main(void)
{
  char		buffer[4096];
  char		*name = "Julien";
  char		*name2 = "Jules";
  int		number = 42;
  int		number2 = 1337;

  bunny_snprintf(&buffer[0], sizeof(buffer),
		 "Salut %s! Tu es le numéro %d.\n",
		 name, number,
		 "Tu passes avec l'autre gars, la, le numéro %d, il s'appelle %s je crois...\n",
		 number2, name2,
		 NULL);
  write(1, &buffer[0], strlen(&buffer[0]));
  return (0);
}
