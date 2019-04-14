// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2019
//
// Lapin library

#define			__LAPIN_H__
#include		"private2/allocator.hpp"
#include		"private2/logs.hpp"
#include		"lapin2/error.h"

t_bunny_allocator	*bunny::DefaultAllocator = NULL;

t_bunny_allocator	*bunny::get_default_allocator(void)
{
  if (!DefaultAllocator)
    if ((DefaultAllocator = bunny::new_allocator(DefaultAllocatorSize)) == NULL)
      Critical(return (NULL), bunny_errno, {"allocator"},
	       "Cannot create default allocator",
	       NULL);
  return (DefaultAllocator);
}

const t_bunny_allocator	*bunny_get_default_allocator(void)
{
  t_bunny_allocator	*alloc;

  Prelog({"allocator"}, "Entering", "?");
  if ((alloc = bunny::get_default_allocator()) == NULL)
    {
      bunny::TryFlushError();
      return (NULL);
    }
  Postlog({"allocator"}, "Leaving", alloc);
  return (alloc);
}

