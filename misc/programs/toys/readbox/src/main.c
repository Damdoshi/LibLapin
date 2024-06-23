/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** LibLapin Test
*/

#include		<fcntl.h>
#include		<stdio.h>
#include		<assert.h>
#include		<lapin.h>

int			main(int		argc,
			     char		**argv)
{
  t_bunny_box		*box;
  int			fd;
  int			i;

  assert(argc >= 3);
  if (*argv[1] == 'c')
    {
      box = bunny_create_box(10);
      memcpy(&box->key[0], "abcd", sizeof(box->key));
      bunny_save_file("./box", box, bunny_box_size(10));
      return (EXIT_SUCCESS);
    }
  else if (*argv[1] != 'o')
    return (EXIT_FAILURE);

  for (i = 2; i < argc; ++i)
    if ((fd = open(argv[i], O_RDONLY)) == -1)
      perror("read");
    else
      {
	while ((box = bunny_load_box(fd)))
	  printf("%c%c%c%c - %d\n", box->key[0], box->key[1], box->key[2], box->key[3], box->box_size);
	close(fd);
      }
  return (EXIT_SUCCESS);
}

