// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include		"lapin_private.h"

/**
 * @doc-symbol bunny_delete_sound
 * @doc-module sound
 * @doc-kind macro
 * @doc-order 550
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Deletes a music, sound effect, sound sprite or recorder.
 * @description The public C11 macro accepts derived sound types and calls _bunny_delete_sound.
 * @param snd Sound object to destroy. NULL is accepted.
 * @log May log in the "ressource" and "sound" domains.
 * @see t_bunny_sound, bunny_load_music, bunny_load_effect, bunny_new_effect
 *
 * @doc-lang fr
 * @brief Détruit une musique, un effet sonore, un sound sprite ou un enregistreur.
 * @description La macro C11 publique accepte les types sonores dérivés et appelle _bunny_delete_sound.
 * @param snd Objet sonore à détruire. NULL est accepté.
 * @log Peut écrire dans les domaines "ressource" et "sound".
 * @see t_bunny_sound, bunny_load_music, bunny_load_effect, bunny_new_effect
 */
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
	  // SI C'EST UN SOUND SPRITE
	  bunny_map_foreach(mus->sound_areas, bunny_foreach_map_bunny_free, NULL);
	  bunny_delete_map(mus->sound_areas);
	}
      if (mus->sound_manager)
	_bunny_sound_manager_remove((t_bunny_sound_manager*)mus->sound_manager, sound);
      delete mus;
    }
  else if (*type == RECORDER)
    {
      struct bunny_recorder *rec = (struct bunny_recorder*)sound;

      if (rec->device)
	bunny_free(rec->device);
      if (rec->sample)
	bunny_free(rec->sample);
      delete rec->recorder;
      if (rec->sound)
	delete rec->sound;
      delete rec;
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
      delete snd;
    }
  scream_log_if("%p", "ressource,sound", sound);
}
