// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<stdint.h>
#include		"lapin_private.h"

#define			PATTERN		\
  "%p picture, (%d, %d) position, %p color"

/**
 * @doc-symbol bunny_set_pixel
 * @doc-module graphics
 * @doc-kind function
 * @doc-order 220
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Draws one pixel on a buffer.
 * @description Drawing individual pixels on pictures is possible but slow because it uses the graphic backend for each call. Drawing into pixelarrays requires gl_bunny_my_set_pixel.
 * @param buf The target buffer.
 * @param pos The pixel position.
 * @param col The color to draw.
 * @error EINVAL The target kind is not supported.
 * @log Logs are written with the "graphics" label.
 * @see t_bunny_my_set_pixel, gl_bunny_my_set_pixel
 *
 * @doc-lang fr
 * @brief Dessine un pixel dans un buffer.
 * @description Dessiner des pixels individuellement dans des pictures est possible mais lent, car chaque appel utilise le backend graphique. Dessiner dans les pixelarrays nécessite gl_bunny_my_set_pixel.
 * @param buf Le buffer cible.
 * @param pos La position du pixel.
 * @param col La couleur à dessiner.
 * @error EINVAL Le type de cible n’est pas pris en charge.
 * @log Les logs sont écrits avec le label "graphics".
 * @see t_bunny_my_set_pixel, gl_bunny_my_set_pixel
 */
void			bunny_set_pixel(t_bunny_buffer		*buffer,
					t_bunny_position	position,
					unsigned int		color)
{
  size_t		*type = (size_t*)buffer;
  sf::Vertex		vert[1] =
    {
      sf::Vertex
      {sf::Vector2f(position.x, position.y),
       sf::Color
       ((color >> (RED_CMP * 8)) & 0xFF,
	(color >> (GREEN_CMP * 8)) & 0xFF,
	(color >> (BLUE_CMP * 8)) & 0xFF,
	(color >> (ALPHA_CMP * 8)) & 0xFF
	)
      }
    };

  switch (*type)
    {
    case WINDOW:
      {
	struct bunny_window	*pic = (struct bunny_window*)buffer;

	pic->window->draw(vert, 1, sf::PrimitiveType::Points);
	scream_log_if(PATTERN, "graphics", buffer, position.x, position.y, (void*)(size_t)color);
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
	pic->texture->draw(vert, 1, sf::PrimitiveType::Points);
	scream_log_if(PATTERN, "graphics", buffer, position.x, position.y, (void*)(size_t)color);
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
	scream_log_if(PATTERN, "graphics", buffer, position.x, position.y, (void*)(size_t)color);
	return ;
      }
    default:
      scream_error_if(return, EINVAL, PATTERN, "graphics", buffer, position.x, position.y, (void*)(size_t)color);
    }
}

