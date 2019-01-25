// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2019
//
// Lapin library

#define			__LAPIN_H__
#include		"private2/allocator.hpp"

ptrdiff_t		bare_allocator_offset(t_bunny_allocator		*allocator)
{
  return (allocator->data[0] - allocator->first_byte);
}

ptrdiff_t		bunny_allocator_offset(t_bunny_allocator	*allocator)
{
  ptrdiff_t		offset;

  PROLOG({"allocator"}, "Entering", "?", allocator);
  offset = bare_allocator_offset(allocator);
  POSTLOG({"allocator"}, "Leaving", offset, allocator);
  return (offset);
}

