// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2019
//
// Lapin library

#define			__LAPIN_H__
#include		"private2/allocator.hpp"
#include		"private2/logs.hpp"

extern size_t		gl_allocator_id_stack;

size_t			bunny::allocator_push_id(void)
{
  return (++gl_allocator_id_stack);
}

size_t			bunny_allocator_push_id(void)
{
  size_t		id;

  Prelog({"allocator"}, "Entering", "?");
  id = bunny::allocator_push_id();
  Postlog({"allocator"}, "Leaving", id);
  return (id);
}
