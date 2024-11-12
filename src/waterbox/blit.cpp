// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
// EFRITS SAS 2022-2025
// Pentacle Technologie 2008-2025
//
// Bunny Library

#include		"lapin_private.h"

void			wbpixel(t_bunny_buffer				*buffer,
				t_bunny_waterbox			*wb,
				int					x,
				int					y,
				int					z,
				int					px,
				int					py)
{
  unsigned int		wp = x + y * wb->size.x + z * wb->size.x * wb->size.y;
  int			point = 0;
  t_bunny_position	ppos{px, py};

  wp *= 3;
  
  point |= bunny_bitfield_get(wb->boxes[wb->current_box], wp + 0) << 0;
  point |= bunny_bitfield_get(wb->boxes[wb->current_box], wp + 1) << 1;
  point |= bunny_bitfield_get(wb->boxes[wb->current_box], wp + 2) << 2;
  if (point & BWP_WATER || point & BWP_SOURCE)
    bunny_set_pixel(buffer, ppos, wb->color.full);
}

void			bunny_waterbox_blit(t_bunny_buffer		*px,
					    t_bunny_waterbox		*wb,
					    t_bunny_waterbox_view	slice,
					    int				depth)
{
  int			x;
  int			y;
  int			z;

  if (slice == BWS_HORIZONTAL)
    {
      for (x = 0; x < wb->size.x; ++x)
	for (y = 0; y < wb->size.y; ++y)
	  if (depth != -1)
	    wbpixel(px, wb, x, y, depth, x, y);
	  else
	    for (z = 0; z < wb->depth; ++z)
	      wbpixel(px, wb, x, y, z, x, y);
      return ;
    }
  
  for (x = 0; x < wb->size.x; ++x)
    for (y = 0; y < wb->depth; ++y)
      if (depth != -1)
	wbpixel(px, wb, x, depth, y, x, y);
      else
	for (z = 0; z < wb->size.y; ++z)
	  wbpixel(px, wb, x, z, y, x, y);
}
