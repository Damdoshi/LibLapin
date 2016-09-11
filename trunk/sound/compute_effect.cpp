// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include			"lapin_private.h"

bool				bunny_compute_effect(t_bunny_effect		*effect)
{
  struct bunny_effect		*eff = (struct bunny_effect*)effect;

  return (eff->effect.loadFromSamples
	  (eff->sample,
	   eff->duration * eff->sample_per_second,
	   1,
	   eff->sample_per_second)
	  );
}

