// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2019
//
// Lapin library

#include		<stdlib.h>
#define			__LAPIN_H__
#include		"private2/allocator.hpp"
#include		"private2/logs.hpp"

t_bunny_allocator	*bunny::new_allocator(size_t		nbr_bytes)
{
  t_bunny_allocator	*alloc;

  if (nbr_bytes <= sizeof(*alloc))
    Failure(return (NULL), EINVAL, {"allocator"}, "Insufficient memory width requested.", NULL, nbr_bytes);
  if ((alloc = (t_bunny_allocator*)malloc(nbr_bytes)) == NULL)
    Critical(return (NULL), bunny_errno, {"allocator"}, "", NULL, nbr_bytes);
  alloc->first_byte = &alloc->data[0];
  alloc->length = nbr_bytes;
  alloc->occupied_space = 0;
  alloc->available_space = nbr_bytes - (sizeof(*alloc) - sizeof(alloc->data));
  alloc->nbr_current_allocation = 0;
  alloc->nbr_allocation = 0;
  alloc->nbr_free = 0;
  return (alloc);
}

t_bunny_allocator	*bunny_new_allocator(size_t		nbr_bytes)
{
  t_bunny_allocator	*alloc;

  Prelog({"allocator"}, "Entering", "?", nbr_bytes);
  if ((alloc = bunny::new_allocator(nbr_bytes)) == NULL)
    {
      bunny::TryFlushError();
      return (NULL);
    }
  Postlog({"allocator"}, "Leaving", alloc, nbr_bytes);
  return (alloc);
}

