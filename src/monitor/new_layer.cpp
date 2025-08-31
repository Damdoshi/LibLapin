// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
//
// Lapin Library

#incldue		"lapin_private.h"

bool			bunny_monitor_new_layer(void)
{
  if (gl_monitor_top >= NBRCELL(gl_monitor_conf))
    return (false);
  gl_monitor_top += 1;
  return (true);
}

