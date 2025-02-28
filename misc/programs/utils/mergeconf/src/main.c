/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2020
**
** MergeConf (UniConf 2.0)
**
** stdin / -i [files]+
** stdout / -o [outfile]+
*/

#include		<stdio.h>
#include		<lapin.h>
#include		<string.h>

bool			load_all_files(const char			*prg,
				       t_bunny_configuration_type	format,
				       t_bunny_configuration		*cnf,
				       const char			**inputs,
				       size_t				len)
{
  if (len)
    {
      char		*tmp;
      
      for (size_t i = 0; i < len; ++i)
	if ((tmp = strchr(inputs[i], '=')) != NULL)
	  {
	    *tmp = 0;
	    char	buffer[strlen(tmp + 1) + 1];
	    ssize_t	j = 0;
	    
	    if (tmp[1] != '"')
	      strcpy(buffer, &tmp[1]);
	    else if (bunny_read_cstring(tmp + 1, &j, buffer, sizeof(buffer)) == false)
	      goto Bad;
	    if (bunny_configuration_setf(cnf, buffer, "%s", inputs[i]) == false)
	      goto Bad;
	    continue ;
	  Bad:
	    fprintf(stderr, "%s: Cannoy apply transformation of %s into %s.\n", prg, inputs[i], tmp + 1);
	    return (false);
	  }
	else if (bunny_open_configuration(inputs[i], cnf) == NULL)
	  {
	    fprintf(stderr, "%s: Cannot load file %s.\n", prg, inputs[i]);
	    return (false);
	  }
    }
  else
    {
      char		buffer[1024 * 1024];
      ssize_t		z, s;

      z = s = 0;
      do
	{
	  if ((s = read(STDIN_FILENO, &buffer[z], sizeof(buffer) - z - 1)) == -1)
	    {
	      fprintf(stderr, "%s: Cannot read from stdin: %s.\n", prg, strerror(errno));
	      return (false);
	    }
	  z += s;
	}
      while (s == 0 && z != sizeof(buffer) - 1);
      buffer[z] = '\0';
      if (bunny_read_configuration(format, &buffer[0], cnf) == NULL)
	return (false);
    }

  return (true);
}

bool			write_all_files(const char			*prg,
					t_bunny_configuration_type	format,
					t_bunny_configuration		*cnf,
					const char			**outputs,
					size_t				len)
{
  if (len)
    {
      for (size_t i = 0; i < len; ++i)
	if (bunny_save_configuration
	    (bunny_which_format(outputs[i]), outputs[i], cnf) == false)
	  {
	    fprintf(stderr, "%s: Cannot write file %s.\n", prg, outputs[i]);
	    return (false);
	  }
    }
  else if (bunny_save_configuration(format, "/dev/stdout", cnf) == false)
    {
      fprintf(stderr, "%s: Cannot write configuration.\n", prg);
      return (false);
    }
  return (true);
}

int			main(int					argc,
			     char					**argv)
{
  t_bunny_configuration	*cnf;
  const char		*inputs[argc];
  const char		*outputs[argc];
  size_t		nbr_inputs = 0;
  size_t		nbr_outputs = 0;
  t_bunny_configuration_type iformat = BC_CUSTOM;
  t_bunny_configuration_type oformat = BC_CUSTOM;
  bool			resolve = false;
  int			call_main = -1;
  bool			keepsave = false;

  bunny_set_log_mode(false);
  bunny_set_error_descriptor(2);
  bunny_set_log_filter("syntax,configuration");
  for (int i = 1; i < argc; ++i)
    {
      if (strcmp("--resolve", argv[i]) == 0)
	resolve = true;
      if (strcmp("!", argv[i]) == 0)
	{
	  keepsave = false;
	  call_main = i;
	  break ;
	}
      else if (strcmp("+", argv[i]) == 0)
	{
	  keepsave = true;
	  call_main = i;
	  break ;
	}
      else if (!strcmp("-i", argv[i]))
	{
	  if (iformat != BC_CUSTOM)
	    {
	      fprintf(stderr, "%s: Cannot mix option '-if' with option '-i'.\n", *argv);
	      return (EXIT_FAILURE);
	    }
	  for (i += 1; i < argc && argv[i][0] != '-' && argv[i][0] != '!' && argv[i][0] != '+'; ++i)
	    inputs[nbr_inputs++] = argv[i];
	  if (i < argc && (argv[i][0] == '-' || argv[i][0] == '!' || argv[i][0] == '+'))
	    i -= 1;
	}
      else if (!strcmp("-I", argv[i]))
	{
	  i += 1;
	  if (i < argc && argv[i][0] != '-' && argv[i][0] != '!' && argv[i][0] != '+')
	    bunny_configuration_push_path(argv[i]);
	}
      else if (!strcmp("-m", argv[i]))
	{
	  for (i += 1; i < argc && argv[i][0] != '-' && argv[i][0] != '!' && argv[i][0] != '+'; ++i)
	    inputs[nbr_inputs++] = argv[i];
	  if (i < argc && (argv[i][0] == '-' || argv[i][0] == '!' || argv[i][0] == '+'))
	    i -= 1;
	}
      else if (!strcmp("-if", argv[i]))
	{
	  if (iformat != BC_CUSTOM)
	    {
	      fprintf(stderr, "%s: Input format is set twice.\n", *argv);
	      return (EXIT_FAILURE);
	    }
	  if (nbr_inputs != 0)
	    {
	      fprintf(stderr, "%s: Cannot mix option '-if' with option '-i'.\n", *argv);
	      return (EXIT_FAILURE);
	    }
	  i += 1;
	  if (i >= argc)
	    {
	      fprintf(stderr, "%s: -if option takes a parameter.\n", *argv);
	      return (EXIT_FAILURE);
	    }
	  if ((iformat = bunny_which_format(argv[i])) == BC_CUSTOM)
	    {
	      fprintf(stderr, "%s: Unknown format %s.\n", *argv, argv[i]);
	      return (EXIT_FAILURE);
	    }
	}
      else if (!strcmp("-o", argv[i]))
	{
	  if (oformat != BC_CUSTOM)
	    {
	      fprintf(stderr, "%s: Cannot mix option '-of' with option '-o'.\n", *argv);
	      return (EXIT_FAILURE);
	    }
	  for (i += 1; i < argc && argv[i][0] != '-' && argv[i][0] != '!' && argv[i][0] != '+'; ++i)
	    outputs[nbr_outputs++] = argv[i];
	  if (i < argc && (argv[i][0] == '-' || argv[i][0] == '!' || argv[i][0] == '+'))
	    i -= 1;
	}
      else if (!strcmp("-of", argv[i]))
	{
	  if (oformat != BC_CUSTOM)
	    {
	      fprintf(stderr, "%s: Output format is set twice.\n", *argv);
	      return (EXIT_FAILURE);
	    }
	  if (nbr_outputs != 0)
	    {
	      fprintf(stderr, "%s: Cannot mix option '-of' with option '-o'.\n", *argv);
	      return (EXIT_FAILURE);
	    }
	  i += 1;
	  if (i >= argc)
	    {
	      fprintf(stderr, "%s: -of option takes a parameter.\n", *argv);
	      return (EXIT_FAILURE);
	    }
	  if ((oformat = bunny_which_format(argv[i])) == BC_CUSTOM)
	    {
	      fprintf(stderr, "%s: Unknown format %s.\n", *argv, argv[i]);
	      return (EXIT_FAILURE);
	    }
	}
    }

  if (oformat == BC_CUSTOM)
    oformat = BC_DABSIC;
  if (argc == 1 || (iformat == BC_CUSTOM && nbr_inputs == 0))
    {
      fprintf
	(stderr,
	 "Usage is:\n"
	 "\n"
	 "  -if [format]\tSpecify the input format when using stdin\n"
	 "  -of [format]\tSpecify the output format when using stdout. Default is Dabsic.\n"
	 "  -I [path]   \tSpecify an additional path for include or other files to be loaded.\n"
	 "  -i [files]+ \tSpecify input files. Cannot combine with if.\n"
	 "  -o [files]+ \tSpecify output files. Cannot combine with of.\n"
	 "  -m [address=value]+ Specifiy field value.\n"
	 "\n"
	 "  -if and -i are mutually exclusive.\n"
	 "  -if/-i and -m can be chained.\n"
	 "  Fields values and set in the command line order.\n"
	 "\n"
	 "Supported formats are:\n"
	 "\n"
	 "  .ini   \tINI format\n"
	 "  .xml   \tXML format\n"
	 "  .tmx   \tXML format\n"
	 "  .lua   \tLUA data format\n"
	 "  .json  \tJSON format\n"
	 "  .lisp  \tLISP format\n"
	 "  .el    \tLISP format\n"
	 "  .csv   \tCSV format\n"
	 "  .expr  \tMathematic expression\n"
	 "  .dab   \tDabsic format\n"
	 "  .sic   \tDabsic format\n"
	 "  .dabsic\tDabsic format\n"
	 "  .dabseq\tDabsic sequence format\n"
	 "  .dabfun\tDabsic function format\n"
	 "\n"
	 );
      return (EXIT_FAILURE);
    }

  if ((cnf = bunny_new_configuration()) == NULL)
    {
      fprintf(stderr, "%s: Cannot allocate memory for configuration merging.\n", argv[0]);
      return (EXIT_FAILURE);
    }

  if (load_all_files(*argv, iformat, cnf, inputs, nbr_inputs) == false)
    return (EXIT_FAILURE);
  if (resolve)
    if (bunny_configuration_resolve(cnf) == false)
      fprintf(stderr, "%s: Cannot resolve all operations! Operation will be rendered as it.", argv[0]);

  if (call_main != -1)
    {
      bunny_set_log_filter("syntax");
      t_bunny_configuration *params = bunny_new_configuration();
      int ret;
      int i;
      
      bunny_configuration_setf(params, argc - call_main, "[0]");
      for (i = call_main; i < argc; ++i)
	bunny_configuration_setf(params, argv[i], "[1][%d]", i - call_main);
      if (!bunny_configuration_executef(cnf, &ret, false, params, "Main"))
	return (EXIT_FAILURE);
      if (!keepsave)
	return (ret);
    }
  if (write_all_files(*argv, oformat, cnf, outputs, nbr_outputs) == false)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

