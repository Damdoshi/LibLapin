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

  bunny_configuration_push_path(".");
  for (i = 1; i + 1 < argc; ++i)
    bunny_configuration_push_path(argv[i]);
  printf("Resolved path is: %s.\n", bunny_configuration_resolve_path(argv[i]));
  return (EXIT_SUCCESS);
}
