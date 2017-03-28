/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Bibliotheque Lapin
*/

/*!
** \file collide.h
** Functions to detect collisions
*/

#ifndef				__LAPIN_COLLIDE_H__
# define			__LAPIN_COLLIDE_H__

/*!
** Return true if the distance elem-dot is inferior to radius
** \param elem The elem to collide with
** \param dot The dot to collide with
** \param radius The distance between elem and dot that indicates a collision
** \return True if elem->dot < radius
*/
bool				bunny_circle_collision_dot(const t_bunny_accurate_position	*elem,
							   const t_bunny_accurate_position	*dot,
							   double				radius);
# define			bunny_circle_collision(a, r1, b, r2)				\
  bunny_circle_collision_dot(elem, dot, r1 + r2)

/*!
** Return true if dot is inside area.
** \param area The zone in which it collides
** \param dot The dot that may collide
** \return True if it collides
*/
bool				bunny_retangular_collision_dot(const t_bunny_accurate_area	*elem,
							       const t_bunny_accurate_position	*dot);

/*!
** Return true if a and b rectangle collides.
** \param a A first rectangle
** \param b A second rectangle
** \return True if rectangles overlaps.
*/
bool				bunny_rectangular_collision(const t_bunny_accurate_area		*a,
							    const t_bunny_accurate_area		*b);

/*!
** Return true if dot is on the clip
** \param clip The clipable
** \param dot The dot
** \return True if dot is on clip
*/
bool				bunny_clip_collision_dot(const t_bunny_clipable			*clip,
							 const t_bunny_accurate_position	*dot);

/*!
** Return true if a and b clip collides.
** \param a A first clip
** \param b A second clip
** \return True if clips overlaps.
*/
bool				bunny_clip_collision(const t_bunny_clipable			*a,
						     const t_bunny_clipable			*b);


/*!
** Return true if dot is inside the triangle.
** \param v3 A 3 elements vertex_array
** \param dot The position to test
** \return True if it collides.
*/
bool				bunny_triangle_collision_dot(const t_bunny_vertex_array		*v3,
							     const t_bunny_accurate_position	*dot);

/*!
** Return true if dot is inside the quad.
** \param v4 A 4 elements vertex_array
** \param dot The position to test
** \return True if it collides.
*/
bool				bunny_quad_collision_dot(const t_bunny_vertex_array		*v4,
							 const t_bunny_accurate_position	*dot);

#endif	/*			__LAPIN_COLLIDE_H__	*/
