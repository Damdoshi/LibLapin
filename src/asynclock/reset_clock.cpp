// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

double			bunny_reset_clock(void)
{
  gl_bunny_current_time.restart();
  scream_log_if("%s", "asynclock", "");
  return (0);
}

