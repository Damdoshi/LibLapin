// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include	"lapin_private.h"

bool		bunny_collision_rectangle_circle(const t_bunny_collision	*a,
						 const t_bunny_collision	*b)
{
  const t_bunny_rectangular_collision *rectangle = &a->rectangular;
  const t_bunny_circle_collision *circle = &b->circle;
  t_bunny_accurate_position nearest;
  double	rad = circle->radius;
  double	minx = rectangle->coord[0].x;
  double	maxx = rectangle->coord[0].x + rectangle->coord[1].x;
  double	miny = rectangle->coord[0].y;
  double	maxy = rectangle->coord[0].y + rectangle->coord[1].y;

  if (rad < 0)
    rad = -rad;
  if (minx > maxx)
    {
      double tmp = minx;

      minx = maxx;
      maxx = tmp;
    }
  if (miny > maxy)
    {
      double tmp = miny;

      miny = maxy;
      maxy = tmp;
    }
  nearest.x = circle->coord.x;
  nearest.y = circle->coord.y;
  if (nearest.x < minx)
    nearest.x = minx;
  else if (nearest.x > maxx)
    nearest.x = maxx;
  if (nearest.y < miny)
    nearest.y = miny;
  else if (nearest.y > maxy)
    nearest.y = maxy;
  return (_bunny_collision_distance_square(nearest, circle->coord) <= rad * rad);
}
