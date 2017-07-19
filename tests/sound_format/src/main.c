/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** LibLapin Test
*/

#include		<assert.h>
#include		<stdio.h>
#include		<lapin.h>

int			main(void)
{
  t_bunny_sound		*snd = NULL;
  t_bunny_configuration	*cnf = NULL;

  assert(bunny_set_sound_attribute("./falling.ini", &snd, &cnf, false));
  bunny_save_configuration(BC_INI, "/dev/stdout", cnf);

  assert((snd->volume - 0.6) < 0.1);
  assert((snd->pitch - 0.65) < 0.1);
  assert(snd->loop);
  assert(snd->position[0] - 10 < 0.1);
  assert(snd->position[1] - 20 < 0.1);
  assert(snd->position[2] - 30 < 0.1);
  assert(snd->attenuation - 40 < 0.1);

  bunny_delete_sound(snd);
  bunny_delete_configuration(cnf);
  return (EXIT_SUCCESS);
}

