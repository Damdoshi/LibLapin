// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include			"lapin_private.h"

void				__bunny_tilemap_lock_borders(t_bunny_accurate_position	&tilsiz,
							     t_bunny_accurate_position	&tlcam,
							     struct bunny_tilemap	*tmap,
							     double			left,
							     double			right,
							     double			top,
							     double			bot)
{
  t_bunny_accurate_position	fpos = {
    .x = tmap->map_size.x * tilsiz.x,
    .y = tmap->map_size.y * tilsiz.y
  };

  if (fpos.x <= tmap->width)
    {
      tlcam.x = fpos.x / 2.0;
      tmap->camera.x = fpos.x / tmap->zoom.x / 2.0;
    }
  else if (left < 0)
    {
      tlcam.x -= left * tilsiz.x;
      tmap->camera.x -= left * tilsiz.x / tmap->zoom.x;
    }
  else if (right >= tmap->map_size.x)
    {
      tlcam.x -= (right - tmap->map_size.x) * tilsiz.x;
      tmap->camera.x -= (right - tmap->map_size.x) * tilsiz.x / tmap->zoom.x;
    }

  if (fpos.y <= tmap->height)
    {
      tlcam.y = fpos.y / 2.0;
      tmap->camera.y = fpos.y / tmap->zoom.y / 2.0;
    }
  else if (top < 0)
    {
      tlcam.y -= top * tilsiz.y;
      tmap->camera.y -= top * tilsiz.y / tmap->zoom.y;
    }
  else if (bot >= tmap->map_size.y)
    {
      tlcam.y -= (bot - tmap->map_size.y) * tilsiz.y - 1;
      tmap->camera.y -= (bot - tmap->map_size.y) * tilsiz.y / tmap->zoom.y;
    }
}
