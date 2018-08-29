// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include			<assert.h>
#include			"lapin_private.h"

#define				do_assert(a, b) printf("(%48s == %48s). Ptr are %8p and %8p\n", #a, #b, a, b); assert((void*)a == (void*)b);

void				bunny_consistancy(void)
{
  t_bunny_window		*usr_win = NULL;
  struct bunny_window		*prv_win = NULL;

  do_assert(&usr_win->buffer._private[0], &prv_win->type);
  do_assert(&usr_win->buffer._private[1], &prv_win->window);
  do_assert(&usr_win->buffer.width, &prv_win->width);
  do_assert(&usr_win->buffer.height, &prv_win->height);
  do_assert(&usr_win->name, &prv_win->window_name);

  t_bunny_pixelarray		*usr_pix = NULL;
  struct bunny_pixelarray	*prv_pix = NULL;

  do_assert(&usr_pix->clipable.buffer._private[0], &prv_pix->type);
  do_assert(&usr_pix->clipable.buffer._private[1], &prv_pix->unused);
  do_assert(&usr_pix->clipable.buffer.width, &prv_pix->width);
  do_assert(&usr_pix->clipable.buffer.height, &prv_pix->height);
  do_assert(&usr_pix->clipable.clip_x_position, &prv_pix->rect.x);
  do_assert(&usr_pix->clipable.clip_y_position, &prv_pix->rect.y);
  do_assert(&usr_pix->clipable.clip_width, &prv_pix->rect.w);
  do_assert(&usr_pix->clipable.clip_height, &prv_pix->rect.h);
  do_assert(&usr_pix->clipable.position.x, &prv_pix->position.x);
  do_assert(&usr_pix->clipable.position.y, &prv_pix->position.y);
  do_assert(&usr_pix->clipable.origin.x, &prv_pix->origin.x);
  do_assert(&usr_pix->clipable.origin.y, &prv_pix->origin.y);
  do_assert(&usr_pix->clipable.scale.x, &prv_pix->scale.x);
  do_assert(&usr_pix->clipable.scale.y, &prv_pix->scale.y);
  do_assert(&usr_pix->clipable.rotation, &prv_pix->rotation);
  do_assert(&usr_pix->clipable.color_mask, &prv_pix->color_mask);
  do_assert(&usr_pix->pixels, &prv_pix->rawpixels);

  t_bunny_picture		*usr_pic = NULL;
  struct bunny_picture		*prv_pic = NULL;

  do_assert(&usr_pic->buffer._private[0], &prv_pic->type);
  do_assert(&usr_pic->buffer._private[1], &prv_pic->texture);
  do_assert(&usr_pic->buffer.width, &prv_pic->width);
  do_assert(&usr_pic->buffer.height, &prv_pic->height);
  do_assert(&usr_pic->clip_x_position, &prv_pic->rect.x);
  do_assert(&usr_pic->clip_y_position, &prv_pic->rect.y);
  do_assert(&usr_pic->clip_width, &prv_pic->rect.w);
  do_assert(&usr_pic->clip_height, &prv_pic->rect.h);
  do_assert(&usr_pic->position.x, &prv_pic->position.x);
  do_assert(&usr_pic->position.y, &prv_pic->position.y);
  do_assert(&usr_pic->origin.x, &prv_pic->origin.x);
  do_assert(&usr_pic->origin.y, &prv_pic->origin.y);
  do_assert(&usr_pic->scale.x, &prv_pic->scale.x);
  do_assert(&usr_pic->scale.y, &prv_pic->scale.y);
  do_assert(&usr_pic->rotation, &prv_pic->rotation);
  do_assert(&usr_pic->color_mask, &prv_pic->color_mask);

  t_bunny_effect		*usr_eff = NULL;
  struct bunny_effect		*prv_eff = NULL;

  do_assert(&usr_eff->sound._private[0], &prv_eff->type);
  do_assert(&usr_eff->sound.file, &prv_eff->file);
  do_assert(&usr_eff->sample_per_second, &prv_eff->sample_per_second);
  do_assert(&usr_eff->duration, &prv_eff->duration);
  do_assert(&usr_eff->sample, &prv_eff->sample);

  t_bunny_sound_sprite		*usr_spr = NULL;
  struct bunny_music		*prv_spr = NULL;

  do_assert(&usr_spr->soundset.sound._private[0], &prv_spr->type);
  do_assert(&usr_spr->soundset.sound.file, &prv_spr->file);
  do_assert(&usr_spr->soundset.sound.volume, &prv_spr->volume);
  do_assert(&usr_spr->soundset.sound.pitch, &prv_spr->pitch);
  do_assert(&usr_spr->soundset.sound.loop, &prv_spr->loop);
  do_assert(&usr_spr->soundset.sound.position[0], &prv_spr->position[0]);
  do_assert(&usr_spr->soundset.sound.attenuation, &prv_spr->attenuation);
  do_assert(&usr_spr->soundset.sound.playing, &prv_spr->playing);
  do_assert(&usr_spr->soundset.sound.pause, &prv_spr->pause);
  do_assert(&usr_spr->soundset.duration, &prv_spr->duration);
  do_assert(&usr_spr->sound_areas, &prv_spr->sound_areas);
  do_assert(&usr_spr->last_played_slice, &prv_spr->last_played_slice);
  do_assert(&usr_spr->track, &prv_spr->track);

  t_bunny_tilemap		*usr_tmap = NULL;
  struct bunny_tilemap		*prv_tmap = NULL;

  do_assert(&usr_tmap->_private[0], &prv_tmap->res_id);
  do_assert(&usr_tmap->_private[1], &prv_tmap->tex);
  do_assert(&usr_tmap->_private[2], &prv_tmap->sprite);
  do_assert(&usr_tmap->map_size, &prv_tmap->map_size);
  do_assert(&usr_tmap->tiles, &prv_tmap->tiles);
  do_assert(&usr_tmap->tile_size, &prv_tmap->tile_size);
  do_assert(&usr_tmap->camera, &prv_tmap->camera);
  do_assert(&usr_tmap->zoom, &prv_tmap->zoom);
  do_assert(&usr_tmap->rotation, &prv_tmap->tile_rotation);
  do_assert(&usr_tmap->lock_borders, &prv_tmap->lock_borders);

  bunny_printl("If this text appears, it menas that all tests were successful.");
}
