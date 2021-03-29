// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2021
//
// LibLapin

#include		"lapin_private.h"

void			bunny_stop_record(t_bunny_recorder	*recorder)
{
  struct bunny_recorder	*rec = (struct bunny_recorder*)recorder;
  int			len;

  if (rec->recording == false)
    return ;
  rec->recorder->stop();
  rec->effect = (sf::SoundBuffer*)&rec->recorder->getBuffer();
  rec->sound->setBuffer(*rec->effect);

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
