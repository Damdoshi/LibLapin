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
# ifdef			__cplusplus
#  include		"cpp_guard.hpp"
# endif
# include		"attribute.h"
# include		"portability.h"

extern const size_t	gl_bunny_no_id;

typedef struct		s_bunny_allocator
{
  void			*first_byte;
  size_t		minimum_allocation_size;
  size_t		length;
  size_t		occupied_space;
  size_t		available_space;

  size_t		nbr_current_allocation;
  size_t		nbr_allocation;
  size_t		nbr_free;
  char			data[__ZERO_LENGTH__];
}			t_bunny_allocator;

typedef enum		e_bunny_allocator_print_mode
  {
    BAPM_OVERVIEW_INFORMATIONS,
    BAPM_FACTORIZED_BY_SIZE,
    BAPM_FULL_INFORMATIONS
  }			t_bunny_allocator_print_mode;

t_bunny_allocator	*bunny_new_allocator(size_t				nbr_bytes);
t_bunny_allocator	*_bunny_new_stack_allocator(void			*data,
						    size_t			nbr_bytes);
# define		bunny_new_stack_allocator(array_on_stack)		\
  _bunny_new_stack_allocator							\
  (&(array_on_stack)[0], NBRCELL(array_on_stack) * sizeof((array_on_stack)[0]))
void			bunny_delete_allocator(t_bunny_allocator		*allocator);
t_bunny_ptrdiff		bunny_allocator_offset(t_bunny_allocator		*allocator);
void			*bunny_migrate_pointer(t_bunny_ptrdiff			diff,
					       void				*ptr);
t_bunny_allocator	*bunny_migrate_allocator(t_bunny_allocator		*allocator,
						 void				(*func)(void*, t_bunny_ptrdiff));
void			bunny_foreach_allocation(t_bunny_allocator		*ptr,
						 void				(*func)(void*, t_bunny_ptrdiff));

ssize_t			bunny_print_allocator(t_bunny_allocator			*allocator,
					      t_bunny_allocator_print_mode	mode);
ssize_t			bunny_save_allocator(const char				*file,
					     t_bunny_allocator			*allocator);
ssize_t			bunny_save_fd_allocator(int				fd,
						t_bunny_allocator		*allocator);
ssize_t			bunny_write_allocator(char				*buf,
					      size_t				buflen,
					      t_bunny_allocator			*allocator);
t_bunny_allocator	*bunny_load_allocator(const char			*file);
t_bunny_allocator	*bunny_load_fd_allocator(int				fd);
t_bunny_allocator	*bunny_read_allocator(const char			*buf,
					      size_t				buflen);
void			*bunny_get_allocation(t_bunny_allocator			*allocator,
					      unsigned int			id);

bool			bunny_set_default_allocator_size(size_t			size);
const t_bunny_allocator	*bunny_get_default_allocator(void);

size_t			bunny_allocator_push_id(void);
size_t			bunny_allocator_pop_id(void);
size_t			bunny_allocator_get_id(void);

typedef void		(*t_bunny_destructor)(void);

void			_bunny_realloc(void					*ptr,
				       size_t					newsize,
				       size_t					id,
				       t_bunny_destructor			dtor,
				       t_bunny_allocator			*buf,
				       const char				*file,
				       size_t					line);

# define		bunny_realloc_id_opt(old, siz, id, opt)			\
  _bunny_realloc(old, siz, id, NULL, opt, __FILE__, __LINE__)
# define		bunny_realloc_opt(old, siz, opt)			\
  _bunny_realloc(old, siz, bunny_allocator_get_id_stack(), NULL, opt, __FILE__, __LINE__)
# define		bunny_realloc_id(old, siz, id)				\
  _bunny_realloc(old, siz, id, NULL, NULL, __FILE__, __LINE__)
# define		bunny_realloc(old, siz)					\
  _bunny_realloc(old, siz, bunny_allocator_get_id_stack(), NULL, NULL, __FILE__, __LINE__)

# define		bunny_malloc_id_opt(siz, id, opt)			\
  _bunny_realloc(NULL, siz, id, NULL, opt, __FILE__, __LINE__)
# define		bunny_malloc_opt(siz, opt)				\
  _bunny_realloc(NULL, siz, bunny_allocator_get_id_stack(), NULL, opt, __FILE__, __LINE__)
# define		bunny_malloc_id(siz, id)				\
  _bunny_realloc(NULL, siz, id, NULL, NULL, __FILE__, __LINE__)
# define		bunny_malloc(siz)					\
  _bunny_realloc(NULL, siz, bunny_allocator_get_id_stack(), NULL, NULL, __FILE__, __LINE__)

# define		bunny_malloc_dtor_id_opt(siz, id, dtor, opt)		\
  _bunny_realloc(NULL, siz, id, dtor, opt, __FILE__, __LINE__)
# define		bunny_malloc_dtor_opt(siz, dtor, opt)			\
  _bunny_realloc(NULL, siz, bunny_allocator_get_id_stack(), dtor, opt, __FILE__, __LINE__)
# define		bunny_malloc_dtor_id(siz, dtor, id)			\
  _bunny_realloc(NULL, siz, id, dtor, NULL, __FILE__, __LINE__)
# define		bunny_malloc_dtor(siz, dtor)				\
  _bunny_realloc(NULL, siz, bunny_allocator_get_id_stack(), dtor, NULL, __FILE__, __LINE__)

# define		bunny_calloc_id_opt(nbr, siz, id, opt)			\
  memset(bunny_malloc_id_opt((size_t)(nbr) * (siz), id, opt), 0, (size_t)(nbr) * (siz))
# define		bunny_calloc_opt(nbr, siz, opt)				\
  memset(bunny_malloc_opt((size_t)(nbr) * (siz), bunny_allocator_get_id_stack(), opt), 0, (size_t)(nbr) * (siz))
# define		bunny_calloc_id(nbr, siz, id)				\
  memset(bunny_malloc_id((size_t)(nbr) * (siz), id), 0, (size_t)(nbr) * (siz))
# define		bunny_calloc(nbr, siz)					\
  memset(bunny_malloc((size_t)(nbr) * (siz)), 0, (size_t)(nbr) * (siz))

# define		bunny_free_id_opt(id, opt)				\
  _bunny_realloc(NULL, 0, id, NULL, opt, __FILE__, __LINE__)
# define		bunny_free_opt(old, opt)				\
  _bunny_realloc(old, 0, gl_bunny_no_id, NULL, opt, __FILE__, __LINE__)
# define		bunny_free_id(id)					\
  _bunny_realloc(NULL, 0, id, NULL, NULL, __FILE__, __LINE__)
# define		bunny_free(old)						\
  _bunny_realloc(old, 0, gl_bunny_no_id, NULL, NULL, __FILE__, __LINE__)

# ifdef			__cplusplus
#  include		"cpp_guard_end.hpp"
# endif
#endif	/*		__LAPIN_ALLOCATOR_H__					*/
