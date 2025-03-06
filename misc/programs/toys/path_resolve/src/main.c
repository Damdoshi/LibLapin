/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** LibLapin Test
*/

#include	<lapin.h>
#include	<stdio.h>

int		main(int		argc,
		     char		**argv)
{
  int		i;
  char		buffer[1024];

  bunny_configuration_push_path(".");
  for (i = 1; i + 1 < argc; ++i)
    bunny_configuration_push_path(argv[i]);
  if (bunny_configuration_resolve_path(argv[i], buffer, sizeof(buffer)))
    printf("Resolved path is: %s.\n", buffer);
  else
    printf("No resolved path found.");
  return (EXIT_SUCCESS);
}
