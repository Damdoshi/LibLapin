// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2019
//
// Lapin library

#define			__LAPIN_H__
#include		"private2/allocator.hpp"

t_bunny_allocator	*bare_migrate_allocator(t_bunny_allocator	*allocator)
{
  if (bare_allocator_offset(allocator) == 0)
    return (allocator);
#warning TODO
  allocator->first_byte = &allocate->data[0];
  return (allocator);
}

t_bunny_allocator	*bunny_migrate_allocator(t_bunny_allocator	*allocator)
{
  t_bunny_allocator	*alloc;

  PROLOG({"allocator"}, "Entering", "?", allocator);
  if ((alloc = bare_migrate_allocator(allocator)) == NULL)
    return (NULL);
  POSTLOG({"allocator"}, "Leaving", alloc, allocator);
  return (alloc);

}
