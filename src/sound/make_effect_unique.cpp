// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

#define			PATTERN		"%p -> %s"

/**
 * @doc-symbol bunny_make_effect_unique
 * @doc-module sound
 * @doc-kind function
 * @doc-order 570
 * @doc-since 12
 * @doc-until latest
 * @doc-level expert
 *
 * @doc-lang en
 * @brief Detaches an effect from shared low-level resources.
 * @description Call this before editing samples when several effects may share the same loaded file.
 * @param eff Effect that must become unique.
 * @return-success true if the effect is now unique, including when it already was.
 * @return-failure false if duplication fails.
 * @error ENOMEM Out of memory.
 * @log May log in the "sound" domain.
 * @see bunny_load_effect, bunny_compute_effect
 *
 * @doc-lang fr
 * @brief Détache un effet de ses ressources bas niveau partagées.
 * @description Appelez cette fonction avant de modifier les échantillons lorsque plusieurs effets peuvent partager le même fichier chargé.
 * @param eff Effet qui doit devenir unique.
 * @return-success true si l'effet est désormais unique, y compris lorsqu'il l'était déjà.
 * @return-failure false si la duplication échoue.
 * @error ENOMEM Mémoire insuffisante.
 * @log Peut écrire dans le domaine "sound".
 * @see bunny_load_effect, bunny_compute_effect
 */
bool			bunny_make_effect_unique(t_bunny_effect	*_eff)
{
  struct bunny_effect *eff = (struct bunny_effect*)_eff;
  sf::SoundBuffer *snd;
  int16_t *sample;

  if (!eff->res_id)
    return (true);
  if (RessourceManager.IsAlone(ResManager::SF_SOUNDBUFFER, eff->res_id, eff))
    {
      RessourceManager.Extract(ResManager::SF_SOUNDBUFFER, eff->res_id, eff);
      RessourceManager.Extract(ResManager::BUNNY_SAMPLE, eff->res_id, eff);
      scream_log_if(PATTERN, "sound", _eff, "true");
      return (true);
    }

  if ((snd = new (std::nothrow) sf::SoundBuffer) == NULL)
    scream_error_if(return (false), ENOMEM, PATTERN, "sound", _eff, "false");
  if ((sample = (int16_t*)bunny_malloc(sizeof(*sample) * eff->effect->getSampleCount())) == NULL)
    {
      delete snd;
      scream_error_if(return (false), ENOMEM, PATTERN, "sound", _eff, "false");
    }

  RessourceManager.TryRemove(ResManager::SF_SOUNDBUFFER, eff->res_id, eff);
  RessourceManager.TryRemove(ResManager::BUNNY_SAMPLE, eff->res_id, eff);

  memcpy(sample, eff->sample, sizeof(*sample) * eff->effect->getSampleCount());

  eff->sample = sample;
  eff->effect = snd;
  eff->sound->setBuffer(*eff->effect);
  scream_log_if(PATTERN, "sound", _eff, "true");
  return (true);
}
