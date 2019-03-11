/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2019
**
** Bibliotheque Lapin
*/

#ifndef			__LAPIN_ALLOCATOR_H__
# define		__LAPIN_ALLOCATOR_H__
# if			!defined(__LAPIN_H__)
#  error		You cannot include this file directly.
# endif

typedef struct		s_bunny_allocator
{
  void			*first_byte;
  size_t		minimum_allocation_size;
  size_t		length;
  size_t		occupied_space;
  size_t		available_space;

  size_t		nbr_current_allocation;
  size_			nbr_allocation;
  size_			nbr_free;
  char			data[0];
}			t_bunny_allocator;

t_bunny_allocator	*bunny_new_allocator(size_t			nbr_bytes);
void			bunny_delete_allocator(t_bunny_allocator	*allocator);
ptrdiff_t		bunny_allocator_offset(t_bunny_allocator	*allocator);
t_bunny_allocator	*bunny_migrate_allocator(t_bunny_allocator	*allocator);

void			bunny_set_default_allocator_size(size_t		size);
const t_bunny_allocator	*bunny_get_default_allocator(void);

size_t			bunny_allocator_push_id(void);
size_t			bunny_allocator_pop_id(void);
size_t			bunny_allocator_get_id(void);

void			_bunny_realloc(void				*ptr,
				       size_t				newsize,
				       size_t				id,
				       t_bunny_allocator		*buf,
				       const char			*file,
				       size_t				line) _BMALLOC();

# define		bunny_realloc_id_opt(old, siz, id, opt)		\
  _bunny_realloc(old, siz, id, opt, __FILE__, __LINE__)
# define		bunny_realloc_opt(old, siz, opt)		\
  _bunny_realloc(old, siz, bunny_allocator_get_id_stack(), opt, __FILE__, __LINE__)
# define		bunny_realloc_id(old, siz, id)			\
  _bunny_realloc(old, siz, id, NULL, __FILE__, __LINE__)
# define		bunny_realloc(old, siz)				\
  _bunny_realloc(old, siz, bunny_allocator_get_id_stack(), NULL, __FILE__, __LINE__)

# define		bunny_malloc_id_opt(siz, id, opt)		\
  _bunny_realloc(NULL, siz, id, opt, __FILE__, __LINE__)
# define		bunny_malloc_opt(siz, opt)			\
  _bunny_realloc(NULL, siz, bunny_allocator_get_id_stack(), opt, __FILE__, __LINE__)
# define		bunny_malloc_id(siz, id)			\
  _bunny_realloc(NULL, siz, id, NULL, __FILE__, __LINE__)
# define		bunny_malloc(siz)				\
  _bunny_realloc(NULL, siz, bunny_allocator_get_id_stack(), NULL, __FILE__, __LINE__)

# define		bunny_calloc_id_opt(nbr, siz, id, opt)		\
  memset(bunny_malloc_id_opt((size_t)(nbr) * (siz), id, opt), 0, (size_t)(nbr) * (siz))
# define		bunny_calloc_opt(nbr, siz, opt)			\
  memset(bunny_malloc_opt((size_t)(nbr) * (siz), bunny_allocator_get_id_stack(), opt), 0, (size_t)(nbr) * (siz))
# define		bunny_calloc_id(nbr, siz, id)			\
  memset(bunny_malloc_id((size_t)(nbr) * (siz), id), 0, (size_t)(nbr) * (siz))
# define		bunny_calloc(nbr, siz)				\
  memset(bunny_malloc((size_t)(nbr) * (siz)), 0, (size_t)(nbr) * (siz))

# define		bunny_free_id_opt(id, opt)			\
  _bunny_realloc()

#endif	/*		__LAPIN_ALLOCATOR_H__				*/
