/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Mathematic evaluation function test program
*/

#include		<stdio.h>
#include		<lapin.h>

int			main(int	argc,
			     char	**argv)
{
  char			buffer[1024 * 1024];
  double		res;
  FILE			*pip;

  if (argc != 2)
    return (1);
  snprintf(&buffer[0], sizeof(buffer), "echo '%s' | bc", argv[1]);
  if ((pip = popen(&buffer[0], "r")) == NULL)
    return (1);
  res = bunny_evaluate(argv[1], NULL);
  buffer[read(fileno(pip), &buffer[0], sizeof(buffer))] = '\0';
  pclose(pip);
  printf("\nbunny_evaluate: %f\n\nbc: %s\n\n", res, &buffer[0]);
  return (0);
}

