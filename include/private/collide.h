/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
**
** Bibliotheque Lapin
*/

#ifndef			__LAPIN_PRIVATE_COLLIDE_H__
# define		__LAPIN_PRIVATE_COLLIDE_H__

typedef bool		t_bunny_collide_func(const t_bunny_collision	*a,
					     const t_bunny_collision	*b);

t_bunny_collide_func	bunny_collision_equation_equation;
t_bunny_collide_func	bunny_collision_equation_quad;
t_bunny_collide_func	bunny_collision_equation_rectangle;
t_bunny_collide_func	bunny_collision_equation_triangle;
t_bunny_collide_func	bunny_collision_equation_line;
t_bunny_collide_func	bunny_collision_equation_circle;

t_bunny_collide_func	bunny_collision_quad_quad;
t_bunny_collide_func	bunny_collision_quad_rectangle;
t_bunny_collide_func	bunny_collision_quad_triangle;
t_bunny_collide_func	bunny_collision_quad_line;
t_bunny_collide_func	bunny_collision_quad_circle;
t_bunny_collide_func	bunny_collision_quad_dot;

t_bunny_collide_func	bunny_collision_rectangle_rectangle;
t_bunny_collide_func	bunny_collision_rectangle_triangle;
t_bunny_collide_func	bunny_collision_rectangle_line;
t_bunny_collide_func	bunny_collision_rectangle_circle;
t_bunny_collide_func	bunny_collision_rectangle_dot;

t_bunny_collide_func	bunny_collision_triangle_triangle;
t_bunny_collide_func	bunny_collision_triangle_line;
t_bunny_collide_func	bunny_collision_triangle_circle;
t_bunny_collide_func	bunny_collision_triangle_dot;

t_bunny_collide_func	bunny_collision_line_line;
t_bunny_collide_func	bunny_collision_line_circle;
t_bunny_collide_func	bunny_collision_line_dot;

t_bunny_collide_func	bunny_collision_circle_circle;
t_bunny_collide_func	bunny_collision_circle_dot;

t_bunny_collide_func	bunny_collision_dot_dot;

bool			_get_point_on_circle(const t_bunny_accurate_position *coord,
					     double			rad,
					     int			nbr, //0 to 7
					     t_bunny_accurate_position *out);

static inline double	_bunny_collision_cross(const t_bunny_accurate_position &a,
					       const t_bunny_accurate_position &b,
					       const t_bunny_accurate_position &c)
{
  return ((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x));
}

static inline double	_bunny_collision_dot_product(const t_bunny_accurate_position &a,
						     const t_bunny_accurate_position &b,
						     const t_bunny_accurate_position &c)
{
  return ((b.x - a.x) * (c.x - a.x) + (b.y - a.y) * (c.y - a.y));
}

static inline double	_bunny_collision_distance_square(const t_bunny_accurate_position &a,
						       const t_bunny_accurate_position &b)
{
  double		dx = b.x - a.x;
  double		dy = b.y - a.y;

  return (dx * dx + dy * dy);
}

static inline bool	_bunny_collision_point_on_segment(const t_bunny_accurate_position &a,
						       const t_bunny_accurate_position &b,
						       const t_bunny_accurate_position &p,
						       double			margin = 0.001)
{
  double		len = _bunny_collision_distance_square(a, b);
  double		cross;

  if (len < 0.000001)
    return (_bunny_collision_distance_square(a, p) <= margin * margin);
  cross = _bunny_collision_cross(a, b, p);
  if (cross * cross > margin * margin * len)
    return (false);
  if (_bunny_collision_dot_product(a, b, p) < -margin)
    return (false);
  if (_bunny_collision_dot_product(b, a, p) < -margin)
    return (false);
  return (true);
}

static inline double	_bunny_collision_point_segment_distance_square(const t_bunny_accurate_position &a,
								     const t_bunny_accurate_position &b,
								     const t_bunny_accurate_position &p)
{
  double		len = _bunny_collision_distance_square(a, b);
  double		t;
  t_bunny_accurate_position proj;

  if (len < 0.000001)
    return (_bunny_collision_distance_square(a, p));
  t = ((p.x - a.x) * (b.x - a.x) + (p.y - a.y) * (b.y - a.y)) / len;
  if (t < 0)
    t = 0;
  else if (t > 1)
    t = 1;
  proj.x = a.x + t * (b.x - a.x);
  proj.y = a.y + t * (b.y - a.y);
  return (_bunny_collision_distance_square(proj, p));
}

static inline bool	_bunny_collision_segment_intersection(const t_bunny_accurate_position &a,
						  const t_bunny_accurate_position &b,
						  const t_bunny_accurate_position &c,
						  const t_bunny_accurate_position &d)
{
  double		abc = _bunny_collision_cross(a, b, c);
  double		abd = _bunny_collision_cross(a, b, d);
  double		cda = _bunny_collision_cross(c, d, a);
  double		cdb = _bunny_collision_cross(c, d, b);

  if (fabs(abc) <= 0.001 && _bunny_collision_point_on_segment(a, b, c))
    return (true);
  if (fabs(abd) <= 0.001 && _bunny_collision_point_on_segment(a, b, d))
    return (true);
  if (fabs(cda) <= 0.001 && _bunny_collision_point_on_segment(c, d, a))
    return (true);
  if (fabs(cdb) <= 0.001 && _bunny_collision_point_on_segment(c, d, b))
    return (true);
  return (((abc > 0 && abd < 0) || (abc < 0 && abd > 0)) &&
	  ((cda > 0 && cdb < 0) || (cda < 0 && cdb > 0)));
}

#endif	/*		__LAPIN_PRIVATE_COLLIDE_H__	*/
