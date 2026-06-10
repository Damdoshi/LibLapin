// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_rectangular_collision_dot
 * @doc-kind function
 * @doc-module collide
 * @doc-order 440
 * @doc-since 0
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Tests whether a point is inside an axis-aligned area.
 * @param elem Area to test.
 * @param dot Point to test.
 * @return-success Returns true if dot is inside elem.
 * @return-failure Returns false otherwise.
 * @log "collision"
 * @see bunny_rectangular_collision
 *
 * @doc-lang fr
 * @brief Teste si un point est dans une zone alignée sur les axes.
 * @param elem Zone à tester.
 * @param dot Point à tester.
 * @return-success Renvoie true si dot est dans elem.
 * @return-failure Renvoie false sinon.
 * @log "collision"
 * @see bunny_rectangular_collision
 */

/**
 * @doc
 * @doc-symbol bunny_rectangular_collision
 * @doc-kind function
 * @doc-module collide
 * @doc-order 460
 * @doc-since 0
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Tests whether two axis-aligned areas overlap.
 * @param a First area.
 * @param b Second area.
 * @return-success Returns true if the two rectangles overlap.
 * @return-failure Returns false otherwise.
 * @log "collision"
 *
 * @doc-lang fr
 * @brief Teste si deux zones alignées sur les axes se recouvrent.
 * @param a Première zone.
 * @param b Seconde zone.
 * @return-success Renvoie true si les deux rectangles se recouvrent.
 * @return-failure Renvoie false sinon.
 * @log "collision"
 */
bool			bunny_rectangular_collision_dot(const t_bunny_accurate_area	*elem,
							const t_bunny_accurate_position	*pos)
{
  bool			res;

  res = pos->x >= elem->x && pos->x < elem->x + elem->w &&
    pos->y >= elem->y && pos->y < elem->y + elem->h;
  scream_log_if("%p area, %p dot -> %s", "collision", elem, pos, res ? "true" : "false");
  return (res);
}

bool			bunny_rectangular_collision(const t_bunny_accurate_area		*a,
						    const t_bunny_accurate_area		*b)
{
  bool			res;

  res = a->x < b->x + b->w && a->x + a->w > b->x &&
    a->y < b->y + b->h && a->y + a->h > b->y;
  scream_log_if("%p area, %p area -> %s", "collision", a, b, res ? "true" : "false");
  return (res);
}

