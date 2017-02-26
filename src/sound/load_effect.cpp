// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include		<string.h>
#include		"lapin_private.h"

t_bunny_effect		*bunny_load_effect(const char		*file)
{
  struct bunny_effect	*eff;
  size_t		len;
  
  if ((eff = new (std::nothrow) struct bunny_effect) == NULL)
    goto Fail;
  if ((eff->effect.loadFromFile(file)) == false)
    goto FailStruct;

  eff->file = strdup(file);
  eff->sample_per_second = eff->effect.getSampleRate();
  eff->duration = (double)eff->effect.getSampleCount() / eff->sample_per_second;

  len = eff->effect.getSampleCount();
  if ((eff->sample = (int16_t*)bunny_malloc(sizeof(*eff->sample) * len)) == NULL)
    goto FailStruct;
  memcpy(eff->sample, eff->effect.getSamples(), len * sizeof(*eff->sample));

  eff->sound.setBuffer(eff->effect);
  eff->type = EFFECT;

  BUNNY_LOG(fprintf(stderr, "%s: Returning %p.\n", __PRETTY_FUNCTION__, eff));
  
  return ((t_bunny_effect*)eff);

 FailStruct:
  delete eff;
 Fail:
  return (NULL);
}
