/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2018
**
** LibLapin Test
*/

#include		<lapin.h>

int			main(int		argc,
			     char		**argv)
{
  char			buffer[1024 * 1024];
  size_t		len;
  t_bunny_obj_file	*file;

  if (argc != 2)
    return (EXIT_FAILURE);
  if ((file = bunny_load_obj_file(argv[1])) == NULL)
    return (EXIT_FAILURE);
  len = bunny_write_obj_file(file, &buffer[0], sizeof(buffer));
  write(1, &buffer[0], len);
  bunny_delete_obj_file(file);
  return (EXIT_SUCCESS);
}
