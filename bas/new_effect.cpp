// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include		"lapin_private.h"

t_bunny_effect		*bunny_new_effect(unsigned int		duration)
{
  struct bunny_effect	*eff;

  if ((eff = new (std::nothrow) struct bunny_effect) == NULL)
    goto Fail;
  if ((eff->sample = (int16_t*)bunny_malloc(sizeof(*eff->sample) * duration * 44100)) == NULL)
    goto FailStruct;

  eff->sample_per_second = 44100;
  eff->duration = duration;
  eff->sound.setBuffer(eff->effect);
  eff->type = EFFECT;

  return ((t_bunny_effect*)eff);
  
 FailStruct:
  delete eff;
 Fail:
  return (NULL);
}

