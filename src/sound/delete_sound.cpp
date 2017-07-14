// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include		"lapin_private.h"

void			bunny_delete_sound(t_bunny_sound		*sound)
{
  enum _music_or_sound	*type = (enum _music_or_sound*)sound;

  free((void*)sound->file);
  if (*type == MUSIC)
    delete ((struct bunny_music*)sound);
  else
    {
      struct bunny_effect *snd = (struct bunny_effect*)sound;

      RessourceManager.TryRemove(ResManager::BUNNY_SAMPLE, snd->res_id, snd);
      RessourceManager.TryRemove(ResManager::SF_SOUNDBUFFER, snd->res_id, snd);
      delete ((struct bunny_effect*)sound);
    }
  scream_log_if("%p", sound);
}
