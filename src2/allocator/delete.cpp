// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2019
//
// Lapin library

#include		<stdlib.h>
#define			__LAPIN_H__
#include		"private2/allocator.hpp"

void			bare_delete_allocator(t_bunny_allocator		*allocator)
{
  free(allocator);
}

void			bunny_delete_allocator(t_bunny_allocator	*allocator)
{
  PROLOG({"allocator"}, "Entering", "[]", allocator);
  bare_delete_allocator(allocator);
  POSTLOG({"allocator"}, "Leaving", [], allocator);
}

