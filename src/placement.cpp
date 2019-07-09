// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include			"lapin_private.h"

t_bunny_position		bunny_position(int			x,
					       int			y)
{
  t_bunny_position		p = {x, y};

  return (p);
}

t_bunny_accurate_position	bunny_accurate_position(double		x,
							double		y)
{
  t_bunny_accurate_position	p = {x, y};

  return (p);
}

t_bunny_area			bunny_area(int				x,
					   int				y,
					   int				w,
					   int				h)
{
  t_bunny_area			area = {x, y, w, h};

  return (area);
}

t_bunny_accurate_area		bunny_accurate_area(double		x,
						    double		y,
						    double		w,
						    double		h)
{
  t_bunny_accurate_area		area = {x, y, w, h};

  return (area);
}

