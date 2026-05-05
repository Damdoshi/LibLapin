// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2021
//
// LibLapin

#include		"lapin_private.h"

/**
 * @doc-symbol bunny_stop_record
 * @doc-module sound
 * @doc-kind function
 * @doc-order 630
 * @doc-since 13
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Stops a recorder and updates its embedded effect with captured samples.
 * @param recorder Recorder to stop.
 * @see bunny_start_record, t_bunny_recorder, bunny_compute_effect
 *
 * @doc-lang fr
 * @brief Arrête un enregistreur et met à jour son effet embarqué avec les échantillons capturés.
 * @param recorder Enregistreur à arrêter.
 * @see bunny_start_record, t_bunny_recorder, bunny_compute_effect
 */
void			bunny_stop_record(t_bunny_recorder	*recorder)
{
  struct bunny_recorder	*rec = (struct bunny_recorder*)recorder;
  int			len;

  if (rec->recording == false)
    return ;
  rec->recorder->stop();
  rec->effect = (sf::SoundBuffer*)&rec->recorder->getBuffer();
  if ((rec->sound = new (std::nothrow) sf::Sound(*rec->effect)) == NULL)
      return;
  len = rec->effect->getSampleCount();
  if (rec->sample != NULL)
    {
      bunny_free(rec->sample);
      rec->sample = NULL;
    }
  rec->duration = (double)len / rec->sample_per_second;
  if ((rec->sample = (int16_t*)bunny_malloc(sizeof(*rec->sample) * len)) == NULL)
    return ;
  memcpy(rec->sample, rec->effect->getSamples(), len * sizeof(*rec->sample));
  rec->recording = false;
}
