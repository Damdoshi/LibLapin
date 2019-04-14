// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2019
//
// Lapin library

#define			__LAPIN_H__
#include		"private2/allocator.hpp"
#include		"private2/logs.hpp"
#include		"lapin2/error.h"

size_t			bunny::DefaultAllocatorSize = 10 * 1024 * 1024;

size_t			bunny::get_default_allocator_size(void)
{
  return (DefaultAllocatorSize);
}

size_t			bunny_get_default_allocator_size(void)
{
  Prelog({"allocator"}, "Entering", "?");
  auto data = bunny::get_default_allocator_size();
  Postlog({"allocator"}, "Leaving", data);
  return (data);
}

//

bool			bunny::set_default_allocator_size(size_t	size)
{
  if (DefaultAllocator != NULL)
    Failure(return (false), EPERM, {"allocator"},
	    "The default allocator is already created. Setting its size is now impossible.",
	    false, size);
  DefaultAllocatorSize = size;
  return (true);
}

bool			bunny_set_default_allocator_size(size_t		s)
{
  Prelog({"allocator"}, "Entering", "?", nbr_bytes);
  if (bunny::set_default_allocator_size(s) == false)
    {
      bunny::TryFlushError();
      return (false);
    }
  Postlog({"allocator"}, "Leaving", alloc, nbr_bytes);
  return (true);
}
