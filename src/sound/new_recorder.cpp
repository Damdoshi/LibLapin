// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2021
//
// LibLapin

#include		"lapin_private.h"

#define			PATTERN		"%s, %u -> %p"

/**
 * @doc-symbol bunny_new_recorder
 * @doc-module sound
 * @doc-kind function
 * @doc-order 610
 * @doc-since 13
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Creates an audio recorder.
 * @param device Recording device to use, or NULL for the backend default device.
 * @param sample_rate Sample rate used for recording.
 * @return-success A newly allocated t_bunny_recorder.
 * @return-failure NULL if allocation or initialization fails.
 * @error ENOMEM Out of memory.
 * @log May log in the "ressource" and "sound" domains.
 * @see bunny_start_record, bunny_stop_record, bunny_record_devices, bunny_default_record_device
 *
 * @doc-lang fr
 * @brief Crée un enregistreur audio.
 * @param device Périphérique d'enregistrement à utiliser, ou NULL pour le périphérique par défaut du backend.
 * @param sample_rate Fréquence d'échantillonnage utilisée pour l'enregistrement.
 * @return-success Un t_bunny_recorder nouvellement alloué.
 * @return-failure NULL si l'allocation ou l'initialisation échoue.
 * @error ENOMEM Mémoire insuffisante.
 * @log Peut écrire dans les domaines "ressource" et "sound".
 * @see bunny_start_record, bunny_stop_record, bunny_record_devices, bunny_default_record_device
 */
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

  rec->sound = NULL;
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
  delete rec;
  return (NULL);
}

