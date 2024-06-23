/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** LibLapin Test
*/

#include		<stdio.h>
#include		<time.h>
#include		<stdlib.h>
#include		<signal.h>
#include		<assert.h>
#include		<lapin.h>

static void		sighandler(int		sig)
{
  (void)sig;
  exit(EXIT_FAILURE);
}

static void		max_entropy(char		*data,
				    size_t		len,
				    void		*dat,
				    bool		cipher)
{
  (void)data;
  (void)len;
  (void)dat;
  (void)cipher;
  if (cipher)
    {
      // Unciphering operation create better entropy
      bunny_uncipher_data(data, len, BS_SWITCH, dat); // !
      bunny_uncipher_data(data, len, BS_SHAKER, dat); // !
    }
  else
    {
      bunny_cipher_data(data, len, BS_SHAKER, dat);
      bunny_cipher_data(data, len, BS_SWITCH, dat);
    }
}

void			refresh_test(const char	*str)
{
  t_bunny_configuration	*a, *b;

  printf("--------------- test %s --------------\n", str);

  if ((a = bunny_load_configuration(BC_DABSIC, str, NULL)) == NULL)
    {
      bunny_perror(NULL);
      exit(EXIT_FAILURE);
    }

  gl_bunny_ressource_ciphering = NULL;
  bunny_save_configuration(BC_DABSIC, "/dev/stdout", a);
  gl_bunny_ressource_ciphering = max_entropy;

  bunny_save_configuration(BC_DABSIC, "tmp.dab", a);
  assert(b = bunny_load_configuration(BC_DABSIC, "./tmp.dab", NULL));
  bunny_save_configuration(BC_DABSIC, "tmp2.dab", b);
  assert(system("diff tmp.dab tmp2.dab") == 0);
  //system("rm tmp*.dab");

  bunny_delete_configuration(a);
  bunny_delete_configuration(b);
}

int			main(int		argc,
			     char		**argv)
{
  (void)argv;
  srand(time(NULL));
  signal(SIGALRM, sighandler);
  bunny_set_error_descriptor(2);
  if (argc >= 2)
    {
      if (argc == 3)
	refresh_test(argv[1]);
      else
	alarm(2);
      return (EXIT_SUCCESS);
    }

  gl_bunny_ressource_ciphering = max_entropy;
  gl_bunny_ressource_data = bunny_new_key(7);
  strcpy(&((t_bunny_cipher_key*)gl_bunny_ressource_data)->key[0], "abcdef");
  ((t_bunny_cipher_key*)gl_bunny_ressource_data)->length = 6;

  refresh_test("./configuration.dab");

  return (EXIT_SUCCESS);
}
