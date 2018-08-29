// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include			"lapin_private.h"

bool				bunny_compute_effect(t_bunny_effect		*effect)
{
  struct bunny_effect		*eff = (struct bunny_effect*)effect;
  bool				ret;

  ret = (eff->effect->loadFromSamples
	 (eff->sample,
	  eff->duration * eff->sample_per_second,
	  1,
	  eff->sample_per_second)
	 );
  if (ret == false)
    scream_error_if(return (false), bunny_errno, "%p -> %s", "sound", effect, "false");
  scream_log_if("%p -> %s", "sound", effect, "true");
  return (true);
}

