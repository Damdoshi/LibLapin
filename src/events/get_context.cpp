// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Lapin Library

#include		<string.h>
#include		"lapin_private.h"

void			bunny_get_context(t_bunny_context		*context)
{
  memcpy(context, &gl_callback, sizeof(*context));
}

