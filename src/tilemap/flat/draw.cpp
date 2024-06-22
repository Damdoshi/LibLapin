// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

static void		set_color(sf::Color			&c,
				  t_bunny_color			&bc)
{
  c.r = bc.argb[RED_CMP];
  c.g = bc.argb[GREEN_CMP];
  c.b = bc.argb[BLUE_CMP];
  c.a = bc.argb[ALPHA_CMP];
}

static void		loop_borders(bool				loop,
				     double				&min,
				     double				&max,
				     double				limit)
{
  if (loop)
    {
      min -= 1;
      max += 1;
      return ;
    }
  min = bunny_clamp(min - 1, 0, limit);
  max = bunny_clamp(max + 1, 0, limit);
}

static void		draw_layer(struct bunny_tilemap			*tmap,
				   int					layer,
				   int					left,
				   int					right,
				   int					top,
				   int					bot,
				   t_bunny_tileset			&ts,
				   const t_bunny_accurate_position	&tilsiz,
				   const t_bunny_accurate_position	&tlcam)
{
  // Vertex array that will contain everything drawn and its size counter
  int			last_vx = 0;
  sf::VertexArray	vertex = sf::VertexArray
    {
     sf::Triangles, (size_t)((right - left + 1) * (bot - top + 1) * 6)
    };

  for (int v = top; v <= bot; ++v)
    for (int h = left; h <= right; ++h)
      {
	int		oh = tmap->map_size.x * (h < 0) + h % tmap->map_size.x;
	int		ov = tmap->map_size.y * (v < 0) + v % tmap->map_size.y;
	int		index = oh + ov * tmap->map_size.x;
	int		tile;

	if ((tile = tmap->layers[layer].tiles[index]) == 0)
	  continue ;
	if (tile < ts.first_tile || tile >= ts.last_tile)
	  continue ;
	tile -= ts.first_tile;
	t_bunny_picture	*clip;
	double		rleft;
	double		rtop;
	double		tleft;
	double		ttop;

	rleft = h * tilsiz.x - tlcam.x + tmap->width / 2 + tmap->working_target_diff.x;
	rtop = v * tilsiz.y - tlcam.y + tmap->height / 2 + tmap->working_target_diff.y;

	// If the tile is not directly inside the tileset, it must be an animated tile
	if (ts.animated_tiles_id == NULL || ts.animated_tiles_id[tile] == NULL)
	  {
	    // Simple tile - clip its graphics
	    clip = ts.tileset;
	    tleft =
	      (tile % ts.tileset_size.x) * (ts.tile_size.x + ts.intertile.x) + ts.margin.x;
	    ttop =
	      (tile / ts.tileset_size.x) * (ts.tile_size.y + ts.intertile.y) + ts.margin.y;
	  }
	else
	  {
	    clip = &ts.animated_tiles_id[tile]->clipable;
	    tleft = clip->clip_x_position;
	    ttop = clip->clip_y_position;
	  }

	////////////////////
	// FIRST TRIANGLE //
	////////////////////

	// Top left corner
	{
	  sf::Vertex	&vx = vertex[last_vx++];

	  vx.position.x = rleft;
	  vx.position.y = rtop;
	  set_color(vx.color, clip->color_mask);
	  vx.texCoords.x = tleft;
	  vx.texCoords.y = ttop;
	}

	// Top right corner
	{
	  sf::Vertex	&vx = vertex[last_vx++];

	  vx.position.x = rleft + tilsiz.x;
	  vx.position.y = rtop;
	  set_color(vx.color, clip->color_mask);
	  vx.texCoords.x = tleft + ts.tile_size.x;
	  vx.texCoords.y = ttop;
	}

	// Bottom left corner
	{
	  sf::Vertex	&vx = vertex[last_vx++];

	  vx.position.x = rleft;
	  vx.position.y = rtop + tilsiz.y;
	  set_color(vx.color, clip->color_mask);
	  vx.texCoords.x = tleft;
	  vx.texCoords.y = ttop + ts.tile_size.y;
	}

	/////////////////////
	// SECOND TRIANGLE //
	/////////////////////

	// Top right corner
	{
	  sf::Vertex	&vx = vertex[last_vx++];

	  vx.position.x = rleft + tilsiz.x;
	  vx.position.y = rtop;
	  set_color(vx.color, clip->color_mask);
	  vx.texCoords.x = tleft + ts.tile_size.x;
	  vx.texCoords.y = ttop;
	}

	// Bottom right corner
	{
	  sf::Vertex	&vx = vertex[last_vx++];

	  vx.position.x = rleft + tilsiz.x;
	  vx.position.y = rtop + tilsiz.y;
	  set_color(vx.color, clip->color_mask);
	  vx.texCoords.x = tleft + ts.tile_size.x;
	  vx.texCoords.y = ttop + ts.tile_size.y;
	}

	// Bottom left corner
	{
	  sf::Vertex	&vx = vertex[last_vx++];

	  vx.position.x = rleft;
	  vx.position.y = rtop + tilsiz.y;
	  set_color(vx.color, clip->color_mask);
	  vx.texCoords.x = tleft;
	  vx.texCoords.y = ttop + ts.tile_size.y;
	}
      }

  // Render inside the working buffer
  sf::RenderStates state = sf::RenderStates::Default;
  struct bunny_picture *wrk = (struct bunny_picture*)tmap->working;

  vertex.resize(last_vx);
  state.texture = ((struct bunny_picture*)ts.tileset)->tex;
  wrk->texture->draw(vertex, state);
}

bool				__bunny_draw_flat_tilemap(struct bunny_tilemap	*tmap)
{
  // Final target size
  t_bunny_buffer		*buffer = (t_bunny_buffer*)tmap;
  // On screen tile size
  t_bunny_accurate_position	tilsiz = {
    .x = tmap->tile_size.x * tmap->zoom.x,
    .y = tmap->tile_size.y * tmap->zoom.y
  };
  // On screen camera position
  t_bunny_accurate_position	tlcam = {
    .x = tmap->camera.x * tmap->zoom.x,
    .y = tmap->camera.y * tmap->zoom.y
  };
  // Subpart that will be displayed
  double			left =
    (tlcam.x - buffer->width / 1.5) / tilsiz.x;
  double			right =
    (tlcam.x + buffer->width / 1.5) / tilsiz.x;
  double			top =
    (tlcam.y - buffer->height / 1.5) / tilsiz.y;
  double			bot =
    (tlcam.y + buffer->height / 1.5) / tilsiz.y;
  // Layer clipping
  int				depth =
    bunny_clamp(tmap->layer_clip[0], 0, tmap->nbr_layers - 1);
  int				surface =
    bunny_clamp(tmap->layer_clip[1], 0, tmap->nbr_layers - 1);
  // To avoid showing the outside of the map
  if (tmap->lock_borders)
    __bunny_tilemap_lock_borders(tilsiz, tlcam, tmap, left, right, top, bot);
  // Loop borders
  loop_borders(tmap->loop[0], left, right, tmap->map_size.x - 1);
  loop_borders(tmap->loop[1], top, bot, tmap->map_size.y - 1);
  // Compute the animation step to do
  double			now = bunny_get_current_time();
  double			elapsed = now - tmap->last_step;

  for (int ts = 0; ts < (int)tmap->nbr_tilesets; ++ts)
    for (int an = 0; an < (int)tmap->tilesets[ts].nbr_animated_tiles; ++an)
      bunny_sprite_animate(tmap->tilesets[ts].animated_tiles[an], elapsed);
  tmap->last_step = now;

  // Loop from deeper clipped layer from surface clipped layer
  // Jump from tileset to tileset because sf::VertexArray can only clip a single
  // picture at once.
  try
    {
      for (int layer = depth; layer <= surface; ++layer)
	for (int ts = 0; ts < tmap->nbr_tilesets; ++ts)
	  draw_layer(tmap, layer, left, right, top, bot, tmap->tilesets[ts], tilsiz, tlcam);
    }
  catch (const std::bad_alloc &e)
    {
      return (false);
    }

  ((bunny_picture*)tmap->working)->texture->display();
  return (true);
}

