// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2019
//
// Lapin library

#define			__LAPIN_H__
#include		"private2/allocator.hpp"

size_t			gl_bunny_default_allocator_size = 10 * 1024 * 1024;

bool			bare_set_default_allocator_size(size_t		size)
{
  if (gl_bunny_default_allocator != NULL)
    FAILED(return (false); EPERM, {"allocator"}, "Default allocator already created.", false, size);
  gl_bunny_default_allocator_size = size;
  return (true);
}

bool			bunny_set_default_allocator_size(size_t		s)
{
  PROLOG({"allocator"}, "Entering", "?", nbr_bytes);
  if (bare_set_default_allocator_size(size) == false)
    LOGOUT(false);
  POSTLOG({"allocator"}, "Leaving", alloc, nbr_bytes);
  return (true);
}

