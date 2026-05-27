// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

#define			PATTERN			"%p quad, %p dot -> %s"

static double		_scalar(const t_bunny_accurate_position			*a,
				const t_bunny_accurate_position			*b)
{
  return (a->x * b->x + a->y * b->y);
}


/**
 * @doc
 * @doc-symbol bunny_triangle_collision_dot
 * @doc-kind function
 * @doc-module collide
 * @doc-order 520
 * @doc-since 0
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Tests whether a point is inside a triangle.
 * @param v3 Vertex array containing three triangle vertices.
 * @param dot Point to test.
 * @return-success Returns true if dot is inside the triangle.
 * @return-failure Returns false otherwise.
 * @log "collision"
 * @see bunny_quad_collision_dot
 *
 * @doc-lang fr
 * @brief Teste si un point est dans un triangle.
 * @param v3 Tableau de sommets contenant les trois sommets du triangle.
 * @param dot Point à tester.
 * @return-success Renvoie true si dot est dans le triangle.
 * @return-failure Renvoie false sinon.
 * @log "collision"
 * @see bunny_quad_collision_dot
 */
bool			bunny_triangle_collision_dot(const t_bunny_vertex_array		*v3,
						     const t_bunny_accurate_position	*dot)
{
  t_bunny_accurate_position vec[3];
  double		scalar[5];
  double		inv;
  double		u, v;

  if (v3->length != 3)
    scream_error_if(return (false), EINVAL, PATTERN, "collision", v3, dot, "false");

  vec[0].x = v3->vertex[2].pos.x - v3->vertex[0].pos.x;
  vec[0].y = v3->vertex[2].pos.y - v3->vertex[0].pos.y;

  vec[1].x = v3->vertex[1].pos.x - v3->vertex[0].pos.x;
  vec[1].y = v3->vertex[1].pos.y - v3->vertex[0].pos.y;

  vec[2].x = dot->x - v3->vertex[0].pos.x;
  vec[2].y = dot->y - v3->vertex[0].pos.y;

  scalar[0] = _scalar(&vec[0], &vec[0]);
  scalar[1] = _scalar(&vec[0], &vec[1]);
  scalar[2] = _scalar(&vec[0], &vec[2]);
  scalar[3] = _scalar(&vec[1], &vec[1]);
  scalar[4] = _scalar(&vec[1], &vec[2]);

  inv = scalar[0] * scalar[3] - scalar[1] * scalar[1];
  if (fabs(inv) < 0.000001)
    {
      if (_bunny_collision_point_on_segment(v3->vertex[0].pos, v3->vertex[1].pos, *dot) ||
	  _bunny_collision_point_on_segment(v3->vertex[1].pos, v3->vertex[2].pos, *dot) ||
	  _bunny_collision_point_on_segment(v3->vertex[2].pos, v3->vertex[0].pos, *dot))
	{
	  scream_log_if(PATTERN, "collision", v3, dot, "true");
	  return (true);
	}
      scream_log_if(PATTERN, "collision", v3, dot, "false");
      return (false);
    }
  inv = 1.0 / inv;
  u = (scalar[3] * scalar[2] - scalar[1] * scalar[4]) * inv;
  v = (scalar[0] * scalar[4] - scalar[1] * scalar[2]) * inv;

  if ((u >= -0.000001) && (v >= -0.000001) && (u + v <= 1.000001))
    {
      scream_log_if(PATTERN, "collision", v3, dot, "true");
      return (true);
    }
  scream_log_if(PATTERN, "collision", v3, dot, "false");
  return (false);
}

