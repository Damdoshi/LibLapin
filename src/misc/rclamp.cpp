// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin.h"

double			bunny_rclamp(double		val,
				     double		min,
				     double		max)
{
  if (val < min)
    return (max);
  if (val > max)
    return (min);
  return (val);
}
