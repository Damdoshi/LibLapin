// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include	"lapin_private.h"

bool		bunny_pixel_collision(t_bunny_clipable		*_pic,
				      const t_bunny_position	*_pos,
				      double			alpha_margin)
{

  struct bunny_picture *pic = (struct bunny_picture*)_pic;
  t_bunny_position	pos;
  sf::IntRect		rect;

  pos.x = _pos->x - pic->position.x;
  pos.y = _pos->y - pic->position.y;
  if (pos.x < 0
      || pos.y < 0
      || pos.x >= _pic->clip_width
      || pos.y >= _pic->clip_height)
    return (false);

  pos.x += pic->rect.x;
  pos.y += pic->rect.y;

  if (pic->type == SYSTEM_RAM)
    {
      t_bunny_pixelarray *px = (t_bunny_pixelarray*)_pic;
      t_bunny_color col;

      col.full = ((unsigned int*)px->pixels)
	[pos.x + pos.y * px->clipable.buffer.width];
      return (!(col.argb[ALPHA_CMP] < alpha_margin * 255));
    }
  sf::Image		img = pic->tex->copyToImage();

  return (!(img.getPixel(pos.x, pos.y).a < alpha_margin * 255));
}

