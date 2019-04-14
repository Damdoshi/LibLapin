// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2019
//
// Lapin library

#include		<stdlib.h>
#define			__LAPIN_H__
#include		"private2/allocator.hpp"
#include		"private2/logs.hpp"

void			bunny::delete_allocator(t_bunny_allocator	*allocator)
{
  free(allocator);
}

void			bunny_delete_allocator(t_bunny_allocator	*allocator)
{
  Prelog({"allocator"}, "Entering", "[]", allocator);
  bunny::delete_allocator(allocator);
  Postlog({"allocator"}, "Leaving", "[]", allocator);
}

