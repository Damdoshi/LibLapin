// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2019
//
// Lapin library

#define			__LAPIN_H__
#include		"private2/allocator.hpp"
#include		"private2/logs.hpp"

t_bunny_ptrdiff		bunny::allocator_offset(t_bunny_allocator	*allocator)
{
  return ((t_bunny_ptrdiff)&allocator->data[0] - (t_bunny_ptrdiff)allocator->first_byte);
}

t_bunny_ptrdiff		bunny_allocator_offset(t_bunny_allocator	*allocator)
{
  ptrdiff_t		offset;

  Prelog({"allocator"}, "Entering", "?", allocator);
  offset = bunny::allocator_offset(allocator);
  Postlog({"allocator"}, "Leaving", offset, allocator);
  return (offset);
}

