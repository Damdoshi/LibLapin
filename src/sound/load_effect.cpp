// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include		<string.h>
#include		"lapin_private.h"

#define			PATTERN		"%s -> %p"

/**
 * @doc-symbol bunny_load_effect
 * @doc-module sound
 * @doc-kind function
 * @doc-order 200
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Opens a sound effect file or a sound effect configuration file.
 * @description A sound effect is loaded in memory. Several loads of the same file may share low-level resources.
 * @param file Sound file or configuration file to open. Supported sound formats are wav and ogg.
 * @return-success A valid t_bunny_effect pointer.
 * @return-failure NULL if the effect cannot be loaded.
 * @error ENOMEM Out of memory.
 * @error EINVAL Invalid file format.
 * @error ENOENT The file was not found.
 * @error BE_SYNTAX_ERROR The configuration file contains a syntax error.
 * @log May log in the "ressource", "configuration", "syntax" and "sound" domains.
 * @see bunny_new_effect, bunny_compute_effect, bunny_make_effect_unique, bunny_delete_sound
 *
 * @doc-lang fr
 * @brief Ouvre un fichier d'effet sonore ou un fichier de configuration d'effet sonore.
 * @description Un effet sonore est chargé en mémoire. Plusieurs chargements du même fichier peuvent partager des ressources bas niveau.
 * @param file Fichier sonore ou fichier de configuration à ouvrir. Les formats sonores supportés sont wav et ogg.
 * @return-success Un pointeur t_bunny_effect valide.
 * @return-failure NULL si l'effet ne peut pas être chargé.
 * @error ENOMEM Mémoire insuffisante.
 * @error EINVAL Format de fichier invalide.
 * @error ENOENT Le fichier est introuvable.
 * @error BE_SYNTAX_ERROR Le fichier de configuration contient une erreur de syntaxe.
 * @log Peut écrire dans les domaines "ressource", "configuration", "syntax" et "sound".
 * @see bunny_new_effect, bunny_compute_effect, bunny_make_effect_unique, bunny_delete_sound
 */
t_bunny_effect		*bunny_load_effect(const char		*file)
{
  struct bunny_effect	*eff;
  size_t		len;
  uint64_t		hash;

  if (bunny_which_format(file) != BC_CUSTOM)
    {
      t_bunny_sound	*pc = NULL;

      if (bunny_set_sound_attribute(file, &pc, NULL, false) == false)
	return (NULL);
      return ((t_bunny_effect*)pc);
    }
  hash = bunny_hash(BH_FNV, file, strlen(file));

  /*
***** READ EFFECT IS NOT IMPLEMENTED
  if (gl_bunny_ressource_ciphering)
    {
      void		*data;
      size_t		siz;

      if (bunny_load_file(file, &data, &siz) == -1)
	return (NULL);
      gl_bunny_ressource_ciphering((char*)data, siz, gl_bunny_ressource_data, false);
      if ((eff = (struct bunny_effect*)
	   bunny_read_effect_id(data, siz, file)) == NULL)
	return (NULL);
      bunny_delete_file(data, file);
      return ((t_bunny_effect*)eff);
    }
  */

  if ((eff = new (std::nothrow) struct bunny_effect) == NULL)
    goto Fail;
  if (RessourceManager.disable_manager ||
      (eff->effect = (sf::SoundBuffer*)RessourceManager.TryGet(ResManager::SF_SOUNDBUFFER, hash)) == NULL)
    {
      if ((eff->effect = new (std::nothrow) sf::SoundBuffer) == NULL)
	goto FailStruct;
      if ((eff->effect->loadFromFile(file)) == false)
	goto FailEffect;
      len = eff->effect->getSampleCount();
      if ((eff->sample = (int16_t*)bunny_malloc(sizeof(*eff->sample) * len)) == NULL)
	goto FailEffect;
      memcpy(eff->sample, eff->effect->getSamples(), len * sizeof(*eff->sample));
      if ((eff->sound = new (std::nothrow) sf::Sound(*eff->effect)) == NULL)
	goto FailSample;
    }
  else
    {
      eff->sample = (int16_t*)RessourceManager.TryGet(ResManager::BUNNY_SAMPLE, hash);
      if ((eff->sound = new (std::nothrow) sf::Sound(*eff->effect)) == NULL)
	goto FailStruct;
    }

  if (RessourceManager.disable_manager == false)
    {
      RessourceManager.AddToPool(ResManager::SF_SOUNDBUFFER, file, hash, eff, eff->effect);
      RessourceManager.AddToPool(ResManager::BUNNY_SAMPLE, file, hash, eff, eff->sample);
    }

  eff->res_id = hash;

  eff->file = bunny_strdup(file);
  eff->volume = 50;
  eff->pitch = 1;
  eff->loop = false;
  eff->position[0] = 0;
  eff->position[1] = 0;
  eff->position[2] = 0;
  eff->attenuation = 5;
  eff->playing = false;
  eff->pause = false;
  eff->sound_manager = NULL;

  eff->sample_per_second = eff->effect->getSampleRate();
  eff->duration = (double)eff->effect->getSampleCount() / eff->sample_per_second;
  eff->type = EFFECT;

  scream_log_if(PATTERN, "ressource,sound", file, eff);
  return ((t_bunny_effect*)eff);

 FailSample:
  bunny_free(eff->sample);
 FailEffect:
  delete eff->effect;
 FailStruct:
  delete eff;
 Fail:
  scream_error_if(return (NULL), bunny_errno, PATTERN, "ressource,sound", file, (void*)NULL);
  return (NULL);
}
