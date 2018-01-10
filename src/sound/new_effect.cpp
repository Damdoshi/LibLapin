// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include		<string.h>
#include		"lapin_private.h"

#define			PATTERN		"%f -> %p"

t_bunny_effect		*bunny_new_effect(double		duration)
{
  struct bunny_effect	*eff;

  if ((eff = new (std::nothrow) struct bunny_effect) == NULL)
    goto Fail;
  if ((eff->effect = new (std::nothrow) sf::SoundBuffer) == NULL)
    goto FailStruct;
  if ((eff->sample = (int16_t*)bunny_malloc(sizeof(*eff->sample) * duration * 44100)) == NULL)
    goto FailEffect;

  eff->file = strdup("");
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
  eff->sample_per_second = SAMPLE_PER_SECONDS;
  eff->duration = duration;
  eff->sound.setBuffer(*eff->effect);
  eff->type = EFFECT;

  eff->res_id = 0;

  scream_log_if(PATTERN, "ressource,sound", duration, (void*)NULL);
  return ((t_bunny_effect*)eff);

 FailEffect:
  delete eff->effect;
 FailStruct:
  delete eff;
 Fail:
  scream_error_if(return (NULL), bunny_errno, PATTERN, "ressource,sound", duration, (void*)NULL);
  return (NULL);
}
