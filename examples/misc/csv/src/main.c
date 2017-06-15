/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Bibliotheque Lapin
*/

#include			<lapin.h>
#include			<stdlib.h>
#include			<stdio.h>

int				main(int		argc,
				     char		**argv)
{
  t_bunny_configuration		*conf, *nod;
  char				*out;
  int				i;

  for (i = 1; i < argc; ++i)
    {
      if ((conf = bunny_new_configuration()) == NULL)
	return (EXIT_FAILURE);
      if (bunny_load_configuration(BC_CSV, argv[i], conf) == NULL)
	{
	  bunny_delete_configuration(conf);
	  fprintf(stderr, "Failure while reading : %s\n", argv[i]);
	  return (EXIT_FAILURE);
	}
      nod = bunny_configuration_go_get_node_va(conf, 2, -1, -1);
      bunny_configuration_set_string(nod, "ZOUBIDA");
      if ((out = bunny_write_configuration(BC_CSV, conf)) == NULL)
	{
	  bunny_delete_configuration(conf);
	  fprintf(stderr, "Failure while writing : %s\n", argv[i]);
	  return (EXIT_FAILURE);
	}
      write(1, out, strlen(out));
      bunny_free(out);
      bunny_delete_configuration(conf);
    }
  return (EXIT_SUCCESS);
}

