// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

#define			PATTERN		"%p picture, %p color"

/**
 * @doc-symbol bunny_fill
 * @doc-module graphics
 * @doc-kind function
 * @doc-order 340
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Applies a color over the clipped area of a buffer using alpha blending.
 * @description Unlike bunny_clear, this operation applies alpha. Drawing into pixelarrays requires gl_bunny_my_fill.
 * @param buffer The target buffer.
 * @param color The color to apply.
 * @error EINVAL The target kind is not supported.
 * @log Logs are written with the "graphics" label.
 * @see bunny_clear, t_bunny_my_fill, gl_bunny_my_fill
 *
 * @doc-lang fr
 * @brief Applique une couleur sur la zone découpée d’un buffer en utilisant l’alpha.
 * @description Contrairement à bunny_clear, cette opération applique l’alpha. Dessiner dans les pixelarrays nécessite gl_bunny_my_fill.
 * @param buffer Le buffer cible.
 * @param color La couleur à appliquer.
 * @error EINVAL Le type de cible n’est pas pris en charge.
 * @log Les logs sont écrits avec le label "graphics".
 * @see bunny_clear, t_bunny_my_fill, gl_bunny_my_fill
 */
void			bunny_fill(t_bunny_buffer		*picture,
				   unsigned int			_color)
{
  size_t		*type = (size_t*)picture;
  sf::RectangleShape	sh;
  sf::Color		color
    ((_color >> (RED_CMP * 8)) & 0xFF,
     (_color >> (GREEN_CMP * 8)) & 0xFF,
     (_color >> (BLUE_CMP * 8)) & 0xFF,
     (_color >> (ALPHA_CMP * 8)) & 0xFF
     );

  sh.setFillColor(color);
  switch (*type)
    {
    case WINDOW:
      {
	struct bunny_window	*win = (struct bunny_window*)picture;

	sh.setSize({win->width, win->height});
	sh.setPosition({0, 0});
	win->window->draw(sh);
	scream_log_if(PATTERN, "graphics", picture, (void*)(size_t)_color);
	return ;
      }
    case TILEMAP:
      {
	struct bunny_tilemap	*pic = (struct bunny_tilemap*)picture;

	if (pic->working != NULL)
	  bunny_fill(&pic->working->buffer, _color);
	[[fallthrough]];
      }
    case PARALLAX:
    case SPRITE:
    case DRESSED_SPRITE:
    case TTF_TEXT:
    case GRAPHIC_TEXT:
    case GRAPHIC_RAM:
    case CINEMATIC:
      {
	struct bunny_picture	*pic = (struct bunny_picture*)picture;
	sf::IntRect		rect({pic->rect.x, pic->rect.y}, {pic->rect.w, pic->rect.h});

	if (pic->res_id != 0)
	  bunny_make_clipable_unique((t_bunny_clipable*)pic);
	sh.setSize({rect.size.x, rect.size.y});
	sh.setPosition({rect.position.x, rect.position.y});
	pic->texture->draw(sh);
	scream_log_if(PATTERN, "graphics", picture, (void*)(size_t)_color);
	return ;
      }
    case SYSTEM_RAM:
      {
	struct bunny_pixelarray	*pix = (struct bunny_pixelarray*)picture;

	if (gl_bunny_my_fill == NULL)
	  fprintf(stderr, "gl_bunny_my_fill is not set.\n");
	else
	  {
	    if (pix->res_id != 0)
	      bunny_make_clipable_unique((t_bunny_clipable*)pix);
	    gl_bunny_my_fill((t_bunny_pixelarray*)pix, _color);
	  }
       	scream_log_if(PATTERN, "graphics", picture, (void*)(size_t)_color);
	return ;
      }
    default:
      scream_error_if
	(return, EINVAL, PATTERN, "graphics", picture, (void*)(size_t)_color);
    }
}

