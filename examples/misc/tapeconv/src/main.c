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

int				main(int	argc,
				     char	**argv)
{
  t_bunny_effect		*eff;
  struct stat			sta;
  char				bf[512];
  int				tot;
  int				fd;
  int				rd;
  int				i;
  int				j;

  for (i = 1; i < argc; ++i)
    {
      tot = 0;
      stat(argv[i], &sta);
      // 8bit * octet / nbr sample
      rd = 8.0 * sta.st_size / 8000; 
      if ((eff = bunny_create_effect(ceil(rd), 8000)) == NULL)
	{
	  fprintf(stderr, "%s: Cannot create sound effect.\n", argv[0]);
	  return (EXIT_FAILURE);
	}
      if ((fd = open(argv[i], O_RDONLY)) == -1)
	{
	  fprintf(stderr, "%s Cannot open %s.\n", argv[0], argv[i]);
	  goto Free;
	}
      do
	{
	  if ((rd = read(fd, &bf[0], sizeof(bf))) == -1)
	    {
	      fprintf(stderr, "%s Cannot read from %s.\n", argv[0], argv[i]);
	      goto Free;
	    }
	  for (j = 0; j < rd; ++j)
	    {
	      eff->sample[tot++] = ((bf[j] >> 7) & 1) ? 30000 : -30000;
	      eff->sample[tot++] = ((bf[j] >> 6) & 1) ? 30000 : -30000;
	      eff->sample[tot++] = ((bf[j] >> 5) & 1) ? 30000 : -30000;
	      eff->sample[tot++] = ((bf[j] >> 4) & 1) ? 30000 : -30000;
	      eff->sample[tot++] = ((bf[j] >> 3) & 1) ? 30000 : -30000;
	      eff->sample[tot++] = ((bf[j] >> 2) & 1) ? 30000 : -30000;
	      eff->sample[tot++] = ((bf[j] >> 1) & 1) ? 30000 : -30000;
	      eff->sample[tot++] = ((bf[j] >> 0) & 1) ? 30000 : -30000;
	    }
	}
      while (rd > 0);
      snprintf(&bf[0], sizeof(bf), "%s.ogg", argv[i]);
      if (bunny_save_effect(eff, bf) == false)
	fprintf(stderr, "%s Fail to save sound to file.\n", argv[0]);

    Free:
      close(fd);
      bunny_delete_sound(&eff->sound);
    }
  return (EXIT_SUCCESS);
}

