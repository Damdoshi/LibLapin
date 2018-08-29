// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<time.h>
#include		"lapin_private.h"

t_bunny_time		bunny_delta_time(t_bunny_time		bef,
					 t_bunny_time		now)
{
  return (now - bef);
}


