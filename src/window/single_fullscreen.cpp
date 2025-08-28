// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
//
// Lapin library

#include		"lapin_private.h"

t_bunny_window		*bunny_single_fullscreen(const char	*name)
{
  const t_bunny_area	*area;
  
  if ((area = bunny_list_autonomous_monitors()) == NULL)
    return (NULL);
  return (bunny_start(area->w, area->h, true, name));
}
