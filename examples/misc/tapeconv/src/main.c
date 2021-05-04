/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** Bibliotheque Lapin
*/

#include			<fcntl.h>
#include			<sys/stat.h>
#include			<time.h>
#include			<assert.h>
#include			<lapin.h>

void				set_sample(int16_t	*sample,
					   int		*tot,
					   int		val,
					   int		stretch)
{
  int				i;

  for (i = 0; i < stretch; ++i)
    sample[(*tot)++] = val;
}

int				main(int		argc,
				     char		**argv)
{
  char				*format = "wav";
  int				stretch = 1;
  bool				switchbit = false;
  t_bunny_effect		*eff;
  char				*data;
  struct stat			sta;
  char				bf[512];
  int				tot;
  int				fd;
  int				rd;
  int				i;
  int				j;
 
  for (i = 1; i < argc; ++i)
    {
      if (atoi(argv[i]) != 0)
	{
	  if ((stretch = atoi(argv[i])) <= 0)
	    {
	      fprintf(stderr, "%s: Invalid stretch value [1;oo[. Setting 1.\n", argv[0]);
	      stretch = 1;
	    }
	  continue ;
	}
      if (argv[i][0] == '.')
	{
	  format = &argv[i][1];
	  continue ;
	}
      if (strcmp(argv[i], "switch") == 0)
	{
	  switchbit = true;
	  continue;
	}
      if (strcmp(argv[i], "state") == 0)
	{
	  switchbit = false;
	  continue;
	}

      stat(argv[i], &sta);
      // stretch * 8bit * octet / nbr sample
      // stretch pour bien voir les haut et bas binaire
      rd = ceil(stretch * 8.0 * sta.st_size / 8000); 
      if ((eff = bunny_create_effect(rd, 8000)) == NULL)
	{
	  fprintf(stderr, "%s: Cannot create sound effect for %s.\n", argv[0], argv[i]);
	  continue;
	}
      if ((fd = open(argv[i], O_RDONLY)) == -1)
	{
	  fprintf(stderr, "%s: Cannot open %s.\n", argv[0], argv[i]);
	  goto Effect;
	}
      if ((data = malloc(sta.st_size)) == NULL)
	{
	  fprintf(stderr, "%s: Cannot allocate data for %s: %s.\n", argv[0], argv[i], strerror(errno));
	  goto Close;
	}
      if (read(fd, data, sta.st_size) == -1)
	{
	  fprintf(stderr, "%s: Cannot read from file %s: %s.\n", argv[0], argv[i], strerror(errno));
	  goto Free;
	}

      if (switchbit)
	bunny_cipher_data(data, sta.st_size, BS_SWITCH, NULL);
      
      tot = 0;
      for (j = 0; j < sta.st_size; j += 1)
	for (int z = 7; z >= 0; --z)
	  set_sample(eff->sample, &tot, ((data[j] >> z) & 1) ? 30000 : -30000, stretch);

      snprintf(&bf[0], sizeof(bf), "%s.%s", argv[i], format);
      if (bunny_save_effect(eff, bf) == false)
	fprintf(stderr, "%s: Fail to save sound to file %s (from %s).\n", argv[0], bf, argv[i]);

    Free:
      free(data);
    Close:
      close(fd);
    Effect:
      bunny_delete_sound(&eff->sound);
    }
  return (EXIT_SUCCESS);
}

