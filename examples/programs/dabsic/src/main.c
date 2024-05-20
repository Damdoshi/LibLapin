// Jason Brillante "Damdoshi"
// Hanged Bunny studio 2014-2022
// Pentacle Technologie 2008-2023
// EFRITS 2022-2023
//
// DABSIC

#include	<lapin.h>

int		main(int	argc,
		     char	**argv,
		     char	**env)
{
  int		delim;

  if (argc == 1)
    {
      puts("./dabsic file.dab [parameters]*");
      puts("./dabsic [file.dab]+ ! [parameters]*");
      return (EXIT_FAILURE);
    }
  for (delim = 1; delim < argc; ++delim)
    if (strcmp(argv[delim], "!") == 0)
      break ;
  if (delim == argc)
    delim = 1;
  bunny_set_error_descriptor(2);
  bunny_set_log_filter("syntax");

  ///////////////////////////////
  //// CHARGEMENT DES SCRIPTS //
  /////////////////////////////
  t_bunny_configuration *cnf;
  bool			res;

  res = !!(cnf = bunny_new_configuration());
  if (!res)
    return (EXIT_FAILURE);
  for (int i = 1; i <= delim && argv[i][0] != '!'; ++i)
    res = res && (cnf = bunny_open_configuration(argv[i], cnf));
  if (!res)
    return (EXIT_FAILURE);
  t_bunny_configuration *params;
  int			cnt = 1;

  ////////////////////////////////////////////////////////
  //// CHARGEMENT DES PARAMETRES ET DE L'ENVIRONNEMENT //
  //////////////////////////////////////////////////////
  res = !!(params = bunny_new_configuration());
  if (!res)
    return (EXIT_FAILURE);
  res = res && bunny_configuration_setf(params, argv[1], "Argv[0]");
  for (int i = delim + 1; i < argc; ++i, ++cnt)
    res = res && bunny_configuration_setf(params, argv[i], "Argv[%d]", cnt);
  res = res && bunny_configuration_setf(params, cnt, "Argc");
  for (int i = 0; env[i]; ++i)
    res = res && bunny_configuration_setf(params, env[i], "Environ[%d]", i);
  if (!res)
    return (EXIT_FAILURE);

  //////////////////
  //// EXECUTION //
  ////////////////
  bunny_set_error_descriptor(2);
  if (bunny_configuration_executef(cnf, false, params, "[].Main"))
    bunny_configuration_getf(cnf, &cnt, "[].Main");
  else if (bunny_configuration_executef(cnf, false, params, "[].main"))
    bunny_configuration_getf(cnf, &cnt, "[].main");
  else
    {
      fprintf(stderr, "Missing [].Main/[].main node.\n");
      return (EXIT_FAILURE);
    }
  return (cnt);
}

