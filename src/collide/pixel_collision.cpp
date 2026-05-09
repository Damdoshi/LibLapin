// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include	"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_pixel_collision
 * @doc-kind function
 * @doc-module collide
 * @doc-order 625
 * @doc-since 0
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Tests whether a point collides with the visible pixels of a clipable.
 * @param pic Clipable picture to test.
 * @param pos Point to test.
 * @param amgn Alpha margin.
 * @return-success Returns true if the selected pixel is considered colliding.
 * @return-failure Returns false otherwise.
 *
 * @doc-lang fr
 * @brief Teste si un point entre en collision avec les pixels visibles d’un clipable.
 * @param pic Picture clipable à tester.
 * @param pos Point à tester.
 * @param amgn Marge alpha.
 * @return-success Renvoie true si le pixel sélectionné est considéré en collision.
 * @return-failure Renvoie false sinon.
 */
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

  return (!(img.getPixel({pos.x, pos.y}).a < alpha_margin * 255));
}

