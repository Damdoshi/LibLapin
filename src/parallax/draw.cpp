// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<float.h>
#include		"lapin_private.h"

static void		draw_centered(struct bunny_parallax		&px,
				      const t_bunny_parallax_layer	&layer,
				      const t_bunny_position		&camera,
				      const t_bunny_accurate_position	&ratio,
				      const t_bunny_size		&virtual_space)
{
  t_bunny_picture	&pic = *(t_bunny_picture*)&px;
  t_bunny_picture	*src = layer.picture;

  (void)virtual_space;
  (void)px;
  (void)ratio;

  src->mosaic = false;
  src->clip_x_position = 0;
  src->clip_y_position = 0;
  src->clip_width = src->buffer.width;
  src->clip_height = src->buffer.height;
  if (layer.loop_x)
    {
      src->mosaic = true;
      src->clip_width = virtual_space.x;
    }
  if (layer.loop_y)
    {
      src->mosaic = true;
      src->clip_height = virtual_space.y;
    }
  src->origin.x = src->clip_width / 2;
  src->origin.y = src->clip_height / 2;

  t_bunny_position	final_pos = {
    -camera.x + virtual_space.x / 2,
    -camera.y + virtual_space.y / 2
  };

  bunny_blit(&pic.buffer, src, &final_pos);
}

static void		draw_filled(struct bunny_parallax		&px,
				    const t_bunny_parallax_layer	&layer,
				    const t_bunny_position		&camera,
				    const t_bunny_accurate_position	&ratio,
				    const t_bunny_size			&virtual_space)
{
  t_bunny_picture	*src = layer.picture;
  t_bunny_accurate_size	scale = src->scale;

  (void)ratio;

  // Test to fill with X
  src->scale.x = scale.x * ((double)virtual_space.x / src->clip_width);
  if (src->scale.x * src->clip_height * scale.y < virtual_space.y)
    {
      src->scale.y = scale.y * ((double)virtual_space.y / src->clip_height);
      src->scale.x = src->scale.y;
    }
  else
    src->scale.y = src->scale.x;

  draw_centered(px, layer, camera, ratio, virtual_space);

  src->scale = scale;
}

static void		draw_maximized(struct bunny_parallax		&px,
				       const t_bunny_parallax_layer	&layer,
				       const t_bunny_position		&camera,
				       const t_bunny_accurate_position	&ratio,
				       const t_bunny_size		&virtual_space)
{
  t_bunny_picture	*src = layer.picture;
  t_bunny_accurate_size	scale = src->scale;

  (void)ratio;

  // Test to fill with X
  src->scale.x = scale.x * ((double)virtual_space.x / src->clip_width);
  if (src->scale.x * src->clip_height * scale.y >= virtual_space.y)
    {
      src->scale.y = scale.y * ((double)virtual_space.y / src->clip_height);
      src->scale.x = src->scale.y;
    }
  else
    src->scale.y = src->scale.x;

  draw_centered(px, layer, camera, ratio, virtual_space);

  src->scale = scale;
}

static void		draw_stretched(struct bunny_parallax		&px,
				       const t_bunny_parallax_layer	&layer,
				       const t_bunny_position		&camera,
				       const t_bunny_accurate_position	&ratio,
				       const t_bunny_size		&virtual_space)
{
  t_bunny_picture	&pic = *(t_bunny_picture*)&px;
  t_bunny_picture	*src = layer.picture;
  t_bunny_accurate_size	scale = src->scale;

  (void)camera;

  src->scale.x = scale.x * ((double)virtual_space.x / src->clip_width);
  src->scale.y = scale.y * ((double)virtual_space.y / src->clip_height);
  src->origin.x = src->clip_width / 2;
  src->origin.y = src->clip_height / 2;

  t_bunny_accurate_position real_size = {
    .x = src->scale.x * src->clip_width,
    .y = src->scale.y * src->clip_height,
  };
  t_bunny_position	final_pos = {
    (virtual_space.x - ratio.x * real_size.x) / 2,
    (virtual_space.y - ratio.y * real_size.y) / 2
  };

  printf("%d - %d (%f x %f)\n", final_pos.x, final_pos.y, ratio.x, ratio.y);
  bunny_blit(&pic.buffer, src, &final_pos);
  src->scale = scale;
}

typedef void		(*__draw)(struct bunny_parallax			&px,
				  const t_bunny_parallax_layer		&layer,
				  const t_bunny_position		&camera,
				  const t_bunny_accurate_position	&ratio,
				  const t_bunny_size			&virtual_space);

  void			__bunny_draw_parallax(struct bunny_parallax	*px)
{
  t_bunny_picture	*pic = (t_bunny_picture*)px;
  __draw		func[4] = {
    draw_centered, draw_filled, draw_maximized, draw_stretched
  };

  // Keep the viewpoint inside the parallax
  if (px->lock_viewpoint && 0)
    {
      px->viewpoint.x = bunny_clamp
	(px->viewpoint.x,
	 pic->clip_width / 2,
	 px->inside_size.x - pic->clip_width / 2 - 1);
      px->viewpoint.y = bunny_clamp
	(px->viewpoint.y,
	 pic->clip_height / 2,
	 px->inside_size.y - pic->clip_height / 2 - 1);
    }
  t_bunny_position	screen_size = {
    pic->clip_width,
    pic->clip_height
  };

  // Loop on all layers, from first (bottom) to last (top)
  px->type = GRAPHIC_RAM;
  for (size_t i = 0; i < px->nbr_layers; ++i)
    {
      if (px->layers[i].local)
	func[px->layers[i].mode](*px, px->layers[i], {0.0, 0.0}, {0, 0}, screen_size);
      else
	{
	  t_bunny_accurate_position ratio = {
	    .x = (double)px->viewpoint.x / px->inside_size.x,
	    .y = (double)px->viewpoint.y / px->inside_size.y
	  };
	  t_bunny_position	camera = {
	    px->layers[i].speed_ratio.x * px->viewpoint.x - pic->clip_width / 2,
	    px->layers[i].speed_ratio.y * px->viewpoint.y - pic->clip_height / 2
	  };

	  func[px->layers[i].mode](*px, px->layers[i], camera, ratio, px->inside_size);
	}
    }
  px->type = PARALLAX;
}

