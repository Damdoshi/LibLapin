/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** Bibliotheque Lapin
*/

#include		<string.h>
#include		<lapin.h>

int			main(int		argc,
			     char		**argv)
{
  t_bunny_cipher_key	*key;
  void			*dat;
  size_t		siz;
  int			i;

  if (argc < 4)
    {
      printf("%s: Usage is:\n\t%s c/u key [file]+\n", argv[0], argv[0]);
      return (EXIT_FAILURE);
    }

  i = strlen(argv[2]);
  key = bunny_alloca(sizeof(*key) + sizeof(key->key[0]) * (i + 1));
  key->length = i;
  strcpy(&key->key[0], argv[2]);

  for (i = 3; i < argc; ++i)
    if (bunny_load_file(argv[i], &dat, &siz) == -1)
      fprintf(stderr, "Cannot load %s.\n", argv[i]);
    else
      {
	if (argv[1][0] == 'c')
	  {
	    bunny_cipher_data(dat, siz, BS_CAESAR, key);
	    bunny_cipher_data(dat, siz, BS_XOR, key);
	    bunny_cipher_data(dat, siz, BS_SHAKER, key);
	    bunny_cipher_data(dat, siz, BS_SWITCH, key);
	  }
	else if (argv[1][0] == 'u')
	  {
	    bunny_uncipher_data(dat, siz, BS_SWITCH, key);
	    bunny_uncipher_data(dat, siz, BS_SHAKER, key);
	    bunny_uncipher_data(dat, siz, BS_XOR, key);
	    bunny_uncipher_data(dat, siz, BS_CAESAR, key);
	  }
	else
	  {
	    fprintf(stderr, "Invalid operation specified '%s'.\n", argv[1]);
	    bunny_delete_file(dat, argv[i]);
	    continue ;
	  }
	if (bunny_save_file(argv[i], dat, siz) == false)
	  fprintf(stderr, "Cannot save %s.\n", argv[i]);
	bunny_delete_file(dat, argv[i]);
      }
  return (EXIT_SUCCESS);
}

