// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin Library

#include		<unistd.h>
#include		"lapin_private.h"

void			bunny_display_monitored_value(t_bunny_font		*f,
						      const char		*n)
{
  _bunny_monitor_prepare_buffer(&bunny_big_buffer[0], sizeof(bunny_big_buffer), n);
  f->string = &bunny_big_buffer[0];
  bunny_draw(&f->clipable);
  f->string = NULL;
}

