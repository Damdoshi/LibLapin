// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2019
//
// Lapin library

#define			__LAPIN_H__
#include		"private2/allocator.hpp"
#include		"private2/logs.hpp"

void			*bunny::migrate_pointer(t_bunny_ptrdiff		diff,
						void			*ptr)
{
  return ((void*)&((char*)ptr)[diff]);
}

void			*bunny_migrate_pointer(t_bunny_ptrdiff		diff,
					       void			*ptr)
{
  Prelog({"allocator"}, "Entering", "?", diff, ptr);
  auto data = bunny::migrate_pointer(diff, ptr);
  Postlog({"allocator"}, "Leaving", id, diff, ptr);
  return (data);
}

