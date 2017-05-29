// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

sf::Color		bunny_color_to_sf_color(unsigned int	i)
{
  t_bunny_color		col;

  col.full = i;
  return (sf::Color(col.argb[RED_CMP], col.argb[GREEN_CMP], col.argb[BLUE_CMP], col.argb[ALPHA_CMP]));
}

unsigned int		sf_color_to_bunny_color(const sf::Color	&clr)
{
  t_bunny_color		col;

  col.argb[RED_CMP] = clr.r;
  col.argb[GREEN_CMP] = clr.g;
  col.argb[BLUE_CMP] = clr.b;
  col.argb[ALPHA_CMP] = clr.a;
  return (col.full);
}

