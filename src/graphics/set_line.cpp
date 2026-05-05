// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

#define			PATTERN \
  "%p picture, %p (%d, %d -> %d, %d) position, %p (%p -> %p) color"

/**
 * @doc-symbol bunny_set_line
 * @doc-module graphics
 * @doc-kind function
 * @doc-order 280
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Draws a line on a buffer.
 * @description The two colors are used as endpoint colors and may produce a gradient. Drawing into pixelarrays requires gl_bunny_my_set_line.
 * @param buf The target buffer.
 * @param pos An array containing the two endpoints.
 * @param col An array containing the two endpoint colors.
 * @error EINVAL The target kind is not supported.
 * @log Logs are written with the "graphics" label.
 * @see t_bunny_my_set_line, gl_bunny_my_set_line
 *
 * @doc-lang fr
 * @brief Dessine une ligne dans un buffer.
 * @description Les deux couleurs sont utilisées comme couleurs d’extrémité et peuvent produire un dégradé. Dessiner dans les pixelarrays nécessite gl_bunny_my_set_line.
 * @param buf Le buffer cible.
 * @param pos Un tableau contenant les deux extrémités.
 * @param col Un tableau contenant les deux couleurs d’extrémité.
 * @error EINVAL Le type de cible n’est pas pris en charge.
 * @log Les logs sont écrits avec le label "graphics".
 * @see t_bunny_my_set_line, gl_bunny_my_set_line
 */
void			bunny_set_line(t_bunny_buffer		*buffer,
				       const t_bunny_position	*position,
				       const unsigned int	*color)
{
  size_t		*type = (size_t*)buffer;
  sf::Vertex		vert[2] =
    {
      sf::Vertex
      {sf::Vector2f(position[0].x, position[0].y),
       sf::Color
       ((color[0] >> (RED_CMP * 8)) & 0xFF,
	(color[0] >> (GREEN_CMP * 8)) & 0xFF,
	(color[0] >> (BLUE_CMP * 8)) & 0xFF,
	(color[0] >> (ALPHA_CMP * 8)) & 0xFF
	)
      },

      sf::Vertex
      {sf::Vector2f(position[1].x, position[1].y),
       sf::Color
       ((color[1] >> (RED_CMP * 8)) & 0xFF,
	(color[1] >> (GREEN_CMP * 8)) & 0xFF,
	(color[1] >> (BLUE_CMP * 8)) & 0xFF,
	(color[1] >> (ALPHA_CMP * 8)) & 0xFF
	)
      }
    };

  switch (*type)
    {
    case WINDOW:
      {
	struct bunny_window	*pic = (struct bunny_window*)buffer;

	pic->window->draw(vert, 2, sf::PrimitiveType::Lines);
	scream_log_if
	  (PATTERN, "graphics", buffer,
	   position, position[0].x, position[0].y, position[1].x, position[1].y,
	   color, (void*)(size_t)color[0], (void*)(size_t)color[1]);
	return ;
      }
    case PARALLAX:
    case DRESSED_SPRITE:
    case SPRITE:
    case TTF_TEXT:
    case GRAPHIC_TEXT:
    case GRAPHIC_RAM:
      {
	struct bunny_picture	*pic = (struct bunny_picture*)buffer;

	if (pic->res_id != 0)
	  bunny_make_clipable_unique((t_bunny_clipable*)buffer);
	pic->texture->draw(vert, 2, sf::PrimitiveType::Lines);
	scream_log_if
	  (PATTERN, "graphics", buffer,
	   position, position[0].x, position[0].y, position[1].x, position[1].y,
	   color, (void*)(size_t)color[0], (void*)(size_t)color[1]);
	return ;
      }
    case SYSTEM_RAM:
      {
	struct bunny_pixelarray	*pix = (struct bunny_pixelarray*)buffer;

	if (gl_bunny_my_set_line == NULL)
	  fprintf(stderr, "gl_bunny_my_set_line is not set.\n");
	else
	  {
	    if (pix->res_id != 0)
	      bunny_make_clipable_unique((t_bunny_clipable*)buffer);
	    gl_bunny_my_set_line((t_bunny_pixelarray*)pix, position, color);
	  }
	scream_log_if
	  (PATTERN, "graphics", buffer,
	   position, position[0].x, position[0].y, position[1].x, position[1].y,
	   color, (void*)(size_t)color[0], (void*)(size_t)color[1]);
	return ;
      }
    default:
      scream_error_if
	(return, EINVAL, PATTERN, "graphics", buffer,
	 position, position[0].x, position[0].y, position[1].x, position[1].y,
	 color, (void*)(size_t)color[0], (void*)(size_t)color[1]);
    }
}
