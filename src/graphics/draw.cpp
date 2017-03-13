// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

void			bunny_draw(const t_bunny_picture	*picture)
{
  size_t		*typ = (size_t*)picture;

  if (*typ == GRAPHIC_TEXT || *typ == TTF_TEXT)
    _bunny_draw_text((t_bunny_font*)picture);
  struct bunny_picture	*pic = (struct bunny_picture*)picture;

  pic->texture->display();
}

