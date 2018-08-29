// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

bool			bunny_reach(double		*value,
				    double		limit,
				    double		step)
{
  if (fabs(*value - limit) < step)
    {
      *value = limit;
      return (true);
    }

  if (*value < limit)
    {
      if ((*value += step) > limit)
	{
	  *value = limit;
	  return (true);
	}
      return (false);
    }

  if (*value > limit)
    {
      if ((*value -= step) < limit)
	{
	  *value = limit;
	  return (true);
	}
      return (false);
    }

  return (false);
}

