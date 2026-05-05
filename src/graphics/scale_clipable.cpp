// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
//
// Bibliothèque Lapin

#include	"lapin_private.h"

/**
 * @doc-symbol bunny_scale_clipable
 * @doc-module graphics
 * @doc-kind function
 * @doc-order 455
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Adjusts a clipable scale and position to fit a target buffer.
 * @description The scale type controls whether the clipable is stretched, contained or covered. square_pixel preserves identical X and Y scaling when requested.
 * @param target The target buffer used as reference.
 * @param clip The clipable to adjust.
 * @param scale_type The fitting strategy.
 * @param square_pixel True to keep square pixels when possible.
 * @see t_bunny_scale_type
 *
 * @doc-lang fr
 * @brief Ajuste l’échelle et la position d’un clipable pour l’inscrire dans un buffer cible.
 * @description Le type d’échelle contrôle si le clipable est étiré, contenu ou couvrant. square_pixel conserve une échelle identique en X et Y lorsque demandé.
 * @param target Le buffer cible utilisé comme référence.
 * @param clip Le clipable à ajuster.
 * @param scale_type La stratégie d’ajustement.
 * @param square_pixel Vaut true pour conserver des pixels carrés lorsque c’est possible.
 * @see t_bunny_scale_type
 */
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

