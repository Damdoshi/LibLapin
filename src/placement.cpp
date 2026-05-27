// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include			"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_position
 * @doc-kind function
 * @doc-module placement
 * @doc-order 400
 * @doc-since 12
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Builds an integer position value.
 * @param x The X coordinate.
 * @param y The Y coordinate.
 * @return-case success A t_bunny_position initialized with x and y.
 * @see t_bunny_position, t_bunny_area
 *
 * @doc-lang fr
 * @brief Construit une valeur de position entière.
 * @param x La coordonnée X.
 * @param y La coordonnée Y.
 * @return-case success Un t_bunny_position initialisé avec x et y.
 * @see t_bunny_position, t_bunny_area
 */

t_bunny_position		bunny_position(int			x,
					       int			y)
{
  t_bunny_position		p = {x, y};

  return (p);
}


/**
 * @doc
 * @doc-symbol bunny_accurate_position
 * @doc-kind function
 * @doc-module placement
 * @doc-order 430
 * @doc-since 12
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Builds a floating-point position value.
 * @param x The X coordinate.
 * @param y The Y coordinate.
 * @return-case success A t_bunny_accurate_position initialized with x and y.
 * @see t_bunny_position, t_bunny_area
 *
 * @doc-lang fr
 * @brief Construit une valeur de position flottante.
 * @param x La coordonnée X.
 * @param y La coordonnée Y.
 * @return-case success Un t_bunny_accurate_position initialisé avec x et y.
 * @see t_bunny_position, t_bunny_area
 */

t_bunny_accurate_position	bunny_accurate_position(double		x,
							double		y)
{
  t_bunny_accurate_position	p = {x, y};

  return (p);
}


/**
 * @doc
 * @doc-symbol bunny_area
 * @doc-kind function
 * @doc-module placement
 * @doc-order 460
 * @doc-since 12
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Builds an integer area value.
 * @param x The X coordinate of the top-left corner.
 * @param y The Y coordinate of the top-left corner.
 * @param w The width.
 * @param h The height.
 * @return-case success A t_bunny_area initialized with x, y, w and h.
 * @see t_bunny_position, t_bunny_area
 *
 * @doc-lang fr
 * @brief Construit une valeur de zone entière.
 * @param x La coordonnée X du coin supérieur gauche.
 * @param y La coordonnée Y du coin supérieur gauche.
 * @param w La largeur.
 * @param h La hauteur.
 * @return-case success Un t_bunny_area initialisé avec x, y, w et h.
 * @see t_bunny_position, t_bunny_area
 */

t_bunny_area			bunny_area(int				x,
					   int				y,
					   int				w,
					   int				h)
{
  t_bunny_area			area = {x, y, w, h};

  return (area);
}


/**
 * @doc
 * @doc-symbol bunny_accurate_area
 * @doc-kind function
 * @doc-module placement
 * @doc-order 480
 * @doc-since 12
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Builds a floating-point area value.
 * @param x The X coordinate of the top-left corner.
 * @param y The Y coordinate of the top-left corner.
 * @param w The width.
 * @param h The height.
 * @return-case success A t_bunny_accurate_area initialized with x, y, w and h.
 * @see t_bunny_position, t_bunny_area
 *
 * @doc-lang fr
 * @brief Construit une valeur de zone flottante.
 * @param x La coordonnée X du coin supérieur gauche.
 * @param y La coordonnée Y du coin supérieur gauche.
 * @param w La largeur.
 * @param h La hauteur.
 * @return-case success Un t_bunny_accurate_area initialisé avec x, y, w et h.
 * @see t_bunny_position, t_bunny_area
 */

t_bunny_accurate_area		bunny_accurate_area(double		x,
						    double		y,
						    double		w,
						    double		h)
{
  t_bunny_accurate_area		area = {x, y, w, h};

  return (area);
}

