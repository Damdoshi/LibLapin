// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

#define			PATTERN "%p history, %zu time, %p frame -> %zu"

size_t			bunny_history_add_frame(t_bunny_history		*_his,
						size_t			tim,
						const void		*dt)
{
  struct bunny_history	*his = (struct bunny_history*)_his;
  std::map<size_t, void*>::iterator it;
  void			*n;

  if ((it = his->history.find(tim)) == his->history.end())
    try
      {
	if ((n = bunny_memdup(dt, his->frame_size)) == NULL)
	  scream_error_if
	    (return (0), bunny_errno, PATTERN, "history", his, tim, dt, (size_t)0);
	auto thing = his->history.emplace(tim, n);
	it = thing.first;
      }
    catch (...)
      {
	bunny_free(n);
	scream_error_if
	  (return (0), ENOMEM, PATTERN, "history", his, tim, dt, (size_t)0);
      }
  memcpy(it->second, dt, his->frame_size);
  if (his->last_frame_time < tim)
    {
      his->last_frame_time = tim;
      his->last_frame = it->second;
    }
  if (his->oldest_frame_time > tim)
    his->oldest_frame_time = tim;
  his->nbr_frame += his->history.size();
  scream_log_if(PATTERN, "history", _his, tim, dt, his->nbr_frame);
  return (his->nbr_frame);
}

