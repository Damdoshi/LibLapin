// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
//
// Bibliothèque Lapin

#include	"lapin_private.h"

void		bunny_scale_clipable(const t_bunny_buffer	*t,
				     t_bunny_clipable		*c,
				     t_bunny_scale_type		scale,
				     bool			spixel)
{
  t_bunny_buffer *tc = &c->buffer;
  
  c->scale.x = (double)t->width / c->buffer.width;
  c->scale.y = (double)t->height / c->buffer.height;

  // Ignore square_pixel par définition
  if (scale == BST_STRETCH)
    return ;

  if (scale == BST_CONTAIN)
    {
      if (c->scale.x < c->scale.y)
	c->scale.y = c->scale.x;
      else
	c->scale.x = c->scale.y;
    }
  else // scale == BST_COVER
    {
      if (c->scale.x > c->scale.y)
	c->scale.y = c->scale.x;
      else
	c->scale.x = c->scale.y;
    }

  if (spixel)
    c->scale.y = c->scale.x = floor(c->scale.x);
  c->position.x = (t->width - tc->width * c->scale.x) / 2;
  c->position.y = (t->height - tc->height * c->scale.y) / 2;
}

