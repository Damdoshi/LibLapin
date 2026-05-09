// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_sprite_collide
 * @doc-kind function
 * @doc-module sprite
 * @doc-order 286
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Tests collision between the current frames of two sprites.
 * @param a First sprite.
 * @param b Second sprite.
 * @param couple Optional string couples used by collision filtering.
 * @param len Number of entries in couple.
 * @return-success Returns the number or index of detected collision according to the collision backend.
 * @return-failure Returns 0 when no collision is detected.
 * @see bunny_sprite_get_collision
 *
 * @doc-lang fr
 * @brief Teste la collision entre les frames courantes de deux sprites.
 * @param a Premier sprite.
 * @param b Deuxième sprite.
 * @param couple Couples de chaînes optionnels utilisés par le filtrage de collision.
 * @param len Nombre d'entrées dans couple.
 * @return-success Renvoie le nombre ou l'index de collision détectée selon le backend de collision.
 * @return-failure Renvoie 0 si aucune collision n'est détectée.
 * @see bunny_sprite_get_collision
 */
int			bunny_sprite_collide(const t_bunny_sprite	*a,
					     const t_bunny_sprite	*b,
					     t_bunny_string_couple	*couple,
					     size_t			len)
{
  const t_bunny_collision_shapes *as;
  const t_bunny_collision_shapes *bs;

  as = bunny_sprite_get_collision(a);
  bs = bunny_sprite_get_collision(b);
  if (!as || !bs)
    return (-1);
  return
    (bunny_collision_nbr
     (as->collisions, as->nbr_collision, NULL, 0,
      bs->collisions, bs->nbr_collision, NULL, 0,
      couple, len
      ));
}

