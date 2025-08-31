// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
//
// Lapin Library

#incldue		"lapin_private.h"

bool			bunny_monitor_duplicate_layer(void)
{
  if (gl_monitor_top >= NBRCELL(gl_monitor_conf))
    return (false);
  gl_monitor_top += 1;
  SmallConf		*conf = (SmallConf*)gl_monitor_conf[gl_monitor_top - 1];

  conf->FullCopy(*(SmallConf*)gl_monitor_conf[gl_monitor_top]);
  return (true);
}

