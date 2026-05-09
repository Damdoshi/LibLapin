// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

/*!
** Resize the internal rendering surface of a font.
**
** The font remains the same object, but its backing texture is resized and
** cleared. If the current clipping rectangle covered the whole previous
** surface, it is expanded to the new size as well.
**
** \param fnt The font to resize.
** \param width The new surface width in pixels.
** \param height The new surface height in pixels.
** \return True on success, false on error.
*/
bool			bunny_font_resize(t_bunny_font		*fnt,
					  unsigned int		width,
					  unsigned int		height)
{
  struct bunny_picture	*pic = (struct bunny_picture*)fnt;

  if (pic->texture->resize({width, height}) == false)
    return (false);
  if (pic->ntexture && pic->ntexture->resize({width, height}) == false)
    return (false);
  pic->texture->clear(sf::Color(0, 0, 0, 0));
  pic->texture->display();
  pic->tex = &pic->texture->getTexture();
  pic->ntex = pic->ntexture ? &pic->ntexture->getTexture() : NULL;
  if (pic->sprite == NULL)
    {
      if ((pic->sprite = new (std::nothrow) sf::Sprite(*pic->tex)) == NULL)
	return (false);
    }
  else
    pic->sprite->setTexture(*pic->tex); // Safe
  if (pic->rect.w == pic->width && pic->rect.h == pic->height)
    {
      pic->rect.w = width;
      pic->rect.h = height;
    }
  pic->width = width;
  pic->height = height;
  return (true);
}

