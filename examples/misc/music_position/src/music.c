
#include		<math.h>
#include		<lapin.h>
#include		<unistd.h>
#include		<stdio.h>

t_bunny_response	loop(t_bunny_sound		*music)
{
  static double		i;

  i += 0.1;
  bunny_sound_position(music, cos(i) * 2, sin(i) * 2, 0);
  return (GO_ON);
}

int			main(void)
{
  t_bunny_effect	*music;

  puts("CTRL-C pour quitter");
  
  bunny_set_maximum_ram(100 * 1024 * 1024);

  if ((music = bunny_load_effect("videogame.ogg")) == NULL)
    {
      printf("Cannot open file.\n");
      return (1);
    }

  bunny_sound_loop(&music->sound, true);
  bunny_sound_play(&music->sound);

  bunny_set_loop_main_function((t_bunny_loop)loop);
  bunny_loop(NULL, 25, music);

  bunny_delete_sound(&music->sound);
  return (0);
}

