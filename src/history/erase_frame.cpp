// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

#define			PATTERN "%p history, %zu time -> %s"

bool			bunny_history_erase_frame(t_bunny_history	*h,
						  size_t		tim)
{
  struct bunny_history	*his = (struct bunny_history*)h;
  std::map<size_t, void*>::iterator it;

  if (his->history.empty())
    scream_error_if
      (return (0), BE_CANNOT_FIND_ELEMENT, PATTERN,
       "history", h, tim, "false");
  if ((it = his->history.find(tim)) == his->history.end())
    {
      for (it = --his->history.end();
	   it != his->history.begin() && it->first > tim;
	   --it);
      if (it == his->history.begin() && it->first > tim)
	scream_error_if
	  (return (0), BE_CANNOT_FIND_ELEMENT, PATTERN,
	   "history", h, tim, "false");
    }

  bunny_free(it->second);
  his->history.erase(it);
  if ((his->nbr_frame -= 1) == 0)
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

  scream_log_if(PATTERN, "history", his, tim, "true");
  return (true);
}

