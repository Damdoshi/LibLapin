// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include	"lapin_private.h"

#define		PATTERN		"%p a, %p b, %f radius -> %s"


/**
 * @doc
 * @doc-symbol bunny_circle_collision_dot
 * @doc-kind function
 * @doc-module collide
 * @doc-order 400
 * @doc-since 0
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Tests whether a point is inside or on a circle.
 * @param elem Circle center.
 * @param dot Point to test.
 * @param radius Circle radius.
 * @return-success Returns true if the point is at most radius units away from elem.
 * @return-failure Returns false otherwise.
 * @log "collision"
 * @see bunny_circle_collision
 *
 * @doc-lang fr
 * @brief Teste si un point est dans ou sur un cercle.
 * @param elem Centre du cercle.
 * @param dot Point à tester.
 * @param radius Rayon du cercle.
 * @return-success Renvoie true si le point est à radius unités au plus de elem.
 * @return-failure Renvoie false sinon.
 * @log "collision"
 * @see bunny_circle_collision
 */
bool		bunny_circle_collision_dot(const t_bunny_accurate_position	*a,
					   const t_bunny_accurate_position	*b,
					   double				r)
{
  double	va, vb;

  va = b->x - a->x;
  vb = b->y - a->y;
  if (va * va + vb * vb < r * r)
    {
      scream_log_if(PATTERN, "collision", a, b, r, "true");
      return (true);
    }
  scream_log_if(PATTERN, "collision", a, b, r, "false");
  return (false);
}

