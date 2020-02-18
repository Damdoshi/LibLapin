// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include		"lapin_private.h"

void			_bunny_delete_sound(t_bunny_sound		*sound)
{
  enum _music_or_sound	*type = (enum _music_or_sound*)sound;

  if (!sound)
    return ;
  bunny_free((void*)sound->file);
  if (*type == MUSIC)
    {
      struct bunny_music *mus = (struct bunny_music*)sound;

      if (mus->sound_areas)
	{
	  bunny_map_foreach(mus->sound_areas, bunny_foreach_map_bunny_free, NULL);
	  bunny_delete_map(mus->sound_areas);
	}
      if (mus->sound_manager)
	_bunny_sound_manager_remove((t_bunny_sound_manager*)mus->sound_manager, sound);
      delete ((struct bunny_music*)sound);
    }
  else
    {
      struct bunny_effect *snd = (struct bunny_effect*)sound;

      if (snd->sound_manager)
	_bunny_sound_manager_remove((t_bunny_sound_manager*)snd->sound_manager, sound);
      if (RessourceManager.disable_manager)
	{
	  delete (sf::SoundBuffer*)snd->effect;
	  bunny_free(snd->sample);
	}
      else
	{
	  RessourceManager.TryRemove(ResManager::BUNNY_SAMPLE, snd->res_id, snd);
	  RessourceManager.TryRemove(ResManager::SF_SOUNDBUFFER, snd->res_id, snd);
	}
      delete ((struct bunny_effect*)sound);
    }
  scream_log_if("%p", "ressource,sound", sound);
}
