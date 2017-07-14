// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		<stdint.h>
#include		"lapin_private.h"

#define			PATTERN		\
  "%p picture, (%d, %d) position, %p color"

void			bunny_set_pixel(t_bunny_buffer		*buffer,
					t_bunny_position	position,
					unsigned int		color)
{
  size_t		*type = (size_t*)buffer;
  sf::Vertex		vert[1] =
    {
      sf::Vertex
      (sf::Vector2f(position.x, position.y),
       sf::Color
       ((color >> (RED_CMP * 8)) & 0xFF,
	(color >> (GREEN_CMP * 8)) & 0xFF,
	(color >> (BLUE_CMP * 8)) & 0xFF,
	(color >> (ALPHA_CMP * 8)) & 0xFF
	)
       )
    };

  switch (*type)
    {
    case WINDOW:
      {
	struct bunny_window	*pic = (struct bunny_window*)buffer;

	pic->window->draw(vert, 1, sf::Points);
	scream_log_if(PATTERN, buffer, position.x, position.y, (void*)(size_t)color);
	return ;
      }
    case TTF_TEXT:
    case GRAPHIC_TEXT:
    case GRAPHIC_RAM:
      {
	struct bunny_picture	*pic = (struct bunny_picture*)buffer;

	if (pic->res_id != 0)
	  bunny_make_clipable_unique((t_bunny_clipable*)buffer);
	pic->texture->draw(vert, 1, sf::Points);
	scream_log_if(PATTERN, buffer, position.x, position.y, (void*)(size_t)color);
	return ;
      }
    case SYSTEM_RAM:
      {
	struct bunny_pixelarray	*pix = (struct bunny_pixelarray*)buffer;

	if (gl_bunny_my_set_pixel == NULL)
	  fprintf(stderr, "gl_bunny_my_set_pixel is not set.\n");
	else
	  {
	    if (pix->res_id != 0)
	      bunny_make_clipable_unique((t_bunny_clipable*)buffer);
	    gl_bunny_my_set_pixel((t_bunny_pixelarray*)pix, position, color);
	  }
	scream_log_if(PATTERN, buffer, position.x, position.y, (void*)(size_t)color);
	return ;
      }
    default:
      scream_error_if(return, EINVAL, PATTERN, buffer, position.x, position.y, (void*)(size_t)color);
    }
}

