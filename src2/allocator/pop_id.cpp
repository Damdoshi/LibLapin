// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2019
//
// Lapin library

#define			__LAPIN_H__
#include		"private2/allocator.hpp"

extern size_t		gl_allocator_id_stack;

size_t			bare_allocator_pop_id(void)
{
  if (gl_allocator_id_stack == 1)
    FAILED(return (0), EPERM, {"allocator"}, "Stack is empty.", 0);
  return (--gl_allocator_id_stack);
}

size_t			bunny_allocator_pop_id(void)
{
  size_t		id;

  PROLOG({"allocator"}, "Entering", "?");
  if ((id = bare_allocator_push_id()) == 0)
    LOGOUT(0);
  POSTLOG({"allocator"}, "Leaving", id);
  return (id);
}
