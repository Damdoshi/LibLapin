/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Bibliotheque Lapin
*/

#include			<stdio.h>
#include			<lapin.h>

int				main(int		argc,
				     char		**argv)
{
  t_bunny_configuration		*conf;
  char				*out;
  int				i;

  if ((conf = bunny_new_configuration()) == NULL)
    return (EXIT_FAILURE);
  if (argc != 1)
    {
      for (i = 1; i < argc; ++i)
	if (bunny_load_configuration(BC_DABSIC, argv[i], conf) == NULL)
	  {
	    bunny_delete_configuration(conf);
	    return (EXIT_FAILURE);
	  }
      if ((out = bunny_write_configuration(BC_DABSIC, conf)) == NULL)
	{
	  bunny_delete_configuration(conf);
	  return (EXIT_FAILURE);
	}
      puts(out);
      bunny_free(out);
      bunny_delete_configuration(conf);
    }
  return (EXIT_SUCCESS);   
}

