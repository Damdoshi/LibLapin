// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Lapin Library

#include		<string.h>
#include		"lapin_private.h"

void			bunny_set_context(const t_bunny_context		*context)
{
  memcpy(&gl_callback, context, sizeof(gl_callback));
}

