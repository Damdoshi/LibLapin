/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2018
**
** Sound manager test
*/

#include		<stdlib.h>
#include		<lapin.h>
#include		<assert.h>

int			main(void)
{
  // Utilisation du gestionnaire de son global
  t_bunny_sound_manager	*mgr = &gl_bunny_sound_manager;
  t_bunny_music		*mus;
  t_bunny_effect	*eff;

  assert(mus = bunny_load_music("./music.ogg"));
  assert(eff = bunny_load_effect("./effect.ogg"));
  assert(bunny_sound_manager_add(mgr, mus, BST_MUSIC));
  assert(bunny_sound_manager_add(mgr, eff, BST_EFFECT));

  bunny_sound_loop(&mus->sound, true);
  bunny_sound_loop(&eff->sound, true);

  bunny_delete_sound(mus);
  bunny_delete_sound(eff);
  return (EXIT_SUCCESS);
}
