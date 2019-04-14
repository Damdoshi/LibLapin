// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2019
//
// Lapin library

#define			__LAPIN_H__
#include		"private2/logs.hpp"
#include		"private2/allocator.hpp"

size_t			gl_allocator_id_stack = 1;

size_t			bunny::allocator_get_id(void)
{
  return (gl_allocator_id_stack);
}

size_t			bunny_allocator_get_id(void)
{
  size_t		id;

  Prelog({"allocator"}, "Entering", "?");
  id = bunny::allocator_get_id();
  Postlog({"allocator"}, "Leaving", id);
  return (id);
}

