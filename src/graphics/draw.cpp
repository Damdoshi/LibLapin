// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

/**
 * @doc-symbol bunny_draw
 * @doc-module graphics
 * @doc-kind function
 * @doc-order 210
 * @doc-since 0
 * @doc-until latest
 * @doc-level intermediate
 *
 * @doc-lang en
 * @brief Flushes pending drawing operations on a picture-like object.
 * @description Call this on render-target pictures before using them as sources for further blits.
 * @param picture The picture or compatible object to update.
 * @log Logs are written with the "graphics" label.
 * @see bunny_blit, bunny_set_geometry
 *
 * @doc-lang fr
 * @brief Force l’exécution des opérations de dessin en attente sur un objet de type picture.
 * @description Appelez cette fonction sur les pictures cibles de rendu avant de les utiliser comme sources pour d’autres blits.
 * @param picture La picture ou l’objet compatible à mettre à jour.
 * @log Les logs sont écrits avec le label "graphics".
 * @see bunny_blit, bunny_set_geometry
 */
void			bunny_draw(const t_bunny_picture	*picture)
{
  size_t		*typ = (size_t*)picture;

  if (*typ == GRAPHIC_TEXT || *typ == TTF_TEXT)
    _bunny_draw_text((t_bunny_font*)picture);
  else if (*typ == TILEMAP)
    __bunny_draw_tilemap((struct bunny_tilemap*)picture);
  else if (*typ == PARALLAX)
    __bunny_draw_parallax((struct bunny_parallax*)picture);
  else if (*typ == CINEMATIC)
    __bunny_draw_cinematic((struct bunny_cinematic*)picture);
  struct bunny_picture	*pic = (struct bunny_picture*)picture;

  pic->texture->display();
  if (pic->ntexture)
    pic->ntexture->display();
  scream_log_if("%p", "graphics", picture);
}

