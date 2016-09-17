// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include			"lapin_private.h"

void				bunny_blit(t_bunny_buffer		*output,
					   const t_bunny_clipable	*picture,
					   const t_bunny_position	*pos)
{
  bunny_blit_shader(output, picture, pos, NULL);
}

void				bunny_blit_shader(t_bunny_buffer		*output,
						  const t_bunny_picture		*picture,
						  const t_bunny_position	*pos,
						  const t_bunny_shader		*_shader)
{
  static t_bunny_position	defaul = {0, 0};

  if (pos == NULL)
    pos = &defaul;

  size_t			*type = (size_t*)output;
  size_t			*input_type = (size_t*)picture;
  sf::Shader			*shader = (sf::Shader*)_shader;
  sf::Sprite			*spr;
  sf::Texture			_txt;
  sf::Sprite			_spr;

  if (*input_type == GRAPHIC_RAM)
    {
      struct bunny_picture *pic = (struct bunny_picture*)picture;

      pic->tex = &pic->texture->getTexture();
      pic->sprite.setTexture(*pic->tex);
      pic->sprite.setTextureRect(pic->rect);
      pic->sprite.setPosition(pos->x, pos->y);
      pic->sprite.setOrigin(pic->x_origin, pic->y_origin);
      pic->sprite.setScale(pic->x_scale, pic->y_scale);
      pic->sprite.setRotation(pic->rotation);
      pic->sprite.setColor
	(sf::Color(pic->color_mask.argb[RED_CMP],
		   pic->color_mask.argb[GREEN_CMP],
		   pic->color_mask.argb[BLUE_CMP],
		   pic->color_mask.argb[ALPHA_CMP]
		   ));
      spr = &pic->sprite;
    }
  else
    {
      struct bunny_pixelarray	*pic = (struct bunny_pixelarray*)picture;
      int			i;
      int			j;

      for (j = picture->clip_y_position; j < picture->clip_y_position + picture->clip_height; ++j)
	for (i = picture->clip_x_position; i < picture->clip_x_position + picture->clip_width; ++i)
	  if (i >= 0 && j >= 0 && i < picture->buffer.width && j < picture->buffer.height)
	    {
	      unsigned int	c = pic->rawpixels[i + j * pic->width];

	      pic->image.setPixel
		(i, j,
		 sf::Color
		 ((c >> (RED_CMP * 8)) & 0xFF,
		  (c >> (GREEN_CMP * 8)) & 0xFF,
		  (c >> (BLUE_CMP * 8)) & 0xFF,
		  (c >> (ALPHA_CMP * 8)) & 0xFF
		  )
		 );
	    }
      pic->tex.loadFromImage(pic->image, pic->rect);
      pic->sprite.setTexture(pic->tex, true);
      pic->sprite.setPosition(pos->x, pos->y);
      if (gl_full_blit)
	{
	  pic->sprite.setOrigin(pic->x_origin, pic->y_origin);
	  pic->sprite.setScale(pic->x_scale, pic->y_scale);
	  pic->sprite.setRotation(pic->rotation);
	  pic->sprite.setColor
	    (sf::Color(pic->color_mask.argb[RED_CMP],
		       pic->color_mask.argb[GREEN_CMP],
		       pic->color_mask.argb[BLUE_CMP],
		       pic->color_mask.argb[ALPHA_CMP]
		       ));
	}
      spr = &pic->sprite;
    }

  switch (*type)
    {
    case WINDOW:
      {
	struct bunny_window	*out = (struct bunny_window*)output;

	if (*input_type == GRAPHIC_RAM)
	  {
	    if (shader)
	      out->window->draw(*spr, shader);
	    else
	      out->window->draw(*spr);
	  }
	else if (gl_full_blit == false)
	  out->window->draw(*spr, sf::RenderStates(sf::BlendNone));
	else
	  out->window->draw(*spr);
	return ;
      }
    case GRAPHIC_RAM:
      {
	struct bunny_picture	*out = (struct bunny_picture*)output;

	if (*input_type == GRAPHIC_RAM)
	  {
	    if (shader)
	      out->texture->draw(*spr, shader);
	    else
	      out->texture->draw(*spr);
	  }
	else if (gl_full_blit == false)
	  out->texture->draw(*spr, sf::RenderStates(sf::BlendNone));
	else
	  out->texture->draw(*spr);
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
	      gl_bunny_my_blit((t_bunny_pixelarray*)out, pic, pos);
	  }
	else
	  {
	    const bunny_pixelarray	*pic = (const bunny_pixelarray*)output;
	    sf::Image			img = spr->getTexture()->copyToImage();
	    int				i;
	    int				j;

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
		      sf::Color		c = img.getPixel(i, j);
		      int		d = posx.x + posx.y * pic->width;

		      ((t_color*)pic->rawpixels)[d].argb[ALPHA_CMP] = c.a;
		      ((t_color*)pic->rawpixels)[d].argb[RED_CMP] = c.r;
		      ((t_color*)pic->rawpixels)[d].argb[GREEN_CMP] = c.g;
		      ((t_color*)pic->rawpixels)[d].argb[BLUE_CMP] = c.b;
		    }
		}
	  }
	return ;
      }
    }
}

