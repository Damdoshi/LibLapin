// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

void			__bunny_blit_tilemap(struct bunny_tilemap	*tmap,
					     const t_bunny_clipable	*_pic,
					     const t_bunny_position	*_pos,
					     const t_bunny_shader	*shader)
{
  t_bunny_position	pos;
  t_bunny_clipable	*pic = (t_bunny_clipable*)_pic;
  t_bunny_accurate_position tlcam;
  t_bunny_clipable	*save = (t_bunny_clipable*)bunny_alloca(sizeof(*save));

  bunny_clipable_copy(save, pic);

  if (_pos == NULL)
    {
      pos.x = pic->position.x;
      pos.y = pic->position.y;
    }
  else
    {
      pos.x = _pos->x;
      pos.y = _pos->y;
    }

#warning shitty code right here
  if (tmap->loop[0])
    {
      if (pos.x < 0)
	while (pos.x < 0) // shitty
	  pos.x += tmap->map_size.x * tmap->tile_size.x;
      else
	pos.x = pos.x % (int)(tmap->map_size.x * tmap->tile_size.x);
    }

  if (tmap->loop[1])
    {
      if (pos.y < 0)
	while (pos.y < 0) // shitty
	  pos.y += tmap->map_size.y * tmap->tile_size.y;
      else
	pos.y = pos.y % (int)(tmap->map_size.y * tmap->tile_size.y);
    }

  // On screen camera position
  tlcam.x = tmap->camera.x * tmap->zoom.x;
  tlcam.y = tmap->camera.y * tmap->zoom.y;

  pic->position.x = pos.x * tmap->zoom.x - tlcam.x + tmap->working->buffer.width / 2;
  pic->position.y = pos.y * tmap->zoom.y - tlcam.y + tmap->working->buffer.height / 2;

  pic->scale.x *= tmap->zoom.x;
  pic->scale.y *= tmap->zoom.y;

  tmap->type = GRAPHIC_RAM;
  bunny_blit_shader((t_bunny_buffer*)tmap->working, pic, NULL, shader);
  tmap->type = TILEMAP;

  bunny_clipable_copy(pic, save);
  bunny_freea((t_bunny_clipable*)save);
}

