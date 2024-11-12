// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
// EFRITS SAS 2022-2025
// Pentacle Technologie 2008-2025
//
// Bunny Library

#include		"lapin_private.h"

t_bunny_waterbox	*bunny_new_waterbox(int				w,
					    int				h,
					    int				d)
{
  t_bunny_waterbox	*wb = new (std::nothrow) t_bunny_waterbox;
  int			siz;

  wb->size.x = w;
  wb->size.y = h;
  wb->depth = d;
  siz = w * h * d * 3;
  if ((wb->boxes[0] = bunny_new_bitfield(siz)) == NULL)
    goto DeleteWB;
  if ((wb->boxes[1] = bunny_new_bitfield(siz)) == NULL)
    goto DeleteBox;
  wb->current_box = 0;
  wb->color.full = ALPHA(128, BLUE);
  return (wb);

 DeleteBox:
  bunny_delete_bitfield(wb->boxes[0]);
 DeleteWB:
  delete wb;
  return (NULL);
}
