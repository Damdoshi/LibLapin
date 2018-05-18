/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2018
**
**
** Bibliotheque Lapin
*/

#ifndef				__LAPIN_PRIVATE_HISTORY_H__
# define			__LAPIN_PRIVATE_HISTORY_H__
# include			<list>

struct				bunny_history
{
  size_t			frame_size;
  size_t			last_frame_time;
  size_t			oldest_frame_time;
  size_t			nbr_frame;
  void				*last_frame;
  std::map<size_t, void*>	history;
};

#endif	/*			__LAPIN_PRIVATE_HISTORY_H__	*/
