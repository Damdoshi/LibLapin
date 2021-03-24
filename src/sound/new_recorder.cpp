// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2021
//
// LibLapin

#include		"lapin_private.h"

t_bunny_recorder	*bunny_new_recorder(const char			*dev,
					    unsigned int		sample_rate)
{
  struct bunny_recorder	*rec;

  if ((rec = bunny_malloc(sizeof(*rec))) == NULL)
    return (NULL);
  if ((rec->device = bunny_strdup(dev)) == NULL)
    goto Delete;
  if ((rec->recorder = new (std::nothrow) sf::SoundBufferRecorder) == NULL)
    goto FailString;
  if ((eff->sound = new (std::nothrow) sf::Sound) == NULL)
    goto FailRecorder;

  rec->file = bunny_strdup("");
  rec->volume = 50;
  rec->pitch = 1;
  rec->loop = false;
  rec->position[0] = 0;
  rec->position[1] = 0;
  rec->position[2] = 0;
  rec->attenuation = 5;
  rec->playing = false;
  rec->pause = false;
  rec->recording = false;

  rec->sound_manager = NULL;
  rec->sample_per_second = sample_rate;
  rec->duration = 0;
  rec->type = RECORDER;

  rec->res_id = 0;

  scream_log_if(PATTERN, "ressource,sound", duration, (void*)NULL);
  return ((t_bunny_recorder*)rec);

 FailRecorder:
  delete rec->recorder;
 FailString:
  bunny_free(rec->device);
 Delete:
  bunny_free(rec);
  return (NULL);
}

