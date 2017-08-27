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



#endif	/*		__LAPIN_PRIVATE_COLLIDE_H__	*/
