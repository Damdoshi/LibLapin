// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

#define			PATTERN "%p history, %zu time -> %zu"

size_t			bunny_history_erase_before(t_bunny_history	*h,
						   size_t		tim)
{
  struct bunny_history	*his = (struct bunny_history*)h;
  std::map<size_t, void*>::iterator it;
  size_t		del;

  if (his->history.empty())
    scream_error_if
      (return (0), BE_CANNOT_FIND_ELEMENT, PATTERN,
       "history", h, tim, (size_t)0);
  if ((it = his->history.find(tim)) == his->history.end())
    {
      for (it = --his->history.end();
	   it != his->history.begin() && it->first > tim;
	   --it);
      if (it == his->history.begin() && it->first > tim)
	scream_error_if
	  (return (0), BE_CANNOT_FIND_ELEMENT, PATTERN,
	   "history", h, tim, (size_t)0);
    }

  --it;
  del = 0;
  while (it != his->history.begin())
    {
      bunny_free(it->second);
      it = --his->history.erase(it);
      his->nbr_frame -= 1;
      del += 1;
    }
  his->nbr_frame -= 1;
  bunny_free(it->second);
  his->history.erase(it);

  if (his->nbr_frame == 0)
    {
      his->last_frame = NULL;
      his->last_frame_time = 0;
      his->oldest_frame_time = 0;
    }
  else
    {
      his->last_frame = his->history.rbegin()->second;
      his->last_frame_time = his->history.rbegin()->first;
      his->oldest_frame_time = his->history.begin()->first;
    }

  scream_log_if(PATTERN, "history", his, tim, del);
  return (del);
}

