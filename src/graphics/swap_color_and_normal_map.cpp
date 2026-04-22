// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2026
//
// Bibliothèque Lapin

#include		"lapin_private.h"

static void		swap(void						**a,
			     void						**b)
{
  void			*c;

  c = *a;
  *a = *b;
  *b = c;
}

bool			bunny_swap_color_and_normal_map(t_bunny_clipable	*s)
{
  struct bunny_picture	*pic = (struct bunny_picture*)s;

  if (pic->ntexture == NULL)
    return (false);
  swap((void**)&pic->ntexture, (void**)&pic->texture);
  swap((void**)&pic->ntex, (void**)&pic->tex);
  pic->sprite->setTexture(*pic->tex);
  return (true);
}

