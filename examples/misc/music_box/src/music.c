
#include		<stdlib.h>
#include		<unistd.h>
#include		<stdio.h>
#include		<string.h>
#include		<lapin.h>

int			main(void)
{
  t_bunny_music		*music;
  char			buffer[64];
  int			len;

  if ((music = bunny_load_music("soundlogo.wav")) == NULL)
    return (EXIT_FAILURE);
  puts("Syntax is: play | stop | exit | pitch=float | vol=float | loop=0|1");
  bunny_sound_play(&music->sound);
  do
    {
      write(1, "LAPIN>", 6);
      if ((len = read(0, &buffer[0], 63)) == -1)
	return (EXIT_FAILURE);
      buffer[len] = '\0';
      if (strncmp(&buffer[0], "play", 4) == 0)
	bunny_sound_play(&music->sound);
      else if (strncmp(&buffer[0], "stop", 4) == 0)
	bunny_sound_stop(&music->sound);
      else if (strncmp(&buffer[0], "pitch=", 6) == 0)
	bunny_sound_pitch(&music->sound, atof(&buffer[6]));
      else if (strncmp(&buffer[0], "vol=", 4) == 0)
      	bunny_sound_volume(&music->sound, atof(&buffer[4]));
      else if (strncmp(&buffer[0], "loop=", 5) == 0)
      	bunny_sound_loop(&music->sound, !!atoi(&buffer[5]));
      else if (strncmp(&buffer[0], "exit", 4) == 0)
	len = 0;
      else
	write(1, "Unrecognized command\n", 21);
    }
  while (len > 0);
  bunny_delete_sound(&music->sound);
  return (EXIT_SUCCESS);
}

