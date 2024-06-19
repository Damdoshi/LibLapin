// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		<string.h>
#include		"lapin_private.h"

#define			PATTERN		"%f -> %p"

t_bunny_effect		*_bunny_new_effect(double		duration,
					   int			sample_per_second,
					   int			channel)
{
  struct bunny_effect	*eff;
  int			len = duration * sample_per_second;

  if ((eff = new (std::nothrow) struct bunny_effect) == NULL)
    goto Fail;
  if ((eff->effect = new (std::nothrow) sf::SoundBuffer) == NULL)
    goto FailStruct;
  if ((eff->sample = (int16_t*)bunny_malloc(sizeof(*eff->sample) * len)) == NULL)
    goto FailEffect;
  if (eff->effect->loadFromSamples(eff->sample, len, channel, sample_per_second) == false)
    goto FailSample;
  if ((eff->sound = new (std::nothrow) sf::Sound) == NULL)
    goto FailSample;

  eff->file = bunny_strdup("");
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
  eff->sample_per_second = sample_per_second;
  eff->duration = duration;
  eff->sound->setBuffer(*eff->effect);
  eff->type = EFFECT;

  eff->res_id = 0;

  scream_log_if(PATTERN, "ressource,sound", duration, (void*)NULL);
  return ((t_bunny_effect*)eff);

 FailSample:
  bunny_free(eff->sample);
 FailEffect:
  delete eff->effect;
 FailStruct:
  delete eff;
 Fail:
  scream_error_if(return (NULL), bunny_errno, PATTERN, "ressource,sound", duration, (void*)NULL);
  return (NULL);
}
