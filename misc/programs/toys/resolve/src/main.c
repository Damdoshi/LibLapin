/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2021
**
** LibLapin Test
*/

#include		<stdio.h>
#include		<time.h>
#include		<stdlib.h>
#include		<signal.h>
#include		<assert.h>
#include		<lapin.h>


int			main(int		argc,
			     char		**argv)
{
  t_bunny_configuration	*cnf;

  if (argc != 2)
    return (EXIT_FAILURE);
  if ((cnf = bunny_open_configuration(argv[1], NULL)) == NULL)
    return (EXIT_FAILURE);
  bunny_configuration_resolve(cnf);
  bunny_save_configuration(BC_DABSIC, "/dev/stdout", cnf);
  return (EXIT_SUCCESS);
}

