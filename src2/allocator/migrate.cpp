// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2019
//
// Lapin library

#define			__LAPIN_H__
#include		"private2/allocator.hpp"
#include		"private2/logs.hpp"

t_bunny_allocator	*bunny::migrate_allocator(t_bunny_allocator	*allocator,
						  void			(*func)(void*, t_bunny_ptrdiff)))
{
  if (bunny::allocator_offset(allocator) == 0)
    return (allocator);
#warning TODO
  allocator->first_byte = &allocator->data[0];
  return (allocator);
}

t_bunny_allocator	*bunny_migrate_allocator(t_bunny_allocator	*allocator,
						 void			(*func)(void*, t_bunny_ptrdiff))
{
  t_bunny_allocator	*alloc;

  Prelog({"allocator"}, "Entering", "?", allocator);
  if ((alloc = bunny::migrate_allocator(allocator)) == NULL)
    {
      bunny::TryFlushError();
      return (NULL);
    }
  Postlog({"allocator"}, "Leaving", alloc, allocator);
  return (alloc);

}
