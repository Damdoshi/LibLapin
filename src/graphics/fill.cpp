// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

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

	sh.setSize(sf::Vector2f(win->width, win->height));
	sh.setPosition(0, 0);
	win->window->draw(sh);
	return ;
      }
    case GRAPHIC_RAM:
      {
	struct bunny_picture	*pic = (struct bunny_picture*)picture;

	sh.setSize(sf::Vector2f(pic->rect.width, pic->rect.height));
	sh.setPosition(pic->rect.left, pic->rect.top);
	pic->texture->draw(sh);
	return ;
      }
    default:
      {
	t_bunny_pixelarray	*pix = (t_bunny_pixelarray*)picture;

	if (gl_bunny_my_fill == NULL)
	  fprintf(stderr, "gl_bunny_my_fill is not set.\n");
	else
	  gl_bunny_my_fill(pix, _color);
	return ;
      }
    }
}
