// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

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
	return ;
      }
    case TTF_TEXT:
    case GRAPHIC_TEXT:
    case GRAPHIC_RAM:
      {
	struct bunny_picture	*pic = (struct bunny_picture*)picture;
	sf::IntRect		rect(pic->rect.x, pic->rect.y, pic->rect.w, pic->rect.h);
	sf::RectangleShape	shape;

	shape.setPosition(sf::Vector2f(rect.left, rect.top));
	shape.setSize(sf::Vector2f(rect.width, rect.height));
	shape.setFillColor(color);
	pic->texture->draw(shape, sf::RenderStates(sf::BlendNone));
	return ;
      }
    case SYSTEM_RAM:
      {
	t_bunny_pixelarray	*pix = (t_bunny_pixelarray*)picture;

	if (gl_bunny_my_clear == NULL)
	  fprintf(stderr, "gl_bunny_my_set_clear is not set.\n");
	else
	  gl_bunny_my_clear(pix, _color);
	return ;
      }
    default:
      return ;
    }
}
