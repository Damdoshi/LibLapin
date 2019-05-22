/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Bibliotheque Lapin
*/

/*!
** \file collide.h
** Functions to detect collisions and structure to represent complex collision shape.
*/

#ifndef		__LAPIN_COLLIDE_H__
# define	__LAPIN_COLLIDE_H__
# if		!defined(__LAPIN_H__)
#  error	You cannot include this file directly.
# endif

/*!
** Return true if the distance elem-dot is inferior to radius
** \param elem The elem to collide with
** \param dot The dot to collide with
** \param radius The distance between elem and dot that indicates a collision
** \return True if elem->dot < radius
*/
bool		bunny_circle_collision_dot(const t_bunny_accurate_position	*elem,
					   const t_bunny_accurate_position	*dot,
					   double				radius);

/*!
** Return true if the distance center of a-center of b is inferior to both added radius
** \param a A circle that will collide with another one
** \param r1 The first circle radius
** \param b The other circle that will collide with the first one
** \param r2 The second circle radius
** \return True if circle collide
*/
# define	bunny_circle_collision(a, r1, b, r2)				\
  bunny_circle_collision_dot(a, b, r1 + r2)

/*!
** Return true if dot is inside area.
** \param area The zone in which it collides
** \param dot The dot that may collide
** \return True if it collides
*/
bool		bunny_rectangular_collision_dot(const t_bunny_accurate_area	*elem,
						const t_bunny_accurate_position	*dot);

/*!
** Return true if a and b rectangle collides.
** \param a A first rectangle
** \param b A second rectangle
** \return True if rectangles overlaps.
*/
bool		bunny_rectangular_collision(const t_bunny_accurate_area		*a,
					    const t_bunny_accurate_area		*b);

/*!
** Return true if dot is on the clip
** \param clip The clipable
** \param dot The dot
** \return True if dot is on clip
*/
bool		bunny_clip_collision_dot(const t_bunny_clipable			*clip,
					 const t_bunny_accurate_position	*dot);

/*!
** Return true if a and b clip collides.
** \param a A first clip
** \param b A second clip
** \return True if clips overlaps.
*/
bool		bunny_clip_collision(const t_bunny_clipable			*a,
				     const t_bunny_clipable			*b);


/*!
** Return true if dot is inside the triangle.
** \param v3 A 3 elements vertex_array
** \param dot The position to test
** \return True if it collides.
*/
bool		bunny_triangle_collision_dot(const t_bunny_vertex_array		*v3,
					     const t_bunny_accurate_position	*dot);

/*!
** Return true if dot is inside the quad.
** \param v4 A 4 elements vertex_array
** \param dot The position to test
** \return True if it collides.
*/
bool		bunny_quad_collision_dot(const t_bunny_vertex_array		*v4,
					 const t_bunny_accurate_position	*dot);

/*!
** This enumeration is used as recognition token for t_bunny_collision.
** Each values, except for LAST_COLLISION_TYPE may be used and the union
** filled accordingly.
*/
typedef enum	e_bunny_collision_type
  {
    BCT_DOT,
    BCT_CIRCLE,
    BCT_LINE,
    BCT_TRIANGLE,
    BCT_RECTANGLE,
    BCT_QUAD,
    BCT_EQUATION,
    LAST_COLLISION_TYPE
  }		t_bunny_collision_type;

/*!
** The t_bunny_dot_collision represents a single dot in space.
** It has no size, only coordinates and may be used to check
** if it has the same coordinates as an other dot or if it is
** inside an area of any shape.
** Its type field must be set to BCT_DOT.
** Its coord attribute is its coordinate.
*/
typedef struct	s_bunny_dot_collision
{
  t_bunny_collision_type type;
  t_bunny_accurate_position coord;
}		t_bunny_dot_collision;

/*!
** The t_bunny_circle_collision represents a circle in space.
** It has a radius and coordinates of its center.
** Its type field must be set to BCT_CIRCLE.
** Its coord attribute is the coordinate of the center of the circle.
** If its radius field is between -1 and 1, it is considered as a dot.
*/
typedef struct	s_bunny_circle_collision
{
  t_bunny_collision_type type;
  t_bunny_accurate_position coord;
  double	radius;
}		t_bunny_circle_collision;

/*!
** The t_bunny_line_collision represents two dots with a specific
** amount of points inbetween.
** Its type field must be set to BCT_LINE.
** Its coord attribute is an array with coordinates of each side of the line.
** Its intermediate_points attribute must be greater or equal to 0.
*/
typedef struct	s_bunny_line_collision
{
  t_bunny_collision_type type;
  t_bunny_accurate_position coord[2];
  double	intermediate_points;
}		t_bunny_line_collision;

/*!
** The t_bunny_triangle_collision represents a triangle.
** Its type field must be set to BCT_TRIANGLE.
** Its coord attribute is an array with coordinates of each extremities.
*/
typedef struct	s_bunny_triangle_collision
{
  t_bunny_collision_type type;
  t_bunny_accurate_position coord[3];
}		t_bunny_triangle_collision;


/*!
** The t_bunny_rectangular_collision represents a rectangle.
** Its type field must be set to BCT_RECTANGLE.
** Its coord attribute is an array with the position of the top left corner
** and then the size of the rectangle.
*/
typedef struct	s_bunny_rectangular_collision
{
  t_bunny_collision_type type;
  t_bunny_accurate_position coord[2];
}		t_bunny_rectangular_collision;

/*!
** The t_bunny_quad_collision represents a quad.
** Its type field must be set to BCT_QUAD.
** Its coord attribute is an array of coordinates for the quad.
*/
typedef struct	s_bunny_quad_collision
{
  t_bunny_collision_type type;
  t_bunny_accurate_position coord[4];
}		t_bunny_quad_collision;

/*!
** The t_bunny_equation_collision describe a rectangular area
** in which collision rely on a second degree equation:
**                a * x^2 + b * x + c
** This allow to build complex collision shape, tile per tile.
**
** The origin_at_center indicates that the origin is
** considered at the middle of area. If false, it is in a corner:
** If flipx and flipy are false, it is the top left one.
** If flipx is true and flipy is false, it is the top right.
** If flipy is true and flipx is false, it is the bottom left.
** If they are both true, it is the bottom right.
**
** Its type field must be set to BCT_EQUATION.
*/
typedef struct	s_bunny_equation_collision
{
  t_bunny_collision_type type;
  t_bunny_accurate_position coord[2];
  t_bunny_accurate_position amplitude;
  double	a;
  double	b;
  double	c;
  bool		origin_at_center;
  bool		flipx;
  bool		flipy;
}		t_bunny_equation_collision;

typedef struct		s_bunny_collide_point
{
  double		radian;
  t_bunny_accurate_position position;
}			t_bunny_collide_point;

/*!
** Test if the dot is colliding with the equation: colliding means that for the
** position on X, its position on Y is greater than the equation value for X.
** \param a The equation that will be used to test the collision.
** \param b The dot that will be used to test the collision.
** \return A pair of radian and position that are the spot where to collision
** occurs (The X/Y value of the equation for the sent X) and the inclinaison
** of the position.
*/
t_bunny_collide_point bunny_collision_equation_dot(const t_bunny_equation_collision *a,
						   const t_bunny_dot_collision	*b);

/*!
** The u_bunny_collision union contains every t_bunny_*_collision
** structure as available types. Its first field is the common part: the type
** of the collision.
** Depending of the type you will set in this field, you may use one of the other
** field accordingly.
** For example, if you set type to BCT_RECTANGLE, you should use the rectangular
** field.
*/
typedef union	u_bunny_collision
{
  t_bunny_collision_type type;
  t_bunny_dot_collision dot;
  t_bunny_circle_collision circle;
  t_bunny_line_collision line;
  t_bunny_triangle_collision triangle;
  t_bunny_rectangular_collision rectangular;
  t_bunny_quad_collision quad;
  t_bunny_equation_collision equation;
}		t_bunny_collision;

/*!
** Return if the two shapes collides, whatever they are.
** \param a A shape to test the collision with
** \param a A shape to test the collision with
** \return True if shapes collides
*/
bool		bunny_collide(const t_bunny_collision				*a,
			      const t_bunny_collision				*b);

bool		bunny_collision(const t_bunny_collision				*a,
				const t_bunny_accurate_position			*posa,
				double						rota,
				const t_bunny_collision				*b,
				const t_bunny_accurate_position			*posb,
				double						rotb);

bool		bunny_collision_nbr(const t_bunny_collision			*a,
				    size_t					lena,
				    const t_bunny_accurate_position		*posa,
				    double					rota,
				    const t_bunny_collision			*b,
				    size_t					lenb,
				    const t_bunny_accurate_position		*posb,
				    double					rotb);

void		bunny_move_collision(t_bunny_collision				*a,
				     t_bunny_accurate_position			move);

void		bunny_turn_collision(t_bunny_collision				*a,
				     double					moment);
/*!
** Draw the collision shape on the sent buffer.
** \param tar The surface where to draw the collision
** \param x The collision to draw
** \param col The color that will be used to draw the collision
*/
void		bunny_draw_collision_shape(t_bunny_buffer			*tar,
					   const t_bunny_collision		*x,
					   unsigned int				col);

void		bunny_set_collision_shape(t_bunny_buffer			*tar,
					  const t_bunny_collision		*x,
					  t_bunny_position			pos,
					  unsigned int				col);

bool		bunny_pixel_collision(t_bunny_clipable				*pic,
				      const t_bunny_position			*pos,
				      double					amgn);

t_bunny_decision bunny_collision_configuration(const char			*field,
					       t_bunny_collision		**col,
					       int				*len,
					       t_bunny_configuration		*cnf);

#endif	/*	__LAPIN_COLLIDE_H__						*/
