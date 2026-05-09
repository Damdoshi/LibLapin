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

/**
 * @doc
 * @doc-symbol bunny_font_resize
 * @doc-kind function
 * @doc-module text
 * @doc-order 150
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Resizes the backing texture of a font/text box.
 * @param fnt Font/text box to resize.
 * @param width New width in pixels.
 * @param height New height in pixels.
 * @return-success Returns true on success.
 * @return-failure Returns false on error.
 * @log "ressource,text"
 * @see bunny_load_font
 *
 * @doc-lang fr
 * @brief Redimensionne la texture interne d'une police/boîte de texte.
 * @param fnt Police/boîte de texte à redimensionner.
 * @param width Nouvelle largeur en pixels.
 * @param height Nouvelle hauteur en pixels.
 * @return-success Renvoie true en cas de succès.
 * @return-failure Renvoie false en cas d'erreur.
 * @log "ressource,text"
 * @see bunny_load_font
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

