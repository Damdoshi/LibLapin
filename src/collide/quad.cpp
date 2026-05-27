// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

#define			PATTERN			"%p quad, %p dot -> %s"


/**
 * @doc
 * @doc-symbol bunny_quad_collision_dot
 * @doc-kind function
 * @doc-module collide
 * @doc-order 540
 * @doc-since 0
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Tests whether a point is inside a quadrilateral.
 * @param v4 Vertex array containing four quad vertices.
 * @param dot Point to test.
 * @return-success Returns true if dot is inside the quadrilateral.
 * @return-failure Returns false otherwise.
 * @log "collision"
 * @see bunny_triangle_collision_dot
 *
 * @doc-lang fr
 * @brief Teste si un point est dans un quadrilatère.
 * @param v4 Tableau de sommets contenant les quatre sommets du quadrilatère.
 * @param dot Point à tester.
 * @return-success Renvoie true si dot est dans le quadrilatère.
 * @return-failure Renvoie false sinon.
 * @log "collision"
 * @see bunny_triangle_collision_dot
 */
bool			bunny_quad_collision_dot(const t_bunny_vertex_array		*v4,
						 const t_bunny_accurate_position	*dot)
{
  if (v4->length != 4)
    scream_error_if(return (false), EINVAL, PATTERN, "collision", v4, dot, "false");

  t_bunny_vertex_array	*t1 = (t_bunny_vertex_array*)bunny_alloca(sizeof(*t1) + 3 * sizeof(t1->vertex[0]));
  t_bunny_vertex_array	*t2 = (t_bunny_vertex_array*)bunny_alloca(sizeof(*t1) + 3 * sizeof(t1->vertex[0]));

  t1->length = 3;
  t1->vertex[0].pos.x = v4->vertex[0].pos.x;
  t1->vertex[0].pos.y = v4->vertex[0].pos.y;
  t1->vertex[1].pos.x = v4->vertex[1].pos.x;
  t1->vertex[1].pos.y = v4->vertex[1].pos.y;
  t1->vertex[2].pos.x = v4->vertex[2].pos.x;
  t1->vertex[2].pos.y = v4->vertex[2].pos.y;

  if (bunny_triangle_collision_dot(t1, dot))
    {
      scream_log_if(PATTERN, "collision", v4, dot, "true");
      bunny_freea(t1);
      bunny_freea(t2);
      return (true);
    }

  t2->length = 3;
  t2->vertex[0].pos.x = v4->vertex[0].pos.x;
  t2->vertex[0].pos.y = v4->vertex[0].pos.y;
  t2->vertex[1].pos.x = v4->vertex[2].pos.x;
  t2->vertex[1].pos.y = v4->vertex[2].pos.y;
  t2->vertex[2].pos.x = v4->vertex[3].pos.x;
  t2->vertex[2].pos.y = v4->vertex[3].pos.y;

  if (bunny_triangle_collision_dot(t2, dot))
    {
      scream_log_if(PATTERN, "collision", v4, dot, "true");
      bunny_freea(t1);
      bunny_freea(t2);
      return (true);
    }

  scream_log_if(PATTERN, "collision", v4, dot, "false");
  bunny_freea(t1);
  bunny_freea(t2);
  return (false);
}

