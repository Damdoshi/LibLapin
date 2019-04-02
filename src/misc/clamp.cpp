// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin.h"

double			bunny_clamp(double		val,
				    double		min,
				    double		max)
{
  if (val < min)
    return (min);
  if (val > max)
    return (max);
  return (val);
}
