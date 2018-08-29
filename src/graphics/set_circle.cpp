// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

#define			PATTERN \
  "%p picture, (%d, %d) position, (%d, %d) size, %p color"

void			bunny_set_disk(t_bunny_buffer		*buffer,
				       t_bunny_position		pos,
				       t_bunny_position		siz,
				       unsigned int		incolor,
				       unsigned int		outcolor,
				       int			outline_thickness)
{
  size_t		*type = (size_t*)buffer;
  sf::CircleShape	shape;
  double		coef;

  if (*type != SYSTEM_RAM)
    {
      shape.setRadius(siz.x);
      shape.setScale(sf::Vector2f(1, (double)(coef = (double)siz.y / siz.x)));
      shape.setPosition(sf::Vector2f(pos.x - siz.x, pos.y - siz.y));
      shape.setFillColor
	(sf::Color
	 ((incolor >> (RED_CMP * 8)) & 0xFF,
	  (incolor >> (GREEN_CMP * 8)) & 0xFF,
	  (incolor >> (BLUE_CMP * 8)) & 0xFF,
	  (incolor >> (ALPHA_CMP * 8)) & 0xFF
	  )
	 );
      shape.setOutlineColor
	(sf::Color
	 ((outcolor >> (RED_CMP * 8)) & 0xFF,
	  (outcolor >> (GREEN_CMP * 8)) & 0xFF,
	  (outcolor >> (BLUE_CMP * 8)) & 0xFF,
	  (outcolor >> (ALPHA_CMP * 8)) & 0xFF
	  )
	 );
      shape.setOutlineThickness(outline_thickness);
    }
  switch (*type)
    {
    case WINDOW:
      {
	struct bunny_window	*pic = (struct bunny_window*)buffer;

	pic->window->draw(shape);
	scream_log_if(PATTERN, "graphics", buffer, pos.x, pos.y, siz.x, siz.y, (void*)(size_t)outcolor);
	return ;
      }
    case TTF_TEXT:
    case GRAPHIC_RAM:
    case GRAPHIC_TEXT:
      {
	struct bunny_picture	*pic = (struct bunny_picture*)buffer;

	pic->texture->draw(shape);
	scream_log_if(PATTERN, "graphics", buffer, pos.x, pos.y, siz.x, siz.y, (void*)(size_t)outcolor);
	return ;
      }
    case SYSTEM_RAM:
      {
	t_bunny_pixelarray	*pix = (t_bunny_pixelarray*)buffer;

	if (gl_bunny_my_set_disk == NULL)
	  fprintf(stderr, "gl_bunny_my_set_disk is not set.\n");
	else
	  gl_bunny_my_set_disk(pix, pos, siz, incolor, outcolor, outline_thickness);
	scream_log_if(PATTERN, "graphics", buffer, pos.x, pos.y, siz.x, siz.y, (void*)(size_t)outcolor);
	return ;
      }
    default:
      scream_error_if(return, EINVAL, PATTERN, "graphics", buffer, pos.x, pos.y, siz.x, siz.y, (void*)(size_t)outcolor);
    }
}
