/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** LibLapin - Basic Ciphering
**
** All bunny functions are from lapin/security.h
**
*/

#include		<stdlib.h> /* EXIT_FAILURE, EXIT_SUCCESS */
#include		<stdio.h> /* fprintf */
#include		<string.h> /* strerror */
#include		<errno.h> /* ...errno... */
#include		<lapin.h>

static void		usage(const char		*bin)
{
  fprintf
    (stderr,
     "%s: Usage is:\n\t%s "
     "[positive integer as random seed] "
     "[[-p program+] | [-r algorithm ressource+]]\n"
     , bin, bin);
}

static int		prepare_data(const char		*bin,
				     t_bunny_ciphering	ciphering,
				     t_bunny_cipher_key	*key,
				     int		program,
				     const char		*file)
{
  if (program)
    {
      if (bunny_fill_default_key(file, key) == false)
	{
	  fprintf(stderr, "%s: Cannot fill the program '%s'.\n", bin, file);
	  return (-1);
	}
    }
  else if (bunny_cipher_file(file, ciphering, key) == false)
    {
      fprintf(stderr, "%s: Cannot fill the program '%s'.\n", bin, file);
      return (-1);
    }
  return (0);
}

int			main(int			argc,
			     char			**argv)
{
  t_bunny_ciphering	ciphering;
  t_bunny_cipher_key	*key;
  char			*str;
  long long int		res;
  int			i;

  if (argc < 4 && argc != 2)
    {
      usage(*argv);
      return (EXIT_FAILURE);
    }
  res = strtoll(argv[1], &str, 0);
  if (argv[1] == str || errno == ERANGE)
    {
      usage(*argv);
      return (EXIT_FAILURE);
    }
  srand(res);
  if ((key = bunny_new_key(bunny_default_key()->length)) == NULL)
    {
      fprintf(stderr, "%s: Cannot generate the ciphering key: %s.\n", *argv, strerror(errno));
      return (EXIT_FAILURE);
    }
  res = 1;
  if (strcmp(argv[2], "-r") != 0 && (res = strcmp(argv[2], "-p")) != 0)
    {
      usage(*argv);
      return (EXIT_FAILURE);
    }
  if (res == 1)
    {
      if ((ciphering = bunny_get_ciphering(argv[4])) == BS_CUSTOM)
	{
	  fprintf(stderr, "%s: Unsupported algorithm '%s'.\n", *argv, argv[4]);
	  return (EXIT_FAILURE);
	}
      if (argc == 4)
	{
	  usage(*argv);
	  return (EXIT_FAILURE);
	}
    }
  for (i = 4 + res; i < argc; ++i)
    if (prepare_data(*argv, ciphering, key, res, argv[i]) == -1)
      {
	if (i == 4 + res)
	  fprintf(stderr, "%s: No files were processed.\n", *argv);
	else
	  fprintf(stderr, "%s: Last processed file was '%s'.\n", *argv, argv[i - 1]);
	return (EXIT_FAILURE);
      }
  return (EXIT_SUCCESS);
}

