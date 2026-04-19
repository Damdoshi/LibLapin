// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

void			bunny_maximize_inside(t_bunny_clipable		*tr,
					      const t_bunny_clipable	*cn)
{
  tr->scale.x = (double)cn->buffer.width / tr->buffer.width;
  tr->scale.y = (double)cn->buffer.height / tr->buffer.height;

  tr->scale.x = (int)tr->scale.x;
  tr->scale.y = (int)tr->scale.y;

  if (tr->scale.x < tr->scale.y)
    tr->scale.y = tr->scale.x;
  else
    tr->scale.x = tr->scale.y;

  tr->position.x = cn->buffer.width / 2.0;
  tr->position.y = cn->buffer.height / 2.0;
  tr->origin.x = tr->buffer.width / 2.0;
  tr->origin.y = tr->buffer.height / 2.0;
}

