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
  t_bunny_configuration		*conf;
  char				*out;
  const char			*out2;
  int				i;

  if ((conf = bunny_new_configuration()) == NULL)
    return (EXIT_FAILURE);
  if (argc != 1)
    {
      for (i = 1; i < argc; ++i)
	if (bunny_load_configuration(BC_INI, argv[i], conf) == NULL)
	  {
	    bunny_delete_configuration(conf);
	    fprintf(stderr, "Failure while reading : %s\n", argv[i]);
	    return (EXIT_FAILURE);
	  }
      if ((out = bunny_write_configuration(BC_INI, conf)) == NULL)
	{
	  bunny_delete_configuration(conf);
	  fprintf(stderr, "Failure while writing : %s\n", argv[i]);
	  return (EXIT_FAILURE);
	}
      puts(out);
      bunny_free(out);
      bunny_delete_configuration(conf);
    }
  else
    {
      if ((conf = bunny_load_configuration(BC_INI, "verylong.ini", NULL)) == NULL)
	return (EXIT_FAILURE);
      if ((conf = bunny_configuration_go_get_node_va(conf, 3, "topsection", "field", -3)) == NULL)
	return (EXIT_FAILURE);
      if (bunny_configuration_get_string(conf, &out2))
	puts(out2);
    }
  return (EXIT_SUCCESS);
}

