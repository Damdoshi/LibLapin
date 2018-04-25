/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** LibLapin Test
*/

#include		<lapin.h>

int			main(int	argc,
			     char	**argv)
{
  t_bunny_configuration	*a;
  int			i;

  bunny_set_error_descriptor(2);
  for (i = 1; i < argc; ++i)
    {
      if ((a = bunny_open_configuration(argv[i], NULL)) == NULL)
	{
	  bunny_perror(NULL);
	  return (EXIT_FAILURE);
	}
      bunny_save_configuration(BC_DABSIC, "/dev/stdout", a);
      bunny_delete_configuration(a);
    }
  return (EXIT_SUCCESS);
}

