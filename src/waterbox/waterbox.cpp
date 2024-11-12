// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
// EFRITS SAS 2022-2025
// Pentacle Technologie 2008-2025
//
// Bunny Library

#include		"lapin_private.h"

static t_bunny_waterbox_point get(t_bunny_waterbox			*wb,
				  t_bunny_bitfield			*box,
				  int					x,
				  int					y,
				  int					z)
{
  int pos = x + y * wb->size.x + z * wb->size.x * wb->size.y;
  int point = 0;

  pos *= 3;
  
  point |= bunny_bitfield_get(box, pos + 0) << 0;
  point |= bunny_bitfield_get(box, pos + 1) << 1;
  point |= bunny_bitfield_get(box, pos + 2) << 2;
  return ((t_bunny_waterbox_point)point);
}

void			 _wbset(t_bunny_waterbox			*wb,
				t_bunny_bitfield			*bf,
				int					x,
				int					y,
				int					z,
				t_bunny_waterbox_point			wp)
{
  int pos = x + y * wb->size.x + z * wb->size.x * wb->size.y;

  pos *= 3;
  
  if ((wp >> 0) & 1)
    bunny_bitfield_set(bf, pos + 0);
  else
    bunny_bitfield_clr(bf, pos + 0);
  if ((wp >> 1) & 1)
    bunny_bitfield_set(bf, pos + 1);
  else
    bunny_bitfield_clr(bf, pos + 1);
  if ((wp >> 2) & 1)
    bunny_bitfield_set(bf, pos + 2);
  else
    bunny_bitfield_clr(bf, pos + 2);
}

void			bunny_waterbox(t_bunny_waterbox		*wb)
{
  t_bunny_bitfield	*cbox = wb->boxes[wb->current_box];
  // wb->current_box = bunny_rclamp(wb->current_box + 1, 0, NBRCELL(wb->boxes) - 1);
  t_bunny_bitfield	*nbox = wb->boxes[wb->current_box + 1];
  int			x;
  int			y;
  int			z;

  memset(nbox, 0, ceil(wb->size.x * wb->size.y * wb->depth / 8.0));
  for (z = 0; z < wb->depth; ++z)
    for (y = 0; y < wb->size.y; ++y)
      for (x = 0; x < wb->size.x; ++x)
	{
	  t_bunny_waterbox_point point;

	  if ((point = get(wb, cbox, x, y, z)) < BWP_WATER)
	    continue ;
	  if (point == BWP_WATER)
	    {

	      continue ;
	    }
	  int		nbr;

	  nbr = (int)point - (int)BWP_SOURCE + 1;
	  // Créer de l'eau
	}
}

