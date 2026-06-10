// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2026
//
// Lapin library

#include		<algorithm>
#include		<cmath>
#include		"lapin_private.h"

static double		positive_mod(double				value,
				     double				period)
{
  if (period <= 0.0)
    return (0.0);
  value = fmod(value, period);
  if (value < 0.0)
    value += period;
  return (value);
}

static double		clamp_double(double				value,
				     double				low,
				     double				high)
{
  if (high < low)
    return ((low + high) / 2.0);
  return (std::min(std::max(value, low), high));
}

static void		lock_viewpoint(struct bunny_parallax		*px,
				       const t_bunny_size		&screen_size)
{
  if (px->lock_viewpoint == false)
    return ;
  if (px->inside_size.x <= screen_size.x)
    px->viewpoint.x = px->inside_size.x / 2.0;
  else
    px->viewpoint.x = clamp_double(px->viewpoint.x,
				   screen_size.x / 2.0,
				   px->inside_size.x - screen_size.x / 2.0);
  if (px->inside_size.y <= screen_size.y)
    px->viewpoint.y = px->inside_size.y / 2.0;
  else
    px->viewpoint.y = clamp_double(px->viewpoint.y,
				   screen_size.y / 2.0,
				   px->inside_size.y - screen_size.y / 2.0);
}

static void		compute_scale(const t_bunny_parallax_layer	&layer,
				      const t_bunny_size		&reference_space,
				      t_bunny_accurate_size		&scale)
{
  double		base_w = layer.picture->clip_width * layer.picture->scale.x;
  double		base_h = layer.picture->clip_height * layer.picture->scale.y;

  scale = layer.picture->scale;
  switch (layer.mode)
    {
    case BPM_FILL:
    case BPM_MAXIMIZED:
      {
	double		sx = base_w != 0.0 ? (double)reference_space.x / base_w : 1.0;
	double		sy = base_h != 0.0 ? (double)reference_space.y / base_h : 1.0;
	double		factor = layer.mode == BPM_FILL ? std::max(sx, sy) : std::min(sx, sy);

	scale.x *= factor;
	scale.y *= factor;
	break ;
      }
    case BPM_STRETCHED:
      scale.x *= layer.picture->clip_width != 0 ? (double)reference_space.x / layer.picture->clip_width : 1.0;
      scale.y *= layer.picture->clip_height != 0 ? (double)reference_space.y / layer.picture->clip_height : 1.0;
      break ;
    case BPM_CENTERED:
    default:
      break ;
    }
}

static void		compute_offsets(struct bunny_parallax		&px,
					const t_bunny_parallax_layer	&layer,
					const t_bunny_size		&screen_size,
					t_bunny_accurate_position	&offset)
{
  offset.x = 0.0;
  offset.y = 0.0;
  if (layer.local)
    return ;
  offset.x = layer.speed_ratio.x * (px.viewpoint.x - screen_size.x / 2.0);
  offset.y = layer.speed_ratio.y * (px.viewpoint.y - screen_size.y / 2.0);
}

static void		draw_layer(struct bunny_parallax		&px,
				   const t_bunny_parallax_layer	&layer,
				   const t_bunny_size		&screen_size)
{
  t_bunny_picture	&dst = *(t_bunny_picture*)&px;
  t_bunny_picture	*src = layer.picture;
  t_bunny_accurate_position saved_pos = src->position;
  t_bunny_accurate_position saved_origin = src->origin;
  t_bunny_accurate_size	saved_scale = src->scale;
  int32_t		saved_clip_x = src->clip_x_position;
  int32_t		saved_clip_y = src->clip_y_position;
  int32_t		saved_clip_w = src->clip_width;
  int32_t		saved_clip_h = src->clip_height;
  bool			saved_mosaic = src->mosaic;
  t_bunny_size		reference_space;
  t_bunny_accurate_size	render_scale;
  t_bunny_accurate_position offset;
  double		base_x;
  double		base_y;
  double		pos_x;
  double		pos_y;
  double		rendered_w;
  double		rendered_h;

  reference_space = layer.local ? screen_size : px.inside_size;
  compute_scale(layer, reference_space, render_scale);
  src->scale = render_scale;
  src->mosaic = false;
  src->clip_x_position = 0;
  src->clip_y_position = 0;
  src->clip_width = src->buffer.width;
  src->clip_height = src->buffer.height;
  src->origin.x = 0;
  src->origin.y = 0;

  rendered_w = src->clip_width * src->scale.x;
  rendered_h = src->clip_height * src->scale.y;

  compute_offsets(px, layer, screen_size, offset);

  base_x = layer.local ? (screen_size.x - rendered_w) / 2.0 : 0.0;
  base_y = layer.local ? (screen_size.y - rendered_h) / 2.0 : 0.0;

  pos_x = layer.local ? base_x : -offset.x;
  pos_y = layer.local ? base_y : -offset.y;

  if (layer.loop_x)
    {
      double	scaled_tile_w = src->buffer.width * std::abs(src->scale.x);
      double	shift = positive_mod(offset.x, scaled_tile_w);
      double	pixel_w = std::abs(src->scale.x);
      int	tex_shift = pixel_w > 0.0 ? (int)floor(shift / pixel_w) : 0;
      double	remainder = shift - tex_shift * pixel_w;

      src->mosaic = true;
      src->clip_x_position = tex_shift;

      pos_x = (layer.local ? base_x : 0.0) - remainder;

      if (scaled_tile_w > 0.0 && pos_x > 0.0)
	{
	  double tiles_before = ceil(pos_x / scaled_tile_w);
	  pos_x -= tiles_before * scaled_tile_w;
	}

      src->clip_width = pixel_w > 0.0
	? (int)ceil((screen_size.x - pos_x) / pixel_w)
	: src->buffer.width;

      if (src->clip_width < src->buffer.width)
	src->clip_width = src->buffer.width;
    }

  if (layer.loop_y)
    {
      double	scaled_tile_h = src->buffer.height * std::abs(src->scale.y);
      double	shift = positive_mod(offset.y, scaled_tile_h);
      double	pixel_h = std::abs(src->scale.y);
      int	tex_shift = pixel_h > 0.0 ? (int)floor(shift / pixel_h) : 0;
      double	remainder = shift - tex_shift * pixel_h;

      src->mosaic = true;
      src->clip_y_position = tex_shift;

      pos_y = (layer.local ? base_y : 0.0) - remainder;

      if (scaled_tile_h > 0.0 && pos_y > 0.0)
	{
	  double tiles_before = ceil(pos_y / scaled_tile_h);
	  pos_y -= tiles_before * scaled_tile_h;
	}

      src->clip_height = pixel_h > 0.0
	? (int)ceil((screen_size.y - pos_y) / pixel_h)
	: src->buffer.height;

      if (src->clip_height < src->buffer.height)
	src->clip_height = src->buffer.height;
    }

  t_bunny_position	final_pos = {
    (int)floor(pos_x),
    (int)floor(pos_y)
  };

  bunny_blit(&dst.buffer, src, &final_pos);

  src->position = saved_pos;
  src->origin = saved_origin;
  src->scale = saved_scale;
  src->clip_x_position = saved_clip_x;
  src->clip_y_position = saved_clip_y;
  src->clip_width = saved_clip_w;
  src->clip_height = saved_clip_h;
  src->mosaic = saved_mosaic;
}

void			__bunny_draw_parallax(struct bunny_parallax	*px)
{
  t_bunny_picture	*pic = (t_bunny_picture*)px;
  t_bunny_size		screen_size;

  screen_size.x = pic->clip_width;
  screen_size.y = pic->clip_height;
  lock_viewpoint(px, screen_size);

  px->type = GRAPHIC_RAM;
  for (size_t i = 0; i < px->nbr_layers; ++i)
    draw_layer(*px, px->layers[i], screen_size);
  px->type = PARALLAX;
}
