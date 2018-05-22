/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Mathematic evaluation function test program
*/

#include		<unistd.h>
#include		<stdio.h>
#include		<lapin.h>

int			main(int	argc,
			     char	**argv)
{
  t_bunny_picture	*pic[200];
  t_bunny_effect	*eff[200];
  void			*fil[200];
  size_t		i;

  if (argc == 2 && argv[1][0] == 'd')
    bunny_set_ressource_management(false);

  printf("LOADING ---------------------------------------------\n");
  for (i = 0; i < 200; ++i)
    {
      pic[i] = bunny_load_picture("./pic.png");
      eff[i] = bunny_load_effect("./sound.ogg");
      bunny_load_file("./file.txt", &fil[i], NULL);
    }
  bunny_managed_ressource();
  printf("FREEING HALF ---------------------------------------------\n");
  for (i = 0; i < 200 / 2; ++i)
    {
      bunny_delete_clipable(pic[i]);
      bunny_delete_sound(&eff[i]->sound);
      bunny_delete_file(fil[i], "./file.txt");
    }
  bunny_managed_ressource();
  printf("FREEING THE OTHER HALF ---------------------------------------------\n");
  for (i = 200 / 2; i < 200; ++i)
    {
      bunny_delete_clipable(pic[i]);
      bunny_delete_sound(&eff[i]->sound);
      bunny_delete_file(fil[i], "./file.txt");
    }
  bunny_managed_ressource();
  printf("DONE -----------------------------------------------------\n");
  return (0);
}

