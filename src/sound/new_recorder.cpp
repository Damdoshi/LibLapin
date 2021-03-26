// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2021
//
// LibLapin

#include		"lapin_private.h"

#define			PATTERN		"%s, %u -> %p"

t_bunny_recorder	*bunny_new_recorder(const char			*dev,
					    unsigned int		sample_rate)
{
  struct bunny_recorder	*rec;

  if ((rec = new (std::nothrow) struct bunny_recorder) == NULL)
    return (NULL);
  memset(rec, 0, sizeof(*rec));
  if ((rec->device = bunny_strdup(dev)) == NULL)
    goto Delete;
  if ((rec->recorder = new (std::nothrow) sf::SoundBufferRecorder) == NULL)
    goto FailString;
  if (rec->recorder->setDevice(std::string(dev)) == false)
    goto FailRecorder;
  if ((rec->sound = new (std::nothrow) sf::Sound) == NULL)
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

  scream_log_if(PATTERN, "ressource,sound", dev, sample_rate, (void*)NULL);
  return ((t_bunny_recorder*)rec);

 FailRecorder:
  delete rec->recorder;
 FailString:
  bunny_free(rec->device);
 Delete:
  bunny_free(rec);
  return (NULL);
}

