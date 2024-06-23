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
#include		<string.h> /* strcmp, memcpy, strerror */
#include		<errno.h> /* ...errno... */
#include		<stdio.h> /* fprintf */
#include		<lapin.h>

static int		cipher(const char		*file,
			       t_bunny_cipher_key	*key,
			       t_bunny_ciphering	ciphering)
{
  if (bunny_cipher_file(file, ciphering, key) == false)
    return (-1);
  return (0);
}

static int		uncipher(const char		*file,
				 t_bunny_cipher_key	*key,
				 t_bunny_ciphering	ciphering)
{
  if (bunny_uncipher_file(file, ciphering, key) == false)
    return (-1);
  return (0);
}

static void		usage(const char		*bin)
{
  fprintf
    (stderr,
     "%s: Usage is:\n\t%s [protocol] [-c (cipher) | -u (uncipher)] [key] [files]+\n"
     "Protocols are:\n - shaker\n - xor\n - caesar\n\n"
     , bin, bin);
}

int			main(int			argc,
			     char			**argv)
{
  t_bunny_cipher_key	*key;
  t_bunny_ciphering	ciphering;
  int			action;
  int			i;

  action = 1;
  if (argc < 4 || (strcmp(argv[2], "-c") != 0 && (action = strcmp(argv[2], "-u")) != 0))
    {
      usage(*argv);
      return (EXIT_FAILURE);
    }

  /* get the id of the ciphering algorithm */
  if ((ciphering = bunny_get_ciphering(argv[1])) == BS_CUSTOM)
    {
      fprintf(stderr, "%s: Unsupported algorithm '%s'.\n", *argv, argv[1]);
      usage(*argv);
      return (EXIT_FAILURE);
    }
  
  /* generate a ciphering key with the sent size. */
  /* This key should be long, but for the sake of the example, our will be short */
  i = strlen(argv[3]);
  if ((key = bunny_new_key(i)) == NULL)
    {
      fprintf(stderr, "%s: Cannot generate the ciphering key: %s.\n", *argv, strerror(errno));
      return (EXIT_FAILURE);
    }
  
  /* replace the generated key for the sake of is simplicity for this example */
  /* for real program, using the inner key is better */
  memcpy(&key->key[0], argv[3], i);

  if (action)
    {
      for (i = 4; i < argc; ++i)
	if (cipher(argv[i], key, ciphering) == -1)
	  {
	    if (i == 4)
	      fprintf(stderr, "%s: No files were ciphered.\n", *argv);
	    else
	      fprintf(stderr, "%s: Last ciphered file was '%s'.\n",
		      *argv, argv[i - 1]);
	    return (EXIT_FAILURE);
	  }
    }
  else
    for (i = 4; i < argc; ++i)
      if (uncipher(argv[i], key, ciphering) == -1)
	{
	  if (i == 4)
	    fprintf(stderr, "%s: No files were unciphered.\n", *argv);
	  else
	    fprintf(stderr, "%s: Last unciphered file was '%s'.\n", *argv,
		    argv[i - 1]);
	  return (EXIT_FAILURE);
	}
  return (EXIT_SUCCESS);
}
