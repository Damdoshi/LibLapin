/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** LibLapin Test
*/

#include		<assert.h>
#include		<lapin.h>

int			main(int	argc,
			     char	**argv)
{
  t_bunny_music		*music;

  assert(argc == 2);
  assert(music = bunny_load_music(argv[1]));
  bunny_sound_play(&music->sound);
  bunny_usleep(10 * 1e6);
  bunny_delete_sound(music);
  return (EXIT_SUCCESS);
}

