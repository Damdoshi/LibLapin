// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2019
//
// Lapin library

#ifndef			__LAPIN_PRIVATE_ALLOCATOR_HPP__
# define		__LAPIN_PRIVATE_ALLOCATOR_HPP__
# include		"lapin2/allocator.h"

namespace		bunny
{
  extern size_t		DefaultAllocatorSize;
  extern t_bunny_allocator *DefaultAllocator;

  t_bunny_allocator	*new_allocator(size_t				nbr_bytes);
  t_bunny_allocator	*new_stack_allocator(void			*data,
					     size_t			nbr_bytes);
  void			delete_allocator(t_bunny_allocator		*allocator);
  t_bunny_ptrdiff	allocator_offset(t_bunny_allocator		*allocator);
  t_bunny_allocator	*migrate_allocator(t_bunny_allocator		*allocator,
					   void				(*func)(void*, t_bunny_ptrdiff));
  void			*migrate_pointer(t_bunny_ptrdiff		diff,
					 void				*ptr);
  void			foreach_allocation(t_bunny_allocator		*ptr,
					   void				(*func)(void*, t_bunny_ptrdiff));

  ssize_t		print_allocator(t_bunny_allocator		*allocator,
					t_bunny_allocator_print_mode	mode);
  ssize_t		save_allocator(const char			*file,
				       t_bunny_allocator		*allocator);
  ssize_t		save_fd_allocator(int				fd,
					  t_bunny_allocator		*allocator);
  ssize_t		write_allocator(char				*buf,
					size_t				buflen,
					t_bunny_allocator		*allocator);
  t_bunny_allocator	*load_allocator(const char			*file);
  t_bunny_allocator	*load_fd_allocator(int				fd);
  t_bunny_allocator	*read_allocator(const char			*buf,
					size_t				buflen);
  void			get_allocation(t_bunny_allocator		*allocator,
				       unsigned int			id);

  size_t		get_default_allocator_size(void);
  bool			set_default_allocator_size(size_t		size);
  t_bunny_allocator	*get_default_allocator(void);

  size_t		allocator_push_id(void);
  size_t		allocator_pop_id(void);
  size_t		allocator_get_id(void);

  void			realloc(void					*ptr,
				size_t					newsize,
				size_t					id,
				t_bunny_destructor			dtor,
				t_bunny_allocator			*buf,
				const char				*file,
				size_t					line);
}

#endif	//		__LAPIN_PRIVATE_ALLOCATOR_HPP__
