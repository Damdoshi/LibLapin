// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

#define			PATTERN		"%p picture, %p color"

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
	sf::IntRect		rect(pic->rect.x, pic->rect.y, pic->rect.w, pic->rect.h);

	if (pic->res_id != 0)
	  bunny_make_clipable_unique((t_bunny_clipable*)pic);
	sh.setSize(sf::Vector2f(rect.width, rect.height));
	sh.setPosition(rect.left, rect.top);
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

