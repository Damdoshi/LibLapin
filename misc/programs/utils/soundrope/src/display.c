/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2018
**
** Sound Rope
*/

#include		<limits.h>
#include		"sound_rope.h"

typedef struct		s_bva
{
  size_t		length;
  t_bunny_vertex	vertex[1024 * 1024 * 16];
}			t_bva;

t_bunny_response	soundrope_display(t_sound_rope		*rope)
{
  static t_bva		bva;
  int			dist;
  size_t		i;

  bunny_clear(&rope->win->buffer, PINK2);
  bva.length = rope->win->buffer.width / rope->zoom;
  for (i = 0; i < bva.length; ++i)
    {
      bva.vertex[i].pos.x = ((double)i / bva.length) * rope->win->buffer.width;
      bva.vertex[i].pos.y =
	((int)rope->output_effect->sample[i + rope->index] / SHRT_MAX)
	* rope->win->buffer.height / 2
	+ rope->win->buffer.height / 2;
      dist = abs(bva.vertex[i].pos.y - rope->win->buffer.height / 2);
      bva.vertex[i].color = GRAY(dist);
    }
  bunny_set_geometry(&rope->win->buffer, BGY_LINE_STRIP, (t_bunny_vertex_array*)&bva, NULL);
  bunny_display(rope->win);
  return (GO_ON);
}
