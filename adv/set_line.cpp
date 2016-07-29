// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

void			bunny_set_line(t_bunny_buffer		*buffer,
				       const t_bunny_position	*position,
				       const unsigned int	*color)
{
  size_t		*type = (size_t*)buffer;
  sf::Vertex		vert[2] =
    {
      sf::Vertex
      (sf::Vector2f(position[0].x, position[0].y),
       sf::Color
       ((color[0] >> (RED_CMP * 8)) & 0xFF,
	(color[0] >> (GREEN_CMP * 8)) & 0xFF,
	(color[0] >> (BLUE_CMP * 8)) & 0xFF,
	(color[0] >> (ALPHA_CMP * 8)) & 0xFF
	)
       ),

      sf::Vertex
      (sf::Vector2f(position[1].x, position[1].y),
       sf::Color
       ((color[1] >> (RED_CMP * 8)) & 0xFF,
	(color[1] >> (GREEN_CMP * 8)) & 0xFF,
	(color[1] >> (BLUE_CMP * 8)) & 0xFF,
	(color[1] >> (ALPHA_CMP * 8)) & 0xFF
	)
       )
    };

  switch (*type)
    {
    case WINDOW:
      {
	struct bunny_window	*pic = (struct bunny_window*)buffer;

	pic->window->draw(vert, 2, sf::Lines);
	return ;
      }
    case GRAPHIC_RAM:
      {
	struct bunny_picture	*pic = (struct bunny_picture*)buffer;

	pic->texture->draw(vert, 2, sf::Lines);
	return ;
      }
    default:
      {
	t_bunny_pixelarray	*pix = (t_bunny_pixelarray*)buffer;

	if (gl_bunny_my_set_line == NULL)
	  fprintf(stderr, "gl_bunny_my_set_line is not set.\n");
	else
	  gl_bunny_my_set_line(pix, position, color);
	return ;
      }
    }
}
