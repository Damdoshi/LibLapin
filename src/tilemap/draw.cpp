// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

void			__bunny_draw_tilemap(struct bunny_tilemap	*tmap)
{
  // Tile cursors
  double		left, right, top, bot;
  int			depth, surface;
  int			h, v, l;
  // Final target size
  t_bunny_buffer	*buffer = (t_bunny_buffer*)tmap;
  // Utils
  t_bunny_accurate_position tlcam, tilsiz;
  int			i, index, tile;
  t_bunny_position	fpos;

  // On screen tile size
  tilsiz.x = tmap->tile_size.x * tmap->zoom.x;
  tilsiz.y = tmap->tile_size.y * tmap->zoom.y;

  // On screen camera position
  tlcam.x = tmap->camera.x * tmap->zoom.x;
  tlcam.y = tmap->camera.y * tmap->zoom.y;

  // Horizontal borders
  left = (tlcam.x - buffer->width / 2.0) / tilsiz.x;
  right = (tlcam.x + buffer->width / 2.0) / tilsiz.x;
  top = (tlcam.y - buffer->height / 2.0) / tilsiz.y;
  bot = (tlcam.y + buffer->height / 2.0) / tilsiz.y;

  // To avoid showing the outside of the map
  if (tmap->lock_borders)
    {
      fpos.x = tmap->map_size.x * tilsiz.x;
      fpos.y = tmap->map_size.y * tilsiz.y;

      if (fpos.x <= tmap->width)
	{
	  tlcam.x = fpos.x / 2.0;
	  tmap->camera.x = fpos.x / tmap->zoom.x / 2.0;
	}
      else
	{
	  if (left < 0)
	    {
	      tlcam.x -= left * tilsiz.x;
	      tmap->camera.x -= left * tilsiz.x / tmap->zoom.x;
	    }
	  else if (right >= tmap->map_size.x)
	    {
	      tlcam.x -= (right - tmap->map_size.x) * tilsiz.x;
	      tmap->camera.x -= (right - tmap->map_size.x) * tilsiz.x / tmap->zoom.x;
	    }
	}

      if (fpos.y <= tmap->height)
	{
	  tlcam.y = fpos.y / 2.0;
	  tmap->camera.y = fpos.y / tmap->zoom.y / 2.0;
	}
      else
	{
	  if (top < 0)
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
    }

  if (tmap->loop[0] == false)
    {
      left = left < 1 ? 0 : left - 1;
      right = right >= tmap->map_size.x - 1 ? tmap->map_size.x - 1 : right + 1;
    }
  else
    {
      left -= 1;
      right += 1;
    }

  if (tmap->loop[1] == false)
    {
      top = top < 1 ? 0 : top - 1;
      bot = bot >= tmap->map_size.y - 1 ? tmap->map_size.y - 1 : bot + 1;
    }
  else
    {
      top -= 1;
      bot += 1;
    }

  // Loop on tiles
  if (tmap->layer_clip[0] == -1 && tmap->layer_clip[1] == -1)
    {
      depth = 0;
      surface = tmap->nbr_layers - 1;
    }
  else if (tmap->layer_clip[0] != -1 && tmap->layer_clip[1] == -1)
    {
      depth = tmap->layer_clip[0];
      surface = tmap->nbr_layers - 1;
    }
  else if (tmap->layer_clip[0] == -1 && tmap->layer_clip[1] != -1)
    {
      depth = 0;
      surface = tmap->layer_clip[1];
    }
  else
    {
      depth = tmap->layer_clip[0];
      surface = tmap->layer_clip[1];
    }

  double elapsed;
  double now;

  elapsed = (now = bunny_get_current_time()) - tmap->last_step;
  for (l = 0; l < (int)tmap->nbr_tilesets; ++l)
    for (v = 0; v < (int)tmap->tilesets[l].nbr_animated_tiles; ++v)
      bunny_sprite_animate(tmap->tilesets[l].animated_tiles[v], elapsed);
  tmap->last_step = now;

  for (l = depth; l <= surface; ++l)
    for (v = top; v <= (int)bot; ++v)
      for (h = left; h <= (int)right; ++h)
	{
	  int oh, ov;

	  if (h < 0)
	    oh = tmap->map_size.x + h % tmap->map_size.x;
	  else
	    oh = h % tmap->map_size.x;

	  if (v < 0)
	    ov = tmap->map_size.y + v % tmap->map_size.y;
	  else
	    ov = v % tmap->map_size.y;

	  index
	    = oh + ov * tmap->map_size.x + l * tmap->map_size.x * tmap->map_size.y;
	  if ((tile = tmap->tiles[index]) == 0)
	    continue ;
	  tile -= 1;

	  for (i = 0;
	       i < (int)tmap->nbr_tilesets && tmap->tilesets[i].last_tile < tile;
	       ++i);
	  if (i >= (int)tmap->nbr_tilesets)
	    continue ;
	  if (i > 0)
	    tile -= tmap->tilesets[i - 1].last_tile;

	  if (tile < (int)tmap->tilesets[i].nbr_tiles)
	    {
	      // Simple tile
	      t_bunny_clipable	*clip = tmap->tilesets[i].tileset;

	      clip->scale.x = (tilsiz.x + 1.0) / clip->clip_width;
	      clip->scale.y = (tilsiz.y + 1.0) / clip->clip_height;

	      clip->clip_x_position = (tile % tmap->tilesets[i].tileset_size.x) *
		(tmap->tilesets[i].tile_size.x + tmap->tilesets[i].intertile.x)
		+ tmap->tilesets[i].intertile.x
		;
	      clip->clip_y_position = (tile / tmap->tilesets[i].tileset_size.x) *
		(tmap->tilesets[i].tile_size.y + tmap->tilesets[i].intertile.y)
		+ tmap->tilesets[i].intertile.y
		;

	      fpos.x = (h * tilsiz.x - tlcam.x + tmap->width / 2)
		+ tmap->working_target_diff.x;
	      fpos.y = (v * tilsiz.y - tlcam.y + tmap->height / 2)
		+ tmap->working_target_diff.y;
	      bunny_blit(&tmap->working->buffer, clip, &fpos);
	    }
	  else
	    {
	      // Animated tile
	      t_bunny_sprite	*sprite =
		tmap->tilesets[i].animated_tiles
		[tile - tmap->tilesets[i].nbr_tiles]
		;

	      sprite->clipable.scale.x =
		(tilsiz.x + 1.0) / sprite->clipable.clip_width;
	      sprite->clipable.scale.y =
		(tilsiz.y + 1.0) / sprite->clipable.clip_height;

	      fpos.x = (h * tilsiz.x - tlcam.x + tmap->width / 2)
		+ tmap->working_target_diff.x;
	      fpos.y = (v * tilsiz.y - tlcam.y + tmap->height / 2)
		+ tmap->working_target_diff.y;
	      bunny_blit(&tmap->working->buffer, &sprite->clipable, &fpos);
	    }
	}
}

