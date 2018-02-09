// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include		"lapin_private.h"

#define			PATTERN		"%p -> %s"

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
  eff->sound.setBuffer(*eff->effect);
  scream_log_if(PATTERN, "sound", _eff, "true");
  return (true);
}
