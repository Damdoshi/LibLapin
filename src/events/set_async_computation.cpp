// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

void			bunny_set_async_computation_response(t_bunny_async_computation_response func)
{
  gl_callback.async_computation_response = func;
}

