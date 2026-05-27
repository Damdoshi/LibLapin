// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

#define			PATTERN		"%p picture, %p color"

/**
 * @doc-symbol bunny_clear
 * @doc-module graphics
 * @doc-kind function
 * @doc-order 370
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Sets the clipped area of a buffer to a color without alpha blending.
 * @description Unlike bunny_fill, this operation writes the color directly. Drawing into pixelarrays requires gl_bunny_my_clear.
 * @param buffer The target buffer.
 * @param color The color to write.
 * @error EINVAL The target kind is not supported.
 * @log Logs are written with the "graphics" label.
 * @see bunny_fill, t_bunny_my_clear, gl_bunny_my_clear
 *
 * @doc-lang fr
 * @brief Fixe la zone découpée d’un buffer à une couleur sans mélange alpha.
 * @description Contrairement à bunny_fill, cette opération écrit directement la couleur. Dessiner dans les pixelarrays nécessite gl_bunny_my_clear.
 * @param buffer Le buffer cible.
 * @param color La couleur à écrire.
 * @error EINVAL Le type de cible n’est pas pris en charge.
 * @log Les logs sont écrits avec le label "graphics".
 * @see bunny_fill, t_bunny_my_clear, gl_bunny_my_clear
 */
void			bunny_clear(t_bunny_buffer		*picture,
				    unsigned int		_color)
{
  size_t		*type = (size_t*)picture;
  sf::Color		color
    ((_color >> (RED_CMP * 8)) & 0xFF,
     (_color >> (GREEN_CMP * 8)) & 0xFF,
     (_color >> (BLUE_CMP * 8)) & 0xFF,
     (_color >> (ALPHA_CMP * 8)) & 0xFF
     );

  switch (*type)
    {
    case WINDOW:
      {
	struct bunny_window	*win = (struct bunny_window*)picture;

	win->window->clear(color);
	scream_log_if(PATTERN, "graphics", picture, (void*)(size_t)_color);
	return ;
      }
    case TILEMAP:
      {
	struct bunny_tilemap	*pic = (struct bunny_tilemap*)picture;

	if (pic->working != NULL)
	  bunny_clear(&pic->working->buffer, _color);
	[[fallthrough]];
      }
    case CINEMATIC:
    case PARALLAX:
    case SPRITE:
    case DRESSED_SPRITE:
    case TTF_TEXT:
    case GRAPHIC_TEXT:
    case GRAPHIC_RAM:
      {
	struct bunny_picture	*pic = (struct bunny_picture*)picture;

	if (pic->res_id != 0)
	  bunny_make_clipable_unique((t_bunny_clipable*)pic);
	if (pic->rect.x == 0 && pic->rect.y == 0 &&
	    pic->rect.w == picture->width && pic->rect.h == picture->height)
	  {
	    pic->texture->clear(color);
	    scream_log_if(PATTERN, "graphics", picture, (void*)(size_t)_color);
	    return ;
	  }

	sf::IntRect		rect({pic->rect.x, pic->rect.y}, {pic->rect.w, pic->rect.h});
	sf::RectangleShape	shape;

	shape.setPosition(sf::Vector2f(rect.position.x, rect.position.y));
	shape.setSize(sf::Vector2f(rect.size.x, rect.size.y));
	shape.setFillColor(color);
	pic->texture->draw(shape, sf::RenderStates(sf::BlendNone));
	scream_log_if(PATTERN, "graphics", picture, (void*)(size_t)_color);
	return ;
      }
    case SYSTEM_RAM:
      {
	struct bunny_pixelarray	*pix = (struct bunny_pixelarray*)picture;

	if (gl_bunny_my_clear == NULL)
	  fprintf(stderr, "gl_bunny_my_set_clear is not set.\n");
	else
	  {
	    if (pix->res_id != 0)
	      bunny_make_clipable_unique((t_bunny_clipable*)pix);
	    gl_bunny_my_clear((t_bunny_pixelarray*)pix, _color);
	  }
	scream_log_if(PATTERN, "graphics", picture, (void*)(size_t)_color);
	return ;
      }
    default:
      scream_error_if(return, EINVAL, PATTERN, "graphics", picture, (void*)(size_t)_color);
    }
}
