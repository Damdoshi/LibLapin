// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2019
//
// Lapin library

#ifndef			__LAPIN_PRIVATE_ALLOCATOR_HPP__
# define		__LAPIN_PRIVATE_ALLOCATOR_HPP__
# include		"lapin2/allocator.h"

namespace		bunny
{
  t_bunny_allocator	*new_allocator(size_t			nbr_bytes);
  void			delete_allocator(t_bunny_allocator	*allocator);
  ptrdiff_t		allocator_offset(t_bunny_allocator	*allocator);
  t_bunny_allocator	*migrate_allocator(t_bunny_allocator	*allocator);

  bool			set_default_allocator_size(size_t	size);
  t_bunny_allocator	*get_default_allocator(void);

  size_t		allocator_push_id(void);
  size_t		allocator_pop_id(void);
  size_t		allocator_get_id(void);
}

#endif	//		__LAPIN_PRIVATE_ALLOCATOR_HPP__
