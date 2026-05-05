// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

/*
** BlendMode:
**  color source factor
**  color destination factor
**  color blend equation
**
**  alpha source factor
**  alpha destination factor
**  alpha blend equation
**
*/

#include			"lapin_private.h"

extern t_bunny_shader		*gl_normal_map_shader;
extern t_bunny_normal_map	*gl_normal_map_configuration;
extern bool			gl_display_normal_map;

static inline unsigned int	extract_bitplane(struct bunny_pixelarray		&pic,
						 uint8_t				*px,
						 int					x,
						 int					y)
{
  unsigned int			data = 0;
  int				plansize = pic.height * pic.width;

  // La taille d'un plan de bit.
  plansize += plansize % 8 ? (8 - plansize % 8) : 0;
  plansize *= pic.bits_per_pixels / 8.0;
  for (int i = 0; i < pic.bits_per_pixels; ++i)
    data = data | (bunny_bitfield_get(&px[i * plansize], x + y * pic.width) ? 1 << i : 0);
  if (pic.palette_size)
    return (pic.palette[data % pic.palette_size].full);
  switch ((int)pic.bits_per_pixels)
    {
    case 1:
      return (GRAY((data / 1.0) * 255));
    case 2:
      return (GRAY((data / 3.0) * 255));
    case 3:
      return (GRAY((data / 7.0) * 255));
    case 4:
      return (COLOR
	      (data & (1 << pic.color_shifts[ALPHA_CMP]) ? 255 : 0,
	       data & (1 << pic.color_shifts[RED_CMP]) ? 255 : 0,
	       data & (1 << pic.color_shifts[GREEN_CMP]) ? 255 : 0,
	       data & (1 << pic.color_shifts[BLUE_CMP]) ? 255 : 0
	       ));
    case 5:
      if (!(data & 0x10))
	return (COLOR
		(data & (1 << pic.color_shifts[ALPHA_CMP]) ? 255 : 0,
		 data & (1 << pic.color_shifts[RED_CMP]) ? 255 : 0,
		 data & (1 << pic.color_shifts[GREEN_CMP]) ? 255 : 0,
		 data & (1 << pic.color_shifts[BLUE_CMP]) ? 255 : 0
		 ));
      return (COLOR
	      (data & (1 << pic.color_shifts[ALPHA_CMP]) ? 128 : 0,
	       data & (1 << pic.color_shifts[RED_CMP]) ? 128 : 0,
	       data & (1 << pic.color_shifts[GREEN_CMP]) ? 128 : 0,
	       data & (1 << pic.color_shifts[BLUE_CMP]) ? 128 : 0
	       ));
    case 8:
      return (COLOR
	      (data >> (2 * pic.color_shifts[ALPHA_CMP]) & 3,
	       data >> (2 * pic.color_shifts[RED_CMP]) & 3,
	       data >> (2 * pic.color_shifts[GREEN_CMP]) & 3,
	       data >> (2 * pic.color_shifts[BLUE_CMP]) & 3
	       ));
    case 12:
      return (COLOR
	      (data >> (3 * pic.color_shifts[ALPHA_CMP]) & 7,
	       data >> (3 * pic.color_shifts[RED_CMP]) & 7,
	       data >> (3 * pic.color_shifts[GREEN_CMP]) & 7,
	       data >> (3 * pic.color_shifts[BLUE_CMP]) & 7
	       ));
    default:
      return (rand() | BLACK);
    }
  return (rand() | BLACK);
}

static inline unsigned int	extract_color(struct bunny_pixelarray			&pic,
					      void					*_px,
					      int					x,
					      int					y)
{
  if (pic.bitplane)
    return (extract_bitplane(pic, (uint8_t*)_px, x, y));
  unsigned int			data;
  uint8_t			*px = (uint8_t*)_px;
  uint16_t			*px16 = (uint16_t*)_px;
  float				*pxf = (float*)_px;

  switch (pic.bits_per_pixels)
    {
    case BBW_BLACK_AND_WHITE:
      data = (px[(x + y * pic.width) / 8] >> (1 * ((x + y * pic.width) % 8))) & 0b00000001;
      if (pic.palette_size)
	return (pic.palette[data % pic.palette_size].full);
      return (GRAY((data / 1.0) * 255));
    case BBW_4_COLORS:
      data = (px[(x + y * pic.width) / 4] >> (2 * ((x + y * pic.width) % 4))) & 0b00000011;
      if (pic.palette_size)
	return (pic.palette[data % pic.palette_size].full);
      return (GRAY((data / 3.0) * 255));
    case BBW_16_COLORS:
      data = (px[(x + y * pic.width) / 2] >> (4 * ((x + y * pic.width) % 2))) & 0b00001111;
      if (pic.palette_size)
	return (pic.palette[data % pic.palette_size].full);
      return (COLOR
	      (data & (1 << pic.color_shifts[ALPHA_CMP]) ? 255 : 0,
	       data & (1 << pic.color_shifts[RED_CMP]) ? 255 : 0,
	       data & (1 << pic.color_shifts[GREEN_CMP]) ? 255 : 0,
	       data & (1 << pic.color_shifts[BLUE_CMP]) ? 255 : 0
	       ));
    case BBW_256_COLORS:
      {
	data = px[x + y * pic.width];
	if (pic.palette_size)
	  return (pic.palette[data % pic.palette_size].full);
	return (COLOR
		(255 * (data >> (2 * pic.color_shifts[ALPHA_CMP]) & 3) / 7.0,
		 255 * (data >> (2 * pic.color_shifts[RED_CMP]) & 3) / 7.0,
		 255 * (data >> (2 * pic.color_shifts[GREEN_CMP]) & 3) / 7.0,
		 255 * (data >> (2 * pic.color_shifts[BLUE_CMP]) & 3) / 7.0
		 ));
      }
    case BBW_64K_COLORS:
      {
	data = px16[x + y * pic.width];
	return (COLOR
		(255 * (data >> (4 * pic.color_shifts[ALPHA_CMP]) & 0xF) / 15.0,
		 255 * (data >> (4 * pic.color_shifts[RED_CMP]) & 0xF) / 15.0,
		 255 * (data >> (4 * pic.color_shifts[GREEN_CMP]) & 0xF) / 15.0,
		 255 * (data >> (4 * pic.color_shifts[BLUE_CMP]) & 0xF) / 15.0
		 ));
      }
    case BBW_ARGB_COLORS:
      data = ((unsigned int*)_px)[x + y * pic.width];
      return (COLOR
	      (255 * (data >> (8 * pic.color_shifts[ALPHA_CMP]) & 0xFF) / 255.0,
	       255 * (data >> (8 * pic.color_shifts[RED_CMP]) & 0xFF) / 255.0,
	       255 * (data >> (8 * pic.color_shifts[GREEN_CMP]) & 0xFF) / 255.0,
	       255 * (data >> (8 * pic.color_shifts[BLUE_CMP]) & 0xFF) / 255.0
	       ));
    default:
      float	f[4] =
	{
	 bunny_clamp(pxf[(x + y * pic.width) * 4 + pic.color_shifts[ALPHA_CMP]], 0, 1) * 255,
	 bunny_clamp(pxf[(x + y * pic.width) * 4 + pic.color_shifts[RED_CMP]], 0, 1) * 255,
	 bunny_clamp(pxf[(x + y * pic.width) * 4 + pic.color_shifts[GREEN_CMP]], 0, 1) * 255,
	 bunny_clamp(pxf[(x + y * pic.width) * 4 + pic.color_shifts[BLUE_CMP]], 0, 1) * 255
	};
      return (COLOR(f[0], f[1], f[2], f[3]));
    }
  return (BLACK);
}

static sf::Sprite		*blit_pixelarray(struct bunny_pixelarray		&pic,
						 const t_bunny_position			&pos)
{
  sf::IntRect			rect;
  int				i;
  int				j;

  rect.position.x = pic.rect.x;
  rect.position.y = pic.rect.y;
  rect.size.x = pic.rect.w;
  rect.size.y = pic.rect.h;
  for (j = pic.rect.y; j < pic.rect.y + pic.rect.h; ++j)
    for (i = pic.rect.x; i < pic.rect.x + pic.rect.w; ++i)
      if (i >= 0 && j >= 0 && i < pic.width && j < pic.height)
	{
	  t_bunny_color c;

	  if (pic.bits_per_pixels == BBW_ARGB_COLORS &&
	      pic.color_shifts[ALPHA_CMP] == ALPHA_CMP &&
	      pic.color_shifts[RED_CMP] == RED_CMP &&
	      pic.color_shifts[GREEN_CMP] == GREEN_CMP &&
	      pic.color_shifts[BLUE_CMP] == BLUE_CMP)
	    c.full = ((unsigned int*)pic.rawpixels)[i + j * pic.width];
	  else
	    c.full = extract_color(pic, pic.rawpixels, i, j);
	  pic.image->setPixel
	    ({i, j},
	     sf::Color
	     (c.argb[RED_CMP],
	      c.argb[GREEN_CMP],
	      c.argb[BLUE_CMP],
	      c.argb[ALPHA_CMP]
	      )
	     );
	}
  pic.tex->loadFromImage(*pic.image, false, rect);
  if (pic.sprite == NULL)
    {
      if ((pic.sprite = new (std::nothrow) sf::Sprite(*pic.tex)) == NULL)
	return (NULL);
    }
  else
    pic.sprite->setTexture(*pic.tex, true); // Safe
  pic.sprite->setPosition({pos.x, pos.y});
  if (gl_full_blit)
    {
      pic.sprite->setOrigin({pic.origin.x, pic.origin.y});
      pic.sprite->setScale({pic.scale.x, pic.scale.y});
      pic.sprite->setRotation(sf::degrees(pic.rotation));
      pic.sprite->setColor
	(sf::Color(pic.color_mask.argb[RED_CMP],
		   pic.color_mask.argb[GREEN_CMP],
		   pic.color_mask.argb[BLUE_CMP],
		   pic.color_mask.argb[ALPHA_CMP]
		   ));
      pic.tex->setSmooth(pic.smooth);
      pic.tex->setRepeated(pic.mosaic);
    }
  return (pic.sprite);
}

static void			draw_rendertexture_sprite(sf::RenderTexture		*target,
							  sf::Sprite			&sprite,
							  sf::Shader			*shader,
							  bool				allow_special_blend)
{
  if (target == NULL)
    return ;
  if (shader)
    {
      if (allow_special_blend)
	{
	  if (gl_set_alpha_blit)
	    {
	      sf::RenderStates stt = sf::BlendMultiply;

	      stt.shader = shader;
	      target->draw(sprite, stt);
	    }
	  if (gl_set_additional_blit)
	    {
	      sf::RenderStates stt = sf::BlendAdd;

	      stt.shader = shader;
	      target->draw(sprite, stt);
	    }
	  else if (gl_full_blit == false)
	    {
	      sf::RenderStates stt = sf::BlendNone;

	      stt.shader = shader;
	      target->draw(sprite, stt);
	    }
	  else
	    target->draw(sprite, shader);
	}
      else if (gl_full_blit == false)
	{
	  sf::RenderStates stt = sf::BlendNone;

	  stt.shader = shader;
	  target->draw(sprite, stt);
	}
      else
	target->draw(sprite, shader);
      return ;
    }
  if (allow_special_blend)
    {
      if (gl_set_alpha_blit)
	{
	  sf::RenderStates stt = sf::BlendAlpha;

	  stt.blendMode = sf::BlendMode
	    (sf::BlendMode::Factor::Zero,
	     sf::BlendMode::Factor::One,
	     sf::BlendMode::Equation::Add,
	     sf::BlendMode::Factor::One,
	     sf::BlendMode::Factor::One,
	     sf::BlendMode::Equation::ReverseSubtract
	     );
	  target->draw(sprite, stt);
	}
      else if (gl_set_additional_blit)
	{
	  sf::RenderStates stt = sf::BlendAdd;

	  target->draw(sprite, stt);
	}
      else if (gl_set_multiply_blit)
	{
	  sf::RenderStates stt = sf::BlendMultiply;

	  target->draw(sprite, stt);
	}
      else
	target->draw(sprite);
    }
  else if (gl_full_blit == false)
    target->draw(sprite, sf::RenderStates(sf::BlendNone));
  else
    target->draw(sprite);
}

void				merge_clothe(t_bunny_map		*nod,
					     void			*pnw);

#define				PATTERN				\
  "%p target, %p source, %p position (%d, %d), %p shader"

/**
 * @doc-symbol bunny_blit
 * @doc-module graphics
 * @doc-kind function
 * @doc-order 180
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Draws a clipable source on a target buffer.
 * @description The target can be a window, a picture or, when the proper user callback is installed, a pixelarray. If position is NULL, the source position field is used.
 * @description When the source is a pixelarray, full transformations and alpha require bunny_enable_full_blit.
 * @param buf The target buffer.
 * @param clp The source clipable.
 * @param pos The destination position, or NULL to use clp->position.
 * @error EINVAL The target or source kind is not supported.
 * @log Logs are written with the "graphics" label.
 * @see bunny_blit_shader, bunny_enable_full_blit, t_bunny_my_blit, gl_bunny_my_blit
 *
 * @doc-lang fr
 * @brief Dessine une source clipable sur un buffer cible.
 * @description La cible peut être une fenêtre, une picture ou, lorsque le callback utilisateur approprié est installé, un pixelarray. Si position vaut NULL, le champ position de la source est utilisé.
 * @description Lorsque la source est un pixelarray, les transformations complètes et l’alpha nécessitent bunny_enable_full_blit.
 * @param buf Le buffer cible.
 * @param clp Le clipable source.
 * @param pos La position de destination, ou NULL pour utiliser clp->position.
 * @error EINVAL Le type de cible ou de source n’est pas pris en charge.
 * @log Les logs sont écrits avec le label "graphics".
 * @see bunny_blit_shader, bunny_enable_full_blit, t_bunny_my_blit, gl_bunny_my_blit
 */
void				bunny_blit(t_bunny_buffer		*output,
					   const t_bunny_clipable	*picture,
					   const t_bunny_position	*pos)
{
  bunny_blit_shader(output, picture, pos, NULL);
}

void				bunny_blit_shader(t_bunny_buffer	*output,
						  const t_bunny_picture	*picture,
						  const t_bunny_position *pos,
						  const t_bunny_shader	*_shader)
{
  t_bunny_position		defaul = {0, 0};

  if (pos == NULL)
    {
      defaul.x = picture->position.x;
      defaul.y = picture->position.y;
      pos = &defaul;
    }

  size_t			*type = (size_t*)output;
  size_t			*input_type = (size_t*)picture;
  sf::Shader			*shader = (sf::Shader*)_shader;
  sf::Sprite			*spr;
  bool				has_normal_sprite = false;

  switch (*input_type)
    {
    case GRAPHIC_TEXT:
    case TTF_TEXT:
      {
	size_t			typ = *input_type;

	*input_type = GRAPHIC_RAM;
	bunny_blit_shader(output, picture, pos, _shader);
	*input_type = typ;
	scream_log_if
	  (PATTERN, "graphics", output, picture, pos, pos->x, pos->y, _shader);
	return ;
      }
    case DRESSED_SPRITE:
      {
	struct bunny_dressed_sprite *spr = (struct bunny_dressed_sprite*)picture;
	std::map<int, std::list<t_bunny_clipable*> > clo;
	t_bunny_map **node;

	spr->type = (size_t)SPRITE;
	bunny_blit_shader(output, picture, pos, _shader);
	spr->type = (size_t)DRESSED_SPRITE;
	for (bunny_map_all(spr->clothes, node))
	  {
	    t_bunny_map *nod = *node;
	    size_t key = (size_t)nod->key;
	    t_bunny_clothe *clothe = (t_bunny_clothe*)nod->data;
	    t_bunny_closet *closet = bunny_map_get_data(spr->closets, key, t_bunny_closet*);

	    clo[closet->depth].push_back(&clothe->sprite->clipable);
	  }
	for (auto it = clo.begin(); it != clo.end(); ++it)
	  for (auto jt = it->second.begin(); jt != it->second.end(); ++jt)
	    bunny_blit_shader(output, *jt, pos, _shader);
	return ;
      }
    case TILEMAP:
      {
	struct bunny_tilemap	*tmap = (struct bunny_tilemap*)picture;

	tmap->working->rotation = tmap->tile_rotation;
	tmap->type = GRAPHIC_RAM;
	((struct bunny_picture*)tmap->working)->texture->display();
	if (((struct bunny_picture*)tmap->working)->ntexture)
	  ((struct bunny_picture*)tmap->working)->ntexture->display();
        bunny_blit((t_bunny_buffer*)tmap, tmap->working, NULL);
	tmap->texture->display();
	if (tmap->ntexture)
	  tmap->ntexture->display();
	tmap->type = TILEMAP;
	// NO BREAK -> Graphic ram scope is needed too.
	[[fallthrough]];
      }
    case PARALLAX:
    case SPRITE:
    case CINEMATIC:
    case GRAPHIC_RAM:
      {
	struct bunny_picture	*pic = (struct bunny_picture*)picture;
	sf::IntRect		rect;

	rect.position.x = pic->rect.x;
	rect.position.y = pic->rect.y;
	rect.size.x = pic->rect.w;
	rect.size.y = pic->rect.h;
	pic->texture->setSmooth(pic->smooth);
	pic->texture->setRepeated(pic->mosaic);
	pic->tex = &pic->texture->getTexture();
	pic->ntex = pic->ntexture ? &pic->ntexture->getTexture() : pic->ntex;
	if (pic->sprite == NULL)
	  {
	    if ((pic->sprite = new (std::nothrow) sf::Sprite(*(pic->tex))) == NULL)
	      return;
	  }
	else
	  pic->sprite->setTexture(*(pic->tex)); // Safe
	if (gl_display_normal_map && pic->ntex)
	  pic->sprite->setTexture(*(pic->ntex));
	pic->sprite->setTextureRect(rect);
	pic->sprite->setPosition({pos->x, pos->y});
	pic->sprite->setOrigin({pic->origin.x, pic->origin.y});
	pic->sprite->setScale({pic->scale.x, pic->scale.y});
	pic->sprite->setRotation(sf::degrees(pic->rotation));
	pic->sprite->setColor
	  (sf::Color(pic->color_mask.argb[RED_CMP],
		     pic->color_mask.argb[GREEN_CMP],
		     pic->color_mask.argb[BLUE_CMP],
		     pic->color_mask.argb[ALPHA_CMP]
		     ));
	spr = pic->sprite;
	if (pic->ntex)
	  has_normal_sprite = true;
	break ;
      }
    case SYSTEM_RAM:
      {
	spr = blit_pixelarray(*(struct bunny_pixelarray*)picture, *pos);
	break ;
      }
    default:
      scream_error_if
	(return, EINVAL, PATTERN, "graphics", output, picture, pos, pos->x, pos->y, _shader);
    }

  switch (*type)
    {
    case WINDOW:
      {
	struct bunny_window	*out = (struct bunny_window*)output;

	if (*input_type == GRAPHIC_RAM
	    || *input_type == SPRITE
	    || *input_type == TTF_TEXT
	    || *input_type == TILEMAP
	    || *input_type == DRESSED_SPRITE)
	  {
	    if (!shader)
	      out->window->draw(*spr);
	    else if (gl_normal_map_shader == shader)
	      {
		gl_normal_map_configuration->normal_map = (t_bunny_picture*)picture;
		out->window->draw(*spr, (sf::Shader*)bunny_normal_map_shader(gl_normal_map_configuration));
	      }
	    else
	      out->window->draw(*spr, shader);
	  }
	else if (gl_full_blit == false)
	  out->window->draw(*spr, sf::RenderStates(sf::BlendNone));
	else
	  out->window->draw(*spr);
	scream_log_if
	  (PATTERN, "graphics", output, picture, pos, pos->x, pos->y, _shader);
	return ;
      }
    case TILEMAP:
      {
	struct bunny_tilemap	*out = (struct bunny_tilemap*)output;

	__bunny_blit_tilemap(out, picture, pos, _shader);
	return ;
      }
    case TTF_TEXT:
    case DRESSED_SPRITE:
    case SPRITE:
    case GRAPHIC_TEXT:
    case GRAPHIC_RAM:
    case CINEMATIC:
      {
	struct bunny_picture	*out = (struct bunny_picture*)output;

	if (out->res_id != 0)
	  bunny_make_clipable_unique((t_bunny_clipable*)out);
	if (*input_type == GRAPHIC_RAM
	    || *input_type == SPRITE
	    || *input_type == TTF_TEXT
	    || *input_type == TILEMAP
	    || *input_type == DRESSED_SPRITE
	    || *input_type == CINEMATIC)
	  {
	    const bunny_picture *in = (const bunny_picture*)picture;

	    if (out->ntexture && has_normal_sprite)
	      {
		// blit de la normal map source vers la target normal
		spr->setTexture(*in->ntex);
		draw_rendertexture_sprite(out->ntexture, *spr, NULL, true);

		// blit de la color map source vers la target color
		spr->setTexture(*in->tex);
		draw_rendertexture_sprite(out->texture, *spr, shader, true);
	      }
	    else
	      {
		spr->setTexture(*in->tex);
		draw_rendertexture_sprite(out->texture, *spr, shader, true);
	      }
	  }
	else
	  {
	    if (gl_full_blit == false)
	      out->texture->draw(*spr, sf::RenderStates(sf::BlendNone));
	    else
	      out->texture->draw(*spr);
	    if (out->ntexture && has_normal_sprite)
	      {
		spr->setTexture(*out->ntex);
		if (gl_full_blit == false)
		  out->ntexture->draw(*spr, sf::RenderStates(sf::BlendNone));
		else
		  out->ntexture->draw(*spr);
	      }
	  }

	if (*type == SPRITE)
	  {
	    t_bunny_sprite *spr = (t_bunny_sprite*)picture;
	    const t_bunny_collision_shapes *col = bunny_sprite_get_collision(spr);

	    if (col)
	      for (unsigned int x = 0; x < col->nbr_collision; ++x)
		bunny_draw_collision_shape(output, &col->collisions[x], RED);
	  }

	scream_log_if
	  (PATTERN, "graphics", output, picture, pos, pos->x, pos->y, _shader);
	return ;
      }
    case SYSTEM_RAM:
      {
	struct bunny_pixelarray	*out = (struct bunny_pixelarray*)output;

	if (*input_type == SYSTEM_RAM)
	  {
	    const t_bunny_pixelarray	*pic = (const t_bunny_pixelarray*)picture;

	    if (gl_bunny_my_blit == NULL)
	      fprintf(stderr, "gl_bunny_my_blit is not set.");
	    else
	      {
		if (out->res_id != 0)
		  bunny_make_clipable_unique((t_bunny_clipable*)out);
		gl_bunny_my_blit((t_bunny_pixelarray*)out, pic, pos);
	      }
	  }
	else
	  {
	    // This function is an horrible mess
	    const bunny_pixelarray	*pic = (const bunny_pixelarray*)output;
	    sf::Image			img = spr->getTexture().copyToImage();
	    int				i;
	    int				j;

	    if (pic->res_id != 0)
	      bunny_make_clipable_unique((t_bunny_clipable*)pic);
	    for (j = picture->clip_y_position;
		 j < picture->clip_y_position + picture->clip_height;
		 ++j)
	      for (i = picture->clip_x_position;
		   i < picture->clip_x_position + picture->clip_width;
		   ++i)
		{
		  t_bunny_position	posx;

		  posx.x = pos->x + i;
		  posx.y = pos->y + j;
		  if (posx.x >= 0 && posx.x < output->width &&
		      posx.y >= 0 && posx.y < output->height)
		    {
		      sf::Color		c = img.getPixel({i, j});
		      int		d = posx.x + posx.y * pic->width;

		      ((t_color*)pic->rawpixels)[d].argb[ALPHA_CMP] = c.a;
		      ((t_color*)pic->rawpixels)[d].argb[RED_CMP] = c.r;
		      ((t_color*)pic->rawpixels)[d].argb[GREEN_CMP] = c.g;
		      ((t_color*)pic->rawpixels)[d].argb[BLUE_CMP] = c.b;
		    }
		}
	  }
	scream_log_if
	  (PATTERN, "graphics", output, picture, pos, pos->x, pos->y, _shader);
	return ;
      }
    default:
      scream_error_if
	(return, EINVAL, PATTERN, "graphics", output, picture, pos, pos->x, pos->y, _shader);
    }
}
