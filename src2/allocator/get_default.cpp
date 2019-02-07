// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2019
//
// Lapin library

#define			__LAPIN_H__
#include		"private2/allocator.hpp"

t_bunny_allocator	*gl_default_allocator = NULL;

t_bunny_allocator	*bunny::get_default_allocator(void)
{
  if (gl_bunny_default_allocator)
    if (!(gl_bunny_default_allocator = bare_new_allocator(gl_bunny_default_allocator_size)))
      CRITICAL(return (NULL), bunny_errno, {"allocator"}, "", NULL);
  return (gl_bunny_default_allocator);
}

const t_bunny_allocator	*bunny_get_default_allocator(void)
{
  t_bunny_allocator	*alloc;

  PROLOG({"allocator"}, "Entering", "?");
  if ((alloc = bunny::get_default_allocator()) == NULL)
    LOGOUT(NULL);
  POSTLOG({"allocator"}, "Leaving", alloc);
  return (alloc);
}

