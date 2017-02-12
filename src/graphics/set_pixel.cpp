// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		<stdint.h>
#include		"lapin_private.h"

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
	return ;
      }
    case GRAPHIC_RAM:
      {
	struct bunny_picture	*pic = (struct bunny_picture*)buffer;

	pic->texture->draw(vert, 1, sf::Points);
	return ;
      }
    default:
      {
	t_bunny_pixelarray	*pix = (t_bunny_pixelarray*)buffer;

	if (gl_bunny_my_set_pixel == NULL)
	  fprintf(stderr, "gl_bunny_my_set_pixel is not set.\n");
	else
	  gl_bunny_my_set_pixel(pix, position, color);
	return ;
      }
    }
}

