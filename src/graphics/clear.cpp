// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

#define			PATTERN		"%p picture, %p color"

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
      }
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

	sf::IntRect		rect(pic->rect.x, pic->rect.y, pic->rect.w, pic->rect.h);
	sf::RectangleShape	shape;

	shape.setPosition(sf::Vector2f(rect.left, rect.top));
	shape.setSize(sf::Vector2f(rect.width, rect.height));
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
