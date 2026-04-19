// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include <assert.h>
#include <stdio.h>
#include "lapin_private.h"

#define CHECK_ADDR(a, b) do { \
  const void *__a = (const void*)(a); \
  const void *__b = (const void*)(b); \
  printf("(%48s == %48s). Ptr are %8p and %8p\n", #a, #b, __a, __b); \
  assert(__a == __b); \
} while (0)

void bunny_consistancy(void)
{
  t_bunny_window *usr_win = NULL;
  struct bunny_window *prv_win = NULL;

  CHECK_ADDR(&usr_win->buffer._private[0], &prv_win->type);
  CHECK_ADDR(&usr_win->buffer._private[1], &prv_win->window);
  CHECK_ADDR(&usr_win->buffer._private[2], &prv_win->nwindow);
  CHECK_ADDR(&usr_win->buffer._private[3], &prv_win->glactive);
  CHECK_ADDR(&usr_win->buffer._private[4], &prv_win->unused);
  CHECK_ADDR(&usr_win->buffer.width, &prv_win->width);
  CHECK_ADDR(&usr_win->buffer.height, &prv_win->height);
  CHECK_ADDR(&usr_win->buffer.data[0], &prv_win->data[0]);
  CHECK_ADDR(&usr_win->name, &prv_win->window_name);
  CHECK_ADDR(&usr_win->style, &prv_win->style);
  CHECK_ADDR(&usr_win->position, &prv_win->position);

  t_bunny_picture *usr_pic = NULL;
  struct bunny_picture *prv_pic = NULL;

  CHECK_ADDR(&usr_pic->buffer._private[0], &prv_pic->type);
  CHECK_ADDR(&usr_pic->buffer._private[1], &prv_pic->texture);
  CHECK_ADDR(&usr_pic->buffer._private[2], &prv_pic->ntexture);
  CHECK_ADDR(&usr_pic->buffer._private[3], &prv_pic->glactive);
  CHECK_ADDR(&usr_pic->buffer._private[4], &prv_pic->duplicate);
  CHECK_ADDR(&usr_pic->buffer.width, &prv_pic->width);
  CHECK_ADDR(&usr_pic->buffer.height, &prv_pic->height);
  CHECK_ADDR(&usr_pic->buffer.data[0], &prv_pic->data[0]);
  CHECK_ADDR(&usr_pic->clip_x_position, &prv_pic->rect.x);
  CHECK_ADDR(&usr_pic->clip_y_position, &prv_pic->rect.y);
  CHECK_ADDR(&usr_pic->clip_width, &prv_pic->rect.w);
  CHECK_ADDR(&usr_pic->clip_height, &prv_pic->rect.h);
  CHECK_ADDR(&usr_pic->position.x, &prv_pic->position.x);
  CHECK_ADDR(&usr_pic->position.y, &prv_pic->position.y);
  CHECK_ADDR(&usr_pic->origin.x, &prv_pic->origin.x);
  CHECK_ADDR(&usr_pic->origin.y, &prv_pic->origin.y);
  CHECK_ADDR(&usr_pic->scale.x, &prv_pic->scale.x);
  CHECK_ADDR(&usr_pic->scale.y, &prv_pic->scale.y);
  CHECK_ADDR(&usr_pic->rotation, &prv_pic->rotation);
  CHECK_ADDR(&usr_pic->color_mask, &prv_pic->color_mask);
  CHECK_ADDR(&usr_pic->smooth, &prv_pic->smooth);
  CHECK_ADDR(&usr_pic->mosaic, &prv_pic->mosaic);

  t_bunny_pixelarray *usr_pix = NULL;
  struct bunny_pixelarray *prv_pix = NULL;

  CHECK_ADDR(&usr_pix->clipable.buffer._private[0], &prv_pix->type);
  CHECK_ADDR(&usr_pix->clipable.buffer._private[1], &prv_pix->unused);
  CHECK_ADDR(&usr_pix->clipable.buffer._private[2], &prv_pix->ntexture);
  CHECK_ADDR(&usr_pix->clipable.buffer._private[3], &prv_pix->glactive);
  CHECK_ADDR(&usr_pix->clipable.buffer._private[4], &prv_pix->duplicate);
  CHECK_ADDR(&usr_pix->clipable.buffer.width, &prv_pix->width);
  CHECK_ADDR(&usr_pix->clipable.buffer.height, &prv_pix->height);
  CHECK_ADDR(&usr_pix->clipable.buffer.data[0], &prv_pix->data[0]);
  CHECK_ADDR(&usr_pix->clipable.clip_x_position, &prv_pix->rect.x);
  CHECK_ADDR(&usr_pix->clipable.clip_y_position, &prv_pix->rect.y);
  CHECK_ADDR(&usr_pix->clipable.clip_width, &prv_pix->rect.w);
  CHECK_ADDR(&usr_pix->clipable.clip_height, &prv_pix->rect.h);
  CHECK_ADDR(&usr_pix->clipable.position.x, &prv_pix->position.x);
  CHECK_ADDR(&usr_pix->clipable.position.y, &prv_pix->position.y);
  CHECK_ADDR(&usr_pix->clipable.origin.x, &prv_pix->origin.x);
  CHECK_ADDR(&usr_pix->clipable.origin.y, &prv_pix->origin.y);
  CHECK_ADDR(&usr_pix->clipable.scale.x, &prv_pix->scale.x);
  CHECK_ADDR(&usr_pix->clipable.scale.y, &prv_pix->scale.y);
  CHECK_ADDR(&usr_pix->clipable.rotation, &prv_pix->rotation);
  CHECK_ADDR(&usr_pix->clipable.color_mask, &prv_pix->color_mask);
  CHECK_ADDR(&usr_pix->clipable.smooth, &prv_pix->smooth);
  CHECK_ADDR(&usr_pix->clipable.mosaic, &prv_pix->mosaic);
  CHECK_ADDR(&usr_pix->pixels, &prv_pix->rawpixels);
  CHECK_ADDR(&usr_pix->bits_per_pixels, &prv_pix->bits_per_pixels);
  CHECK_ADDR(&usr_pix->bitplane, &prv_pix->bitplane);
  CHECK_ADDR(&usr_pix->color_palette_size, &prv_pix->palette_size);
  CHECK_ADDR(&usr_pix->color_palette, &prv_pix->palette);
  CHECK_ADDR(&usr_pix->color_shifts[0], &prv_pix->color_shifts[0]);
  CHECK_ADDR(&usr_pix->color_shifts[1], &prv_pix->color_shifts[1]);
  CHECK_ADDR(&usr_pix->color_shifts[2], &prv_pix->color_shifts[2]);
  CHECK_ADDR(&usr_pix->color_shifts[3], &prv_pix->color_shifts[3]);

  t_bunny_font *usr_fnt = NULL;
  struct bunny_ttf_font *prv_ttf = NULL;
  struct bunny_gfx_font *prv_gfx = NULL;

  CHECK_ADDR(&usr_fnt->clipable.buffer._private[0], &prv_ttf->type);
  CHECK_ADDR(&usr_fnt->clipable.buffer._private[1], &prv_ttf->texture);
  CHECK_ADDR(&usr_fnt->clipable.buffer._private[2], &prv_ttf->ntexture);
  CHECK_ADDR(&usr_fnt->clipable.buffer._private[3], &prv_ttf->glactive);
  CHECK_ADDR(&usr_fnt->clipable.buffer._private[4], &prv_ttf->duplicate);
  CHECK_ADDR(&usr_fnt->clipable.buffer.width, &prv_ttf->width);
  CHECK_ADDR(&usr_fnt->clipable.buffer.height, &prv_ttf->height);
  CHECK_ADDR(&usr_fnt->clipable.buffer.data[0], &prv_ttf->data[0]);
  CHECK_ADDR(&usr_fnt->clipable.clip_x_position, &prv_ttf->rect.x);
  CHECK_ADDR(&usr_fnt->clipable.clip_y_position, &prv_ttf->rect.y);
  CHECK_ADDR(&usr_fnt->clipable.clip_width, &prv_ttf->rect.w);
  CHECK_ADDR(&usr_fnt->clipable.clip_height, &prv_ttf->rect.h);
  CHECK_ADDR(&usr_fnt->clipable.position.x, &prv_ttf->position.x);
  CHECK_ADDR(&usr_fnt->clipable.position.y, &prv_ttf->position.y);
  CHECK_ADDR(&usr_fnt->clipable.origin.x, &prv_ttf->origin.x);
  CHECK_ADDR(&usr_fnt->clipable.origin.y, &prv_ttf->origin.y);
  CHECK_ADDR(&usr_fnt->clipable.scale.x, &prv_ttf->scale.x);
  CHECK_ADDR(&usr_fnt->clipable.scale.y, &prv_ttf->scale.y);
  CHECK_ADDR(&usr_fnt->clipable.rotation, &prv_ttf->rotation);
  CHECK_ADDR(&usr_fnt->clipable.color_mask, &prv_ttf->color_mask);
  CHECK_ADDR(&usr_fnt->clipable.smooth, &prv_ttf->smooth);
  CHECK_ADDR(&usr_fnt->clipable.mosaic, &prv_ttf->mosaic);
  CHECK_ADDR(&usr_fnt->_private[0], &prv_ttf->res_id);
  CHECK_ADDR(&usr_fnt->_private[1], &prv_ttf->tex);
  CHECK_ADDR(&usr_fnt->_private[2], &prv_ttf->ntex);
  CHECK_ADDR(&usr_fnt->_private[3], &prv_ttf->sprite);
  CHECK_ADDR(&usr_fnt->string, &prv_ttf->string);
  CHECK_ADDR(&usr_fnt->string_offset, &prv_ttf->string_offset);
  CHECK_ADDR(&usr_fnt->string_len, &prv_ttf->string_len);
  CHECK_ADDR(&usr_fnt->halign, &prv_ttf->halign);
  CHECK_ADDR(&usr_fnt->valign, &prv_ttf->valign);
  CHECK_ADDR(&usr_fnt->color, &prv_ttf->color);
  CHECK_ADDR(&usr_fnt->outline, &prv_ttf->outline_color);
  CHECK_ADDR(&usr_fnt->outline_size, &prv_ttf->outline_size);
  CHECK_ADDR(&usr_fnt->offset, &prv_ttf->offset);
  CHECK_ADDR(&usr_fnt->glyph_size, &prv_ttf->glyph_size);
  CHECK_ADDR(&usr_fnt->interglyph_space, &prv_ttf->interglyph_space);

  CHECK_ADDR(&usr_fnt->clipable.buffer._private[0], &prv_gfx->type);
  CHECK_ADDR(&usr_fnt->clipable.buffer._private[1], &prv_gfx->texture);
  CHECK_ADDR(&usr_fnt->clipable.buffer._private[2], &prv_gfx->ntexture);
  CHECK_ADDR(&usr_fnt->clipable.buffer._private[3], &prv_gfx->glactive);
  CHECK_ADDR(&usr_fnt->clipable.buffer._private[4], &prv_gfx->duplicate);
  CHECK_ADDR(&usr_fnt->clipable.buffer.width, &prv_gfx->width);
  CHECK_ADDR(&usr_fnt->clipable.buffer.height, &prv_gfx->height);
  CHECK_ADDR(&usr_fnt->clipable.buffer.data[0], &prv_gfx->data[0]);
  CHECK_ADDR(&usr_fnt->clipable.clip_x_position, &prv_gfx->rect.x);
  CHECK_ADDR(&usr_fnt->clipable.clip_y_position, &prv_gfx->rect.y);
  CHECK_ADDR(&usr_fnt->clipable.clip_width, &prv_gfx->rect.w);
  CHECK_ADDR(&usr_fnt->clipable.clip_height, &prv_gfx->rect.h);
  CHECK_ADDR(&usr_fnt->clipable.position.x, &prv_gfx->position.x);
  CHECK_ADDR(&usr_fnt->clipable.position.y, &prv_gfx->position.y);
  CHECK_ADDR(&usr_fnt->clipable.origin.x, &prv_gfx->origin.x);
  CHECK_ADDR(&usr_fnt->clipable.origin.y, &prv_gfx->origin.y);
  CHECK_ADDR(&usr_fnt->clipable.scale.x, &prv_gfx->scale.x);
  CHECK_ADDR(&usr_fnt->clipable.scale.y, &prv_gfx->scale.y);
  CHECK_ADDR(&usr_fnt->clipable.rotation, &prv_gfx->rotation);
  CHECK_ADDR(&usr_fnt->clipable.color_mask, &prv_gfx->color_mask);
  CHECK_ADDR(&usr_fnt->clipable.smooth, &prv_gfx->smooth);
  CHECK_ADDR(&usr_fnt->clipable.mosaic, &prv_gfx->mosaic);
  CHECK_ADDR(&usr_fnt->_private[0], &prv_gfx->res_id);
  CHECK_ADDR(&usr_fnt->_private[1], &prv_gfx->tex);
  CHECK_ADDR(&usr_fnt->_private[2], &prv_gfx->ntex);
  CHECK_ADDR(&usr_fnt->_private[3], &prv_gfx->sprite);
  CHECK_ADDR(&usr_fnt->string, &prv_gfx->string);
  CHECK_ADDR(&usr_fnt->string_offset, &prv_gfx->string_offset);
  CHECK_ADDR(&usr_fnt->string_len, &prv_gfx->string_len);
  CHECK_ADDR(&usr_fnt->halign, &prv_gfx->halign);
  CHECK_ADDR(&usr_fnt->valign, &prv_gfx->valign);
  CHECK_ADDR(&usr_fnt->color, &prv_gfx->color);
  CHECK_ADDR(&usr_fnt->outline, &prv_gfx->outline_color);
  CHECK_ADDR(&usr_fnt->outline_size, &prv_gfx->outline_size);
  CHECK_ADDR(&usr_fnt->offset, &prv_gfx->offset);
  CHECK_ADDR(&usr_fnt->glyph_size, &prv_gfx->glyph_size);
  CHECK_ADDR(&usr_fnt->interglyph_space, &prv_gfx->interglyph_space);

  t_bunny_sprite *usr_sprite = NULL;
  struct bunny_sprite *prv_sprite = NULL;

  CHECK_ADDR(&usr_sprite->clipable.buffer._private[0], &prv_sprite->type);
  CHECK_ADDR(&usr_sprite->clipable.buffer._private[1], &prv_sprite->texture);
  CHECK_ADDR(&usr_sprite->clipable.buffer._private[2], &prv_sprite->ntexture);
  CHECK_ADDR(&usr_sprite->clipable.buffer._private[3], &prv_sprite->glactive);
  CHECK_ADDR(&usr_sprite->clipable.buffer._private[4], &prv_sprite->duplicate);
  CHECK_ADDR(&usr_sprite->clipable.buffer.width, &prv_sprite->width);
  CHECK_ADDR(&usr_sprite->clipable.buffer.height, &prv_sprite->height);
  CHECK_ADDR(&usr_sprite->clipable.buffer.data[0], &prv_sprite->data[0]);
  CHECK_ADDR(&usr_sprite->clipable.clip_x_position, &prv_sprite->rect.x);
  CHECK_ADDR(&usr_sprite->clipable.clip_y_position, &prv_sprite->rect.y);
  CHECK_ADDR(&usr_sprite->clipable.clip_width, &prv_sprite->rect.w);
  CHECK_ADDR(&usr_sprite->clipable.clip_height, &prv_sprite->rect.h);
  CHECK_ADDR(&usr_sprite->clipable.position.x, &prv_sprite->position.x);
  CHECK_ADDR(&usr_sprite->clipable.position.y, &prv_sprite->position.y);
  CHECK_ADDR(&usr_sprite->clipable.origin.x, &prv_sprite->origin.x);
  CHECK_ADDR(&usr_sprite->clipable.origin.y, &prv_sprite->origin.y);
  CHECK_ADDR(&usr_sprite->clipable.scale.x, &prv_sprite->scale.x);
  CHECK_ADDR(&usr_sprite->clipable.scale.y, &prv_sprite->scale.y);
  CHECK_ADDR(&usr_sprite->clipable.rotation, &prv_sprite->rotation);
  CHECK_ADDR(&usr_sprite->clipable.color_mask, &prv_sprite->color_mask);
  CHECK_ADDR(&usr_sprite->clipable.smooth, &prv_sprite->smooth);
  CHECK_ADDR(&usr_sprite->clipable.mosaic, &prv_sprite->mosaic);
  CHECK_ADDR(&usr_sprite->_private[0], &prv_sprite->res_id);
  CHECK_ADDR(&usr_sprite->_private[1], &prv_sprite->tex);
  CHECK_ADDR(&usr_sprite->_private[2], &prv_sprite->ntex);
  CHECK_ADDR(&usr_sprite->_private[3], &prv_sprite->sprite);
  CHECK_ADDR(&usr_sprite->animation, &prv_sprite->animation);
  CHECK_ADDR(&usr_sprite->nbr_animation, &prv_sprite->nbr_animation);
  CHECK_ADDR(&usr_sprite->hashname_id, &prv_sprite->hashname_id);
  CHECK_ADDR(&usr_sprite->collision_shapes, &prv_sprite->collision_shapes);
  CHECK_ADDR(&usr_sprite->nbr_collision, &prv_sprite->nbr_collision);
  CHECK_ADDR(&usr_sprite->current_animation_hash, &prv_sprite->current_animation_hash);
  CHECK_ADDR(&usr_sprite->current_animation, &prv_sprite->current_animation);
  CHECK_ADDR(&usr_sprite->current_frame_repeat, &prv_sprite->current_frame_repeat);
  CHECK_ADDR(&usr_sprite->current_repeat, &prv_sprite->current_repeat);
  CHECK_ADDR(&usr_sprite->current_frame, &prv_sprite->current_frame);
  CHECK_ADDR(&usr_sprite->current_time, &prv_sprite->current_time);
  CHECK_ADDR(&usr_sprite->stop_repeat, &prv_sprite->stop_repeat);
  CHECK_ADDR(&usr_sprite->draw_collision_shapes, &prv_sprite->draw_collision_shape);

  t_bunny_dressed_sprite *usr_dsp = NULL;
  struct bunny_dressed_sprite *prv_dsp = NULL;

  CHECK_ADDR(&usr_dsp->sprite.clipable.buffer._private[0], &prv_dsp->type);
  CHECK_ADDR(&usr_dsp->sprite.clipable.buffer._private[1], &prv_dsp->texture);
  CHECK_ADDR(&usr_dsp->sprite.clipable.buffer._private[2], &prv_dsp->ntexture);
  CHECK_ADDR(&usr_dsp->sprite.clipable.buffer._private[3], &prv_dsp->glactive);
  CHECK_ADDR(&usr_dsp->sprite.clipable.buffer._private[4], &prv_dsp->duplicate);
  CHECK_ADDR(&usr_dsp->sprite._private[0], &prv_dsp->res_id);
  CHECK_ADDR(&usr_dsp->sprite._private[1], &prv_dsp->tex);
  CHECK_ADDR(&usr_dsp->sprite._private[2], &prv_dsp->ntex);
  CHECK_ADDR(&usr_dsp->sprite._private[3], &prv_dsp->sprite);
  CHECK_ADDR(&usr_dsp->sprite.animation, &prv_dsp->animation);
  CHECK_ADDR(&usr_dsp->sprite.nbr_animation, &prv_dsp->nbr_animation);
  CHECK_ADDR(&usr_dsp->sprite.hashname_id, &prv_dsp->hashname_id);
  CHECK_ADDR(&usr_dsp->sprite.collision_shapes, &prv_dsp->collision_shapes);
  CHECK_ADDR(&usr_dsp->sprite.nbr_collision, &prv_dsp->nbr_collision);
  CHECK_ADDR(&usr_dsp->sprite.current_animation_hash, &prv_dsp->current_animation_hash);
  CHECK_ADDR(&usr_dsp->sprite.current_animation, &prv_dsp->current_animation);
  CHECK_ADDR(&usr_dsp->sprite.current_frame_repeat, &prv_dsp->current_frame_repeat);
  CHECK_ADDR(&usr_dsp->sprite.current_repeat, &prv_dsp->current_repeat);
  CHECK_ADDR(&usr_dsp->sprite.current_frame, &prv_dsp->current_frame);
  CHECK_ADDR(&usr_dsp->sprite.current_time, &prv_dsp->current_time);
  CHECK_ADDR(&usr_dsp->sprite.stop_repeat, &prv_dsp->stop_repeat);
  CHECK_ADDR(&usr_dsp->sprite.draw_collision_shapes, &prv_dsp->draw_collision_shape);
  CHECK_ADDR(&usr_dsp->closets, &prv_dsp->closets);
  CHECK_ADDR(&usr_dsp->clothes, &prv_dsp->clothes);

  t_bunny_tilemap *usr_tmap = NULL;
  struct bunny_tilemap *prv_tmap = NULL;

  CHECK_ADDR(&usr_tmap->clipable.buffer._private[0], &prv_tmap->type);
  CHECK_ADDR(&usr_tmap->clipable.buffer._private[1], &prv_tmap->texture);
  CHECK_ADDR(&usr_tmap->clipable.buffer._private[2], &prv_tmap->ntexture);
  CHECK_ADDR(&usr_tmap->clipable.buffer._private[3], &prv_tmap->glactive);
  CHECK_ADDR(&usr_tmap->clipable.buffer._private[4], &prv_tmap->duplicate);
  CHECK_ADDR(&usr_tmap->clipable.buffer.width, &prv_tmap->width);
  CHECK_ADDR(&usr_tmap->clipable.buffer.height, &prv_tmap->height);
  CHECK_ADDR(&usr_tmap->clipable.buffer.data[0], &prv_tmap->data[0]);
  CHECK_ADDR(&usr_tmap->clipable.clip_x_position, &prv_tmap->rect.x);
  CHECK_ADDR(&usr_tmap->clipable.clip_y_position, &prv_tmap->rect.y);
  CHECK_ADDR(&usr_tmap->clipable.clip_width, &prv_tmap->rect.w);
  CHECK_ADDR(&usr_tmap->clipable.clip_height, &prv_tmap->rect.h);
  CHECK_ADDR(&usr_tmap->clipable.position.x, &prv_tmap->position.x);
  CHECK_ADDR(&usr_tmap->clipable.position.y, &prv_tmap->position.y);
  CHECK_ADDR(&usr_tmap->clipable.origin.x, &prv_tmap->origin.x);
  CHECK_ADDR(&usr_tmap->clipable.origin.y, &prv_tmap->origin.y);
  CHECK_ADDR(&usr_tmap->clipable.scale.x, &prv_tmap->scale.x);
  CHECK_ADDR(&usr_tmap->clipable.scale.y, &prv_tmap->scale.y);
  CHECK_ADDR(&usr_tmap->clipable.rotation, &prv_tmap->rotation);
  CHECK_ADDR(&usr_tmap->clipable.color_mask, &prv_tmap->color_mask);
  CHECK_ADDR(&usr_tmap->clipable.smooth, &prv_tmap->smooth);
  CHECK_ADDR(&usr_tmap->clipable.mosaic, &prv_tmap->mosaic);
  CHECK_ADDR(&usr_tmap->_private[0], &prv_tmap->res_id);
  CHECK_ADDR(&usr_tmap->_private[1], &prv_tmap->tex);
  /* This one is especially important since normal-map migration changed the layout. */
  CHECK_ADDR(&usr_tmap->_private[2], &prv_tmap->ntex);
  CHECK_ADDR(&usr_tmap->_private[3], &prv_tmap->sprite);
  CHECK_ADDR(&usr_tmap->normal_map, &prv_tmap->normal_map);
  CHECK_ADDR(&usr_tmap->projection, &prv_tmap->projection);
  CHECK_ADDR(&usr_tmap->method, &prv_tmap->method);
  CHECK_ADDR(&usr_tmap->tile_size, &prv_tmap->tile_size);
  CHECK_ADDR(&usr_tmap->map_size, &prv_tmap->map_size);
  CHECK_ADDR(&usr_tmap->tilesets, &prv_tmap->tilesets);
  CHECK_ADDR(&usr_tmap->nbr_tilesets, &prv_tmap->nbr_tilesets);
  CHECK_ADDR(&usr_tmap->layers, &prv_tmap->layers);
  CHECK_ADDR(&usr_tmap->nbr_layers, &prv_tmap->nbr_layers);
  CHECK_ADDR(&usr_tmap->layer_clip[0], &prv_tmap->layer_clip[0]);
  CHECK_ADDR(&usr_tmap->camera, &prv_tmap->camera);
  CHECK_ADDR(&usr_tmap->zoom, &prv_tmap->zoom);
  CHECK_ADDR(&usr_tmap->rotation, &prv_tmap->tile_rotation);
  CHECK_ADDR(&usr_tmap->lock_borders, &prv_tmap->lock_borders);
  CHECK_ADDR(&usr_tmap->loop[0], &prv_tmap->loop[0]);
  CHECK_ADDR(&usr_tmap->properties, &prv_tmap->properties);

  t_bunny_parallax *usr_px = NULL;
  struct bunny_parallax *prv_px = NULL;

  CHECK_ADDR(&usr_px->clipable.buffer._private[0], &prv_px->type);
  CHECK_ADDR(&usr_px->clipable.buffer._private[1], &prv_px->texture);
  CHECK_ADDR(&usr_px->clipable.buffer._private[2], &prv_px->ntexture);
  CHECK_ADDR(&usr_px->clipable.buffer._private[3], &prv_px->glactive);
  CHECK_ADDR(&usr_px->clipable.buffer._private[4], &prv_px->duplicate);
  CHECK_ADDR(&usr_px->clipable.buffer.width, &prv_px->width);
  CHECK_ADDR(&usr_px->clipable.buffer.height, &prv_px->height);
  CHECK_ADDR(&usr_px->clipable.buffer.data[0], &prv_px->data[0]);
  CHECK_ADDR(&usr_px->clipable.clip_x_position, &prv_px->rect.x);
  CHECK_ADDR(&usr_px->clipable.clip_y_position, &prv_px->rect.y);
  CHECK_ADDR(&usr_px->clipable.clip_width, &prv_px->rect.w);
  CHECK_ADDR(&usr_px->clipable.clip_height, &prv_px->rect.h);
  CHECK_ADDR(&usr_px->clipable.position.x, &prv_px->position.x);
  CHECK_ADDR(&usr_px->clipable.position.y, &prv_px->position.y);
  CHECK_ADDR(&usr_px->clipable.origin.x, &prv_px->origin.x);
  CHECK_ADDR(&usr_px->clipable.origin.y, &prv_px->origin.y);
  CHECK_ADDR(&usr_px->clipable.scale.x, &prv_px->scale.x);
  CHECK_ADDR(&usr_px->clipable.scale.y, &prv_px->scale.y);
  CHECK_ADDR(&usr_px->clipable.rotation, &prv_px->rotation);
  CHECK_ADDR(&usr_px->clipable.color_mask, &prv_px->color_mask);
  CHECK_ADDR(&usr_px->clipable.smooth, &prv_px->smooth);
  CHECK_ADDR(&usr_px->clipable.mosaic, &prv_px->mosaic);
  CHECK_ADDR(&usr_px->_private[0], &prv_px->res_id);
  CHECK_ADDR(&usr_px->_private[1], &prv_px->tex);
  CHECK_ADDR(&usr_px->_private[2], &prv_px->ntex);
  CHECK_ADDR(&usr_px->_private[3], &prv_px->sprite);
  CHECK_ADDR(&usr_px->layers, &prv_px->layers);
  CHECK_ADDR(&usr_px->nbr_layers, &prv_px->nbr_layers);
  CHECK_ADDR(&usr_px->inside_size, &prv_px->inside_size);
  CHECK_ADDR(&usr_px->viewpoint, &prv_px->viewpoint);
  CHECK_ADDR(&usr_px->lock_viewpoint, &prv_px->lock_viewpoint);

  t_bunny_effect *usr_eff = NULL;
  struct bunny_effect *prv_eff = NULL;

  CHECK_ADDR(&usr_eff->sound._private[0], &prv_eff->type);
  CHECK_ADDR(&usr_eff->sound.file, &prv_eff->file);
  CHECK_ADDR(&usr_eff->sound.volume, &prv_eff->volume);
  CHECK_ADDR(&usr_eff->sound.pitch, &prv_eff->pitch);
  CHECK_ADDR(&usr_eff->sound.loop, &prv_eff->loop);
  CHECK_ADDR(&usr_eff->sound.position[0], &prv_eff->position[0]);
  CHECK_ADDR(&usr_eff->sound.attenuation, &prv_eff->attenuation);
  CHECK_ADDR(&usr_eff->sound.playing, &prv_eff->playing);
  CHECK_ADDR(&usr_eff->sound.pause, &prv_eff->pause);
  CHECK_ADDR(&usr_eff->sample_per_second, &prv_eff->sample_per_second);
  CHECK_ADDR(&usr_eff->duration, &prv_eff->duration);
  CHECK_ADDR(&usr_eff->sample, &prv_eff->sample);

  t_bunny_music *usr_mus = NULL;
  struct bunny_music *prv_mus = NULL;

  CHECK_ADDR(&usr_mus->sound._private[0], &prv_mus->type);
  CHECK_ADDR(&usr_mus->sound.file, &prv_mus->file);
  CHECK_ADDR(&usr_mus->sound.volume, &prv_mus->volume);
  CHECK_ADDR(&usr_mus->sound.pitch, &prv_mus->pitch);
  CHECK_ADDR(&usr_mus->sound.loop, &prv_mus->loop);
  CHECK_ADDR(&usr_mus->sound.position[0], &prv_mus->position[0]);
  CHECK_ADDR(&usr_mus->sound.attenuation, &prv_mus->attenuation);
  CHECK_ADDR(&usr_mus->sound.playing, &prv_mus->playing);
  CHECK_ADDR(&usr_mus->sound.pause, &prv_mus->pause);
  CHECK_ADDR(&usr_mus->duration, &prv_mus->duration);

  t_bunny_recorder *usr_rec = NULL;
  struct bunny_recorder *prv_rec = NULL;

  CHECK_ADDR(&usr_rec->effect.sound._private[0], &prv_rec->type);
  CHECK_ADDR(&usr_rec->effect.sound.file, &prv_rec->file);
  CHECK_ADDR(&usr_rec->effect.sound.volume, &prv_rec->volume);
  CHECK_ADDR(&usr_rec->effect.sound.pitch, &prv_rec->pitch);
  CHECK_ADDR(&usr_rec->effect.sound.loop, &prv_rec->loop);
  CHECK_ADDR(&usr_rec->effect.sound.position[0], &prv_rec->position[0]);
  CHECK_ADDR(&usr_rec->effect.sound.attenuation, &prv_rec->attenuation);
  CHECK_ADDR(&usr_rec->effect.sound.playing, &prv_rec->playing);
  CHECK_ADDR(&usr_rec->effect.sound.pause, &prv_rec->pause);
  CHECK_ADDR(&usr_rec->effect.sample_per_second, &prv_rec->sample_per_second);
  CHECK_ADDR(&usr_rec->effect.duration, &prv_rec->duration);
  CHECK_ADDR(&usr_rec->effect.sample, &prv_rec->sample);
  CHECK_ADDR(&usr_rec->_private[0], &prv_rec->res_id);
  CHECK_ADDR(&usr_rec->_private[1], &prv_rec->effect);
  CHECK_ADDR(&usr_rec->_private[2], &prv_rec->sound);
  CHECK_ADDR(&usr_rec->_private[3], &prv_rec->sound_manager);
  CHECK_ADDR(&usr_rec->device, &prv_rec->device);
  CHECK_ADDR(&usr_rec->recording, &prv_rec->recording);

  t_bunny_sound_sprite *usr_spr = NULL;
  struct bunny_music *prv_spr = NULL;

  CHECK_ADDR(&usr_spr->soundset.sound._private[0], &prv_spr->type);
  CHECK_ADDR(&usr_spr->soundset.sound.file, &prv_spr->file);
  CHECK_ADDR(&usr_spr->soundset.sound.volume, &prv_spr->volume);
  CHECK_ADDR(&usr_spr->soundset.sound.pitch, &prv_spr->pitch);
  CHECK_ADDR(&usr_spr->soundset.sound.loop, &prv_spr->loop);
  CHECK_ADDR(&usr_spr->soundset.sound.position[0], &prv_spr->position[0]);
  CHECK_ADDR(&usr_spr->soundset.sound.attenuation, &prv_spr->attenuation);
  CHECK_ADDR(&usr_spr->soundset.sound.playing, &prv_spr->playing);
  CHECK_ADDR(&usr_spr->soundset.sound.pause, &prv_spr->pause);
  CHECK_ADDR(&usr_spr->soundset.duration, &prv_spr->duration);
  CHECK_ADDR(&usr_spr->sound_areas, &prv_spr->sound_areas);
  CHECK_ADDR(&usr_spr->last_played_slice, &prv_spr->last_played_slice);
  CHECK_ADDR(&usr_spr->track, &prv_spr->track);

  t_bunny_cinematic *usr_cin = NULL;
  struct bunny_cinematic *prv_cin = NULL;

  CHECK_ADDR(&usr_cin->clipable.buffer._private[0], &prv_cin->type);
  CHECK_ADDR(&usr_cin->clipable.buffer._private[1], &prv_cin->texture);
  CHECK_ADDR(&usr_cin->clipable.buffer._private[2], &prv_cin->ntexture);
  CHECK_ADDR(&usr_cin->clipable.buffer._private[3], &prv_cin->glactive);
  CHECK_ADDR(&usr_cin->clipable.buffer._private[4], &prv_cin->duplicate);
  CHECK_ADDR(&usr_cin->clipable.buffer.width, &prv_cin->width);
  CHECK_ADDR(&usr_cin->clipable.buffer.height, &prv_cin->height);
  CHECK_ADDR(&usr_cin->clipable.buffer.data[0], &prv_cin->data[0]);
  CHECK_ADDR(&usr_cin->clipable.clip_x_position, &prv_cin->rect.x);
  CHECK_ADDR(&usr_cin->clipable.clip_y_position, &prv_cin->rect.y);
  CHECK_ADDR(&usr_cin->clipable.clip_width, &prv_cin->rect.w);
  CHECK_ADDR(&usr_cin->clipable.clip_height, &prv_cin->rect.h);
  CHECK_ADDR(&usr_cin->clipable.position.x, &prv_cin->position.x);
  CHECK_ADDR(&usr_cin->clipable.position.y, &prv_cin->position.y);
  CHECK_ADDR(&usr_cin->clipable.origin.x, &prv_cin->origin.x);
  CHECK_ADDR(&usr_cin->clipable.origin.y, &prv_cin->origin.y);
  CHECK_ADDR(&usr_cin->clipable.scale.x, &prv_cin->scale.x);
  CHECK_ADDR(&usr_cin->clipable.scale.y, &prv_cin->scale.y);
  CHECK_ADDR(&usr_cin->clipable.rotation, &prv_cin->rotation);
  CHECK_ADDR(&usr_cin->clipable.color_mask, &prv_cin->color_mask);
  CHECK_ADDR(&usr_cin->clipable.smooth, &prv_cin->smooth);
  CHECK_ADDR(&usr_cin->clipable.mosaic, &prv_cin->mosaic);
  CHECK_ADDR(&usr_cin->_private[0], &prv_cin->res_id);
  CHECK_ADDR(&usr_cin->_private[1], &prv_cin->tex);
  CHECK_ADDR(&usr_cin->_private[2], &prv_cin->ntex);
  CHECK_ADDR(&usr_cin->_private[3], &prv_cin->sprite);
  CHECK_ADDR(&usr_cin->_private[4], &prv_cin->configuration);
  CHECK_ADDR(&usr_cin->volumes.music, &prv_cin->volumes.music);
  CHECK_ADDR(&usr_cin->volumes.voice, &prv_cin->volumes.voice);
  CHECK_ADDR(&usr_cin->volumes.effect, &prv_cin->volumes.effect);
  CHECK_ADDR(&usr_cin->pictures, &prv_cin->pictures);
  CHECK_ADDR(&usr_cin->effects, &prv_cin->effects);
  CHECK_ADDR(&usr_cin->musics, &prv_cin->musics);
  CHECK_ADDR(&usr_cin->voices, &prv_cin->voices);
  CHECK_ADDR(&usr_cin->fonts, &prv_cin->fonts);
  CHECK_ADDR(&usr_cin->texts, &prv_cin->texts);
  CHECK_ADDR(&usr_cin->commands, &prv_cin->commands);
  CHECK_ADDR(&usr_cin->repeat, &prv_cin->repeat);
  CHECK_ADDR(&usr_cin->program, &prv_cin->program);
  CHECK_ADDR(&usr_cin->current_command, &prv_cin->current_command);
  CHECK_ADDR(&usr_cin->stack_frame, &prv_cin->stack_frame);
  CHECK_ADDR(&usr_cin->extended_data[0], &prv_cin->extended_data[0]);

  bunny_printl("If this text appears, it means that all consistency tests were successful.");
}
