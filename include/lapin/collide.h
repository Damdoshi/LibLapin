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

#ifndef					__LAPIN_COLLIDE_H__
# define				__LAPIN_COLLIDE_H__
# if					!defined(__LAPIN_H__)
#  error				You cannot include this file directly.
# endif
# include				"misc.h"


/**
 * @doc
 * @doc-symbol collide
 * @doc-kind module
 * @doc-module collide
 * @doc-order 0
 * @doc-since 0
 * @doc-until latest
 * @doc-level 10
 *
 * @doc-lang en
 * @brief Describes geometric collision shapes and collision tests.
 * @description The collide module provides low-level helpers for simple shapes, and the generic t_bunny_collision union used to describe dots, circles, lines, triangles, rectangles, quads and equation-based shapes.
 * @header lapin/collide.h
 *
 * @doc-lang fr
 * @brief Décrit les formes géométriques de collision et leurs tests.
 * @description Le module collide fournit des aides bas niveau pour les formes simples, ainsi que l'union générique t_bunny_collision utilisée pour décrire des points, cercles, lignes, triangles, rectangles, quadrilatères et formes fondées sur une équation.
 * @header lapin/collide.h
 */

/*!
** Return true if the distance elem-dot is inferior to radius
** \param elem The elem to collide with
** \param dot The dot to collide with
** \param radius The distance between elem and dot that indicates a collision
** \return True if elem->dot < radius
*/
bool					bunny_circle_collision_dot(const t_bunny_accurate_position	*elem,
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


/**
 * @doc
 * @doc-symbol bunny_circle_collision
 * @doc-kind macro
 * @doc-module collide
 * @doc-order 420
 * @doc-since 0
 * @doc-until latest
 * @doc-level 10
 *
 * @doc-lang en
 * @brief Tests whether two circles overlap.
 * @description bunny_circle_collision is a macro wrapper around bunny_circle_collision_dot that adds both radii before testing the distance between the two centers.
 * @param a Center of the first circle.
 * @param r1 Radius of the first circle.
 * @param b Center of the second circle.
 * @param r2 Radius of the second circle.
 * @return-success Returns true if the circles overlap.
 * @return-failure Returns false otherwise.
 * @see bunny_circle_collision_dot
 *
 * @doc-lang fr
 * @brief Teste si deux cercles se recouvrent.
 * @description bunny_circle_collision est une macro autour de bunny_circle_collision_dot qui additionne les deux rayons avant de tester la distance entre les deux centres.
 * @param a Centre du premier cercle.
 * @param r1 Rayon du premier cercle.
 * @param b Centre du second cercle.
 * @param r2 Rayon du second cercle.
 * @return-success Renvoie true si les cercles se recouvrent.
 * @return-failure Renvoie false sinon.
 * @see bunny_circle_collision_dot
 */
# define				bunny_circle_collision(a, r1, b, r2)	\
  bunny_circle_collision_dot(a, b, r1 + r2)

/*!
** Return true if dot is inside area.
** \param area The zone in which it collides
** \param dot The dot that may collide
** \return True if it collides
*/
bool					bunny_rectangular_collision_dot(const t_bunny_accurate_area	*elem,
									const t_bunny_accurate_position	*dot);

/*!
** Return true if a and b rectangle collides.
** \param a A first rectangle
** \param b A second rectangle
** \return True if rectangles overlaps.
*/
bool					bunny_rectangular_collision(const t_bunny_accurate_area		*a,
								    const t_bunny_accurate_area		*b);

/*!
** Return true if dot is on the clip
** \param clip The clipable
** \param dot The dot
** \return True if dot is on clip
*/
bool					bunny_clip_collision_dot(const t_bunny_clipable			*clip,
								 const t_bunny_accurate_position	*dot);

/*!
** Return true if a and b clip collides.
** \param a A first clip
** \param b A second clip
** \return True if clips overlaps.
*/
bool					bunny_clip_collision(const t_bunny_clipable			*a,
							     const t_bunny_clipable			*b);


/*!
** Return true if dot is inside the triangle.
** \param v3 A 3 elements vertex_array
** \param dot The position to test
** \return True if it collides.
*/
bool					bunny_triangle_collision_dot(const t_bunny_vertex_array		*v3,
								     const t_bunny_accurate_position	*dot);

/*!
** Return true if dot is inside the quad.
** \param v4 A 4 elements vertex_array
** \param dot The position to test
** \return True if it collides.
*/
bool					bunny_quad_collision_dot(const t_bunny_vertex_array		*v4,
								 const t_bunny_accurate_position	*dot);

/*!
** This enumeration is used as recognition token for t_bunny_collision.
** Each values, except for LAST_COLLISION_TYPE may be used and the union
** filled accordingly.
*/


/**
 * @doc
 * @doc-symbol t_bunny_collision_type
 * @doc-kind enum
 * @doc-module collide
 * @doc-order 50
 * @doc-since 0
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Selects which member of t_bunny_collision is active.
 * @description t_bunny_collision_type is the discriminator shared by all collision structures. The first field of every t_bunny_*_collision structure is a t_bunny_collision_type so a pointer to any concrete collision may also be interpreted through t_bunny_collision.
 * @enum BCT_DOT A single point.
 * @enum BCT_CIRCLE A circle described by its center and radius.
 * @enum BCT_LINE A segment described by two positions.
 * @enum BCT_TRIANGLE A triangle described by three positions.
 * @enum BCT_RECTANGLE An axis-aligned rectangle described by a position and a size.
 * @enum BCT_QUAD A quadrilateral described by four positions.
 * @enum BCT_EQUATION A collision area driven by a quadratic equation.
 * @enum LAST_COLLISION_TYPE Sentinel value. Do not use it as a shape type.
 * @see t_bunny_collision
 *
 * @doc-lang fr
 * @brief Sélectionne le membre actif de t_bunny_collision.
 * @description t_bunny_collision_type est le discriminateur partagé par toutes les structures de collision. Le premier champ de chaque structure t_bunny_*_collision est un t_bunny_collision_type, ce qui permet aussi d'interpréter un pointeur vers une collision concrète via t_bunny_collision.
 * @enum BCT_DOT Un point unique.
 * @enum BCT_CIRCLE Un cercle décrit par son centre et son rayon.
 * @enum BCT_LINE Un segment décrit par deux positions.
 * @enum BCT_TRIANGLE Un triangle décrit par trois positions.
 * @enum BCT_RECTANGLE Un rectangle aligné sur les axes, décrit par une position et une taille.
 * @enum BCT_QUAD Un quadrilatère décrit par quatre positions.
 * @enum BCT_EQUATION Une zone de collision pilotée par une équation quadratique.
 * @enum LAST_COLLISION_TYPE Valeur sentinelle. Ne l'utilisez pas comme type de forme.
 * @see t_bunny_collision
 */
typedef enum				e_bunny_collision_type
  {
    BCT_DOT,
    BCT_CIRCLE,
    BCT_LINE,
    BCT_TRIANGLE,
    BCT_RECTANGLE,
    BCT_QUAD,
    BCT_EQUATION,
    LAST_COLLISION_TYPE
  }					t_bunny_collision_type;

/*!
** The t_bunny_dot_collision represents a single dot in space.
** It has no size, only coordinates and may be used to check
** if it has the same coordinates as an other dot or if it is
** inside an area of any shape.
** Its type field must be set to BCT_DOT.
** Its coord attribute is its coordinate.
*/


/**
 * @doc
 * @doc-symbol t_bunny_dot_collision
 * @doc-kind struct
 * @doc-module collide
 * @doc-order 120
 * @doc-since 0
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Represents a single point collision shape.
 * @description Set the type field to BCT_DOT before using this structure through t_bunny_collision.
 * @field type Shape discriminator. Must be BCT_DOT.
 * @field name Optional user name associated with the shape.
 * @field coord Point coordinates.
 * @see t_bunny_collision, t_bunny_collision_type
 *
 * @doc-lang fr
 * @brief Représente une forme de collision réduite à un point.
 * @description Définissez le champ type à BCT_DOT avant d'utiliser cette structure via t_bunny_collision.
 * @field type Discriminateur de forme. Doit valoir BCT_DOT.
 * @field name Nom utilisateur optionnel associé à la forme.
 * @field coord Coordonnées du point.
 * @see t_bunny_collision, t_bunny_collision_type
 */
typedef struct				s_bunny_dot_collision
{
  t_bunny_collision_type		type;
  const char				*name;
  t_bunny_accurate_position		coord;
}					t_bunny_dot_collision;

/*!
** The t_bunny_circle_collision represents a circle in space.
** It has a radius and coordinates of its center.
** Its type field must be set to BCT_CIRCLE.
** Its coord attribute is the coordinate of the center of the circle.
** If its radius field is between -1 and 1, it is considered as a dot.
*/


/**
 * @doc
 * @doc-symbol t_bunny_circle_collision
 * @doc-kind struct
 * @doc-module collide
 * @doc-order 140
 * @doc-since 0
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Represents a circle collision shape.
 * @description Set the type field to BCT_CIRCLE before using this structure through t_bunny_collision.
 * @field type Shape discriminator. Must be BCT_CIRCLE.
 * @field name Optional user name associated with the shape.
 * @field coord Circle center.
 * @field radius Circle radius. Values close to zero behave like a dot.
 * @see t_bunny_collision, t_bunny_collision_type
 *
 * @doc-lang fr
 * @brief Représente une forme de collision circulaire.
 * @description Définissez le champ type à BCT_CIRCLE avant d'utiliser cette structure via t_bunny_collision.
 * @field type Discriminateur de forme. Doit valoir BCT_CIRCLE.
 * @field name Nom utilisateur optionnel associé à la forme.
 * @field coord Centre du cercle.
 * @field radius Rayon du cercle. Les valeurs proches de zéro se comportent comme un point.
 * @see t_bunny_collision, t_bunny_collision_type
 */
typedef struct				s_bunny_circle_collision
{
  t_bunny_collision_type		type;
  const char				*name;
  t_bunny_accurate_position		coord;
  double				radius;
}					t_bunny_circle_collision;

/*!
** The t_bunny_line_collision represents two dots with a specific
** amount of points inbetween.
** Its type field must be set to BCT_LINE.
** Its coord attribute is an array with coordinates of each side of the line.
** Its intermediate_points attribute must be greater or equal to 0.
*/


/**
 * @doc
 * @doc-symbol t_bunny_line_collision
 * @doc-kind struct
 * @doc-module collide
 * @doc-order 160
 * @doc-since 0
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Represents a segment collision shape.
 * @description Set the type field to BCT_LINE before using this structure through t_bunny_collision.
 * @field type Shape discriminator. Must be BCT_LINE.
 * @field name Optional user name associated with the shape.
 * @field coord Two extremities of the segment.
 * @field intermediate_points Number of sampled intermediate points used by generic collision tests.
 * @see t_bunny_collision, t_bunny_collision_type
 *
 * @doc-lang fr
 * @brief Représente une forme de collision en segment.
 * @description Définissez le champ type à BCT_LINE avant d'utiliser cette structure via t_bunny_collision.
 * @field type Discriminateur de forme. Doit valoir BCT_LINE.
 * @field name Nom utilisateur optionnel associé à la forme.
 * @field coord Deux extrémités du segment.
 * @field intermediate_points Nombre de points intermédiaires échantillonnés par les tests génériques.
 * @see t_bunny_collision, t_bunny_collision_type
 */
typedef struct				s_bunny_line_collision
{
  t_bunny_collision_type		type;
  const char				*name;
  t_bunny_accurate_position		coord[2];
  double				intermediate_points;
}					t_bunny_line_collision;

/*!
** The t_bunny_triangle_collision represents a triangle.
** Its type field must be set to BCT_TRIANGLE.
** Its coord attribute is an array with coordinates of each extremities.
*/


/**
 * @doc
 * @doc-symbol t_bunny_triangle_collision
 * @doc-kind struct
 * @doc-module collide
 * @doc-order 180
 * @doc-since 0
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Represents a triangle collision shape.
 * @description Set the type field to BCT_TRIANGLE before using this structure through t_bunny_collision.
 * @field type Shape discriminator. Must be BCT_TRIANGLE.
 * @field name Optional user name associated with the shape.
 * @field coord Three vertices of the triangle.
 * @see t_bunny_collision, t_bunny_collision_type
 *
 * @doc-lang fr
 * @brief Représente une forme de collision triangulaire.
 * @description Définissez le champ type à BCT_TRIANGLE avant d'utiliser cette structure via t_bunny_collision.
 * @field type Discriminateur de forme. Doit valoir BCT_TRIANGLE.
 * @field name Nom utilisateur optionnel associé à la forme.
 * @field coord Trois sommets du triangle.
 * @see t_bunny_collision, t_bunny_collision_type
 */
typedef struct				s_bunny_triangle_collision
{
  t_bunny_collision_type		type;
  const char				*name;
  t_bunny_accurate_position		coord[3];
}					t_bunny_triangle_collision;


/*!
** The t_bunny_rectangular_collision represents a rectangle.
** Its type field must be set to BCT_RECTANGLE.
** Its coord attribute is an array with the position of the top left corner
** and then the size of the rectangle.
*/


/**
 * @doc
 * @doc-symbol t_bunny_rectangular_collision
 * @doc-kind struct
 * @doc-module collide
 * @doc-order 200
 * @doc-since 0
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Represents an axis-aligned rectangular collision shape.
 * @description Set the type field to BCT_RECTANGLE before using this structure through t_bunny_collision.
 * @field type Shape discriminator. Must be BCT_RECTANGLE.
 * @field name Optional user name associated with the shape.
 * @field coord coord[0] is the top-left position and coord[1] is the size.
 * @see t_bunny_collision, t_bunny_collision_type
 *
 * @doc-lang fr
 * @brief Représente une forme de collision rectangulaire alignée sur les axes.
 * @description Définissez le champ type à BCT_RECTANGLE avant d'utiliser cette structure via t_bunny_collision.
 * @field type Discriminateur de forme. Doit valoir BCT_RECTANGLE.
 * @field name Nom utilisateur optionnel associé à la forme.
 * @field coord coord[0] est la position haut-gauche et coord[1] est la taille.
 * @see t_bunny_collision, t_bunny_collision_type
 */
typedef struct				s_bunny_rectangular_collision
{
  t_bunny_collision_type		type;
  const char				*name;
  t_bunny_accurate_position		coord[2];
}					t_bunny_rectangular_collision;

/*!
** The t_bunny_quad_collision represents a quad.
** Its type field must be set to BCT_QUAD.
** Its coord attribute is an array of coordinates for the quad.
*/


/**
 * @doc
 * @doc-symbol t_bunny_quad_collision
 * @doc-kind struct
 * @doc-module collide
 * @doc-order 220
 * @doc-since 0
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Represents a quadrilateral collision shape.
 * @description Set the type field to BCT_QUAD before using this structure through t_bunny_collision.
 * @field type Shape discriminator. Must be BCT_QUAD.
 * @field name Optional user name associated with the shape.
 * @field coord Four vertices of the quadrilateral.
 * @see t_bunny_collision, t_bunny_collision_type
 *
 * @doc-lang fr
 * @brief Représente une forme de collision quadrilatère.
 * @description Définissez le champ type à BCT_QUAD avant d'utiliser cette structure via t_bunny_collision.
 * @field type Discriminateur de forme. Doit valoir BCT_QUAD.
 * @field name Nom utilisateur optionnel associé à la forme.
 * @field coord Quatre sommets du quadrilatère.
 * @see t_bunny_collision, t_bunny_collision_type
 */
typedef struct				s_bunny_quad_collision
{
  t_bunny_collision_type		type;
  const char				*name;
  t_bunny_accurate_position		coord[4];
}					t_bunny_quad_collision;

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


/**
 * @doc
 * @doc-symbol t_bunny_equation_collision
 * @doc-kind struct
 * @doc-module collide
 * @doc-order 240
 * @doc-since 0
 * @doc-until latest
 * @doc-level 40
 *
 * @doc-lang en
 * @brief Represents a collision shape based on a quadratic equation.
 * @description t_bunny_equation_collision describes a rectangular area whose limit is computed from a second degree equation. It can be used to approximate sloped or curved terrain tile by tile.
 * @field type Shape discriminator. Must be BCT_EQUATION.
 * @field name Optional user name associated with the shape.
 * @field coord coord[0] is the area position and coord[1] is its size.
 * @field amplitude X and Y amplitude applied to the equation space.
 * @field a Coefficient a in the equation a*x*x + b*x + c.
 * @field b Coefficient b in the equation a*x*x + b*x + c.
 * @field c Coefficient c in the equation a*x*x + b*x + c.
 * @field origin_at_center If true, the equation origin is the center of the area.
 * @field flipx Mirrors the equation on X when the origin is not centered.
 * @field flipy Mirrors the equation on Y when the origin is not centered.
 * @see bunny_collision_equation_dot, t_bunny_collision
 *
 * @doc-lang fr
 * @brief Représente une forme de collision fondée sur une équation quadratique.
 * @description t_bunny_equation_collision décrit une zone rectangulaire dont la limite est calculée à partir d'une équation du second degré. Elle peut servir à approximer des sols inclinés ou courbes, tuile par tuile.
 * @field type Discriminateur de forme. Doit valoir BCT_EQUATION.
 * @field name Nom utilisateur optionnel associé à la forme.
 * @field coord coord[0] est la position de la zone et coord[1] sa taille.
 * @field amplitude Amplitude X et Y appliquée à l'espace de l'équation.
 * @field a Coefficient a dans l'équation a*x*x + b*x + c.
 * @field b Coefficient b dans l'équation a*x*x + b*x + c.
 * @field c Coefficient c dans l'équation a*x*x + b*x + c.
 * @field origin_at_center Si true, l'origine de l'équation est le centre de la zone.
 * @field flipx Miroir de l'équation en X lorsque l'origine n'est pas centrée.
 * @field flipy Miroir de l'équation en Y lorsque l'origine n'est pas centrée.
 * @see bunny_collision_equation_dot, t_bunny_collision
 */
typedef struct				s_bunny_equation_collision
{
  t_bunny_collision_type		type;
  const char				*name;
  t_bunny_accurate_position		coord[2];
  t_bunny_accurate_position		amplitude;
  double				a;
  double				b;
  double				c;
  bool					origin_at_center;
  bool					flipx;
  bool					flipy;
}					t_bunny_equation_collision;



/**
 * @doc
 * @doc-symbol t_bunny_collide_point
 * @doc-kind struct
 * @doc-module collide
 * @doc-order 290
 * @doc-since 0
 * @doc-until latest
 * @doc-level 40
 *
 * @doc-lang en
 * @brief Describes the contact point returned by equation collision helpers.
 * @field radian Inclination of the equation at the returned position.
 * @field position Position of the contact point.
 * @see bunny_collision_equation_dot
 *
 * @doc-lang fr
 * @brief Décrit le point de contact renvoyé par les aides de collision par équation.
 * @field radian Inclinaison de l'équation à la position renvoyée.
 * @field position Position du point de contact.
 * @see bunny_collision_equation_dot
 */
typedef struct				s_bunny_collide_point
{
  double				radian;
  t_bunny_accurate_position		position;
}					t_bunny_collide_point;

/*!
** Test if the dot is colliding with the equation: colliding means that for the
** position on X, its position on Y is greater than the equation value for X.
** \param a The equation that will be used to test the collision.
** \param b The dot that will be used to test the collision.
** \return A pair of radian and position that are the spot where to collision
** occurs (The X/Y value of the equation for the sent X) and the inclinaison
** of the position.
*/
t_bunny_collide_point			bunny_collision_equation_dot(const t_bunny_equation_collision	*a,
								     const t_bunny_dot_collision	*b);




/**
 * @doc
 * @doc-symbol t_bunny_collision_identity
 * @doc-kind struct
 * @doc-module collide
 * @doc-order 95
 * @doc-since 0
 * @doc-until latest
 * @doc-level 50
 *
 * @doc-lang en
 * @brief Common prefix shared by named collision shapes.
 * @description t_bunny_collision_identity exposes the common type and name prefix of every named collision structure. It is mostly useful when inspecting a t_bunny_collision without selecting its full concrete shape.
 * @field type Shape discriminator.
 * @field name Optional user name associated with the shape.
 * @see t_bunny_collision
 *
 * @doc-lang fr
 * @brief Préfixe commun partagé par les formes de collision nommées.
 * @description t_bunny_collision_identity expose le préfixe commun type et name de chaque structure de collision nommée. Il sert surtout lorsqu'on inspecte une t_bunny_collision sans sélectionner sa forme concrète complète.
 * @field type Discriminateur de forme.
 * @field name Nom utilisateur optionnel associé à la forme.
 * @see t_bunny_collision
 */
typedef struct			s_bunny_collision_identity
{
  t_bunny_collision_type		type;
  const char				*name;
}					t_bunny_collision_identity;

/*!
** The u_bunny_collision union contains every t_bunny_*_collision
** structure as available types. Its first field is the common part: the type
** of the collision.
** Depending of the type you will set in this field, you may use one of the other
** field accordingly.
** For example, if you set type to BCT_RECTANGLE, you should use the rectangular
** field.
*/


/**
 * @doc
 * @doc-symbol t_bunny_collision
 * @doc-kind union
 * @doc-module collide
 * @doc-order 100
 * @doc-since 0
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Stores any collision shape handled by the generic collision API.
 * @description Set the type field first, then fill the matching member. Generic functions such as bunny_collide and bunny_collision read type to select the right algorithm.
 * @field type Shortcut to the active collision type.
 * @field identity Common type/name prefix.
 * @field dot Dot shape storage.
 * @field circle Circle shape storage.
 * @field line Line shape storage.
 * @field triangle Triangle shape storage.
 * @field rectangular Rectangle shape storage.
 * @field quad Quad shape storage.
 * @field equation Equation shape storage.
 * @see t_bunny_collision_type, bunny_collide
 *
 * @doc-lang fr
 * @brief Stocke n'importe quelle forme de collision gérée par l'API générique.
 * @description Définissez d'abord le champ type, puis remplissez le membre correspondant. Les fonctions génériques comme bunny_collide et bunny_collision lisent type pour choisir le bon algorithme.
 * @field type Raccourci vers le type de collision actif.
 * @field identity Préfixe commun type/nom.
 * @field dot Stockage d'un point.
 * @field circle Stockage d'un cercle.
 * @field line Stockage d'une ligne.
 * @field triangle Stockage d'un triangle.
 * @field rectangular Stockage d'un rectangle.
 * @field quad Stockage d'un quadrilatère.
 * @field equation Stockage d'une équation.
 * @see t_bunny_collision_type, bunny_collide
 */
typedef union				u_bunny_collision
{
  t_bunny_collision_type		type;
  t_bunny_collision_identity		identity;
  t_bunny_dot_collision			dot;
  t_bunny_circle_collision		circle;
  t_bunny_line_collision		line;
  t_bunny_triangle_collision		triangle;
  t_bunny_rectangular_collision		rectangular;
  t_bunny_quad_collision		quad;
  t_bunny_equation_collision		equation;
}					t_bunny_collision;

/*!
** Return if the two shapes collides, whatever they are.
** \param a A shape to test the collision with
** \param a A shape to test the collision with
** \return True if shapes collides
*/
bool					bunny_collide(const t_bunny_collision				*a,
						      const t_bunny_collision				*b);

bool					bunny_collision(const t_bunny_collision				*a,
							const t_bunny_accurate_position			*posa,
							double						rota,

							const t_bunny_collision				*b,
							const t_bunny_accurate_position			*posb,
							double						rotb);

int					bunny_collision_nbr(const t_bunny_collision			*a,
							    size_t					lena,
							    const t_bunny_accurate_position		*posa,
							    double					rota,
							    const t_bunny_collision			*b,
							    size_t					lenb,
							    const t_bunny_accurate_position		*posb,
							    double					rotb,
							    t_bunny_string_couple			*couple,
							    size_t					couple_len);

void					bunny_move_collision(t_bunny_collision				*a,
							     t_bunny_accurate_position			move);

void					bunny_turn_collision(t_bunny_collision				*a,
							     double					moment);

/*!
** Draw the collision shape on the sent buffer.
** \param tar The surface where to draw the collision
** \param x The collision to draw
** \param col The color that will be used to draw the collision
*/
void					bunny_draw_collision_shape(t_bunny_buffer			*tar,
								   const t_bunny_collision		*x,
								   unsigned int				col);

void					bunny_set_collision_shape(t_bunny_buffer			*tar,
								  const t_bunny_collision		*x,
								  t_bunny_position			pos,
								  unsigned int				col);

bool					bunny_pixel_collision(t_bunny_clipable				*pic,
							      const t_bunny_position			*pos,
							      double					amgn);



/**
 * @doc
 * @doc-symbol t_bunny_collision_shapes
 * @doc-kind struct
 * @doc-module collide
 * @doc-order 620
 * @doc-since 0
 * @doc-until latest
 * @doc-level 40
 *
 * @doc-lang en
 * @brief Stores a dynamically loaded array of collision shapes.
 * @field collisions Array of collision shapes.
 * @field nbr_collision Number of entries in collisions.
 * @see bunny_collision_configuration
 *
 * @doc-lang fr
 * @brief Stocke un tableau de formes de collision chargé dynamiquement.
 * @field collisions Tableau de formes de collision.
 * @field nbr_collision Nombre d'entrées dans collisions.
 * @see bunny_collision_configuration
 */
typedef struct				s_bunny_collision_shapes
{
  t_bunny_collision			*collisions;
  size_t				nbr_collision;
}					t_bunny_collision_shapes;

t_bunny_decision			bunny_collision_configuration(const char			*field,
								      t_bunny_collision_shapes		*shapes,
								      t_bunny_configuration		*cnf);

#endif	/*				__LAPIN_COLLIDE_H__						*/
