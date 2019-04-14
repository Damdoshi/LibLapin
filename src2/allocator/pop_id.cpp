// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2019
//
// Lapin library

#define			__LAPIN_H__
#include		"private2/allocator.hpp"
#include		"private2/logs.hpp"

extern size_t		gl_allocator_id_stack;

size_t			bunny::allocator_pop_id(void)
{
  if (gl_allocator_id_stack == 1)
    Failure(return (0), EPERM, {"allocator"}, "Stack is empty.", 0);
  return (--gl_allocator_id_stack);
}

size_t			bunny_allocator_pop_id(void)
{
  size_t		id;

  Prelog({"allocator"}, "Entering", "?");
  if ((id = bunny::allocator_push_id()) == 0)
    {
      ::bunny::TryFlushError();
      return (0);
    }
  Postlog({"allocator"}, "Leaving", id);
  return (id);
}
