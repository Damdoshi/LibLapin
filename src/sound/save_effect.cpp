// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include		<string.h>
#include		"lapin_private.h"

#define			PATTERN		"%s -> %p"

bool			bunny_save_effect(const t_bunny_effect		*_eff,
					  const char			*file)
{
  struct bunny_effect	*eff = (struct bunny_effect*)_eff;

  if (bunny_compute_effect((t_bunny_effect*)_eff) == false)
    return (false);
  return (eff->effect->saveToFile(file));
}

