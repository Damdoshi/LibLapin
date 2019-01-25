// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2019
//
// Lapin library

#define			__LAPIN_H__
#include		"private2/allocator.hpp"

extern size_t		gl_allocator_id_stack;

size_t			bare_allocator_push_id(void)
{
  return (++gl_allocator_id_stack);
}

size_t			bunny_allocator_push_id(void)
{
  size_t		id;

  PROLOG({"allocator"}, "Entering", "?");
  id = bare_allocator_push_id();
  POSTLOG({"allocator"}, "Leaving", id);
  return (id);
}
