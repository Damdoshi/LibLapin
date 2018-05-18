/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2018
**
**
** Bibliotheque Lapin
*/

#ifndef				__LAPIN_HISTORY_H__
# define			__LAPIN_HISTORY_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif

typedef struct			s_bunny_history
{
  const size_t			frame_size;
  const size_t			last_frame_time;
  const size_t			oldest_frame_time;
  const size_t			nbr_frame;
  void				*last_frame;
}				t_bunny_history;

t_bunny_history			*bunny_new_history(size_t		frame_size);
size_t				bunny_delete_history(t_bunny_history	*h);

size_t				bunny_history_add_frame(t_bunny_history	*h,
							size_t		tim,
							const void	*dt);
const void	*bunny_history_get_frame(t_bunny_history *h,
							 size_t		tim);

bool				bunny_history_erase_frame(t_bunny_history *h,
							  size_t	tim);
size_t				bunny_history_erase_before(t_bunny_history *h,
							   size_t	nbr_frame);
size_t				bunny_history_erase_after(t_bunny_history *h,
							  size_t	nbr_frame);
size_t				bunny_history_clear(t_bunny_history	*h);

#endif	/*			__LAPIN_HISTORY_H__			*/
