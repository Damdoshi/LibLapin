// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include		"lapin_private.h"

bool			bunny_async_computation_foreach(t_bunny_function	fn,
							void			**da,
							size_t			len)
{
  bool			once = true;
  size_t		i;

  for (i = 0; i < len; ++i)
    if (bunny_async_computation_push(fn, da[i]) == false)
      once = false;
    else
      da[i] = NULL;
  return (once);
}

