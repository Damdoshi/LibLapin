/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Bibliotheque Lapin
*/

#include			<unistd.h>
#include			<fcntl.h>
#include			<assert.h>
#include			<lapin.h>
#include			<string.h>
#include			<stdlib.h>
#include			<stdio.h>

int				main(int		argc,
				     char		**argv)
{
  char				buf[256];
  t_bunny_configuration		*conf;
  char				*out;
  int				i;

  for (i = 1; i < argc; ++i)
    {
      if ((conf = bunny_new_configuration()) == NULL)
	return (EXIT_FAILURE);
      if (bunny_load_configuration(BC_CSV, argv[i], conf) == NULL)
	{
	  bunny_delete_configuration(conf);
	  fprintf(stderr, "Failure while reading : %s\n", argv[i]);
	  unlink("dup.csv");
	  return (EXIT_FAILURE);
	}
      if ((out = bunny_write_configuration(BC_CSV, conf)) == NULL)
	{
	  bunny_delete_configuration(conf);
	  fprintf(stderr, "Failure while writing : %s\n", argv[i]);
	  unlink("dup.csv");
	  return (EXIT_FAILURE);
	}
      int			fd;

      assert(fd = open("dup.csv", O_WRONLY | O_CREAT | O_TRUNC, 0644));
      assert(write(fd, out, strlen(out)) == (ssize_t)strlen(out));
      close(fd);
      bunny_free(out);
      bunny_delete_configuration(conf);
      snprintf(&buf[0], sizeof(buf), "diff dup.csv %s", argv[i]);
      assert(system(&buf[0]) == 0);
      printf("%s is ok.\n", argv[i]);
    }
  printf("All ok\n");
  unlink("dup.csv");
  return (EXIT_SUCCESS);
}

