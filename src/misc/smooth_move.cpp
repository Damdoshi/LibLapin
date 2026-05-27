// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_smooth_move
 * @doc-kind function
 * @doc-module misc
 * @doc-order 360
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Moves an integer position smoothly toward a target.
 * @param target Target position.
 * @param current Position to update.
 * @param speed Interpolation factor, usually between 0 and 1.
 * @log "misc"
 *
 * @doc-lang fr
 * @brief Déplace progressivement une position entière vers une cible.
 * @param target Position cible.
 * @param current Position à mettre à jour.
 * @param speed Facteur d'interpolation, généralement entre 0 et 1.
 * @log "misc"
 */
void			bunny_smooth_move(const t_bunny_position	*target,
					  t_bunny_position		*current,
					  double			speed)
{
  t_bunny_position	res;

  res.x = speed * (target->x - current->x) + current->x;
  res.y = speed * (target->y - current->y) + current->y;
  current->x = res.x;
  current->y = res.y;
  scream_log_if("%p (%d, %d) target, %p (%d, %d) current, %f speed", "misc",
		target, target->x, target->y,
		current, current->x, current->y,
		speed);
}

