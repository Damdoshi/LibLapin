// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

#define			PATTERN "%p history, %zu time -> %p"

const void	*bunny_history_get_frame(t_bunny_history	*h,
						 size_t			tim)
{
  struct bunny_history	*his = (struct bunny_history*)h;
  std::map<size_t, void*>::iterator it;

  if ((it = his->history.find(tim)) == his->history.end())
    {
      for (it = --his->history.end();
	   it != his->history.begin() && it->first > tim;
	   --it);
      if (it == his->history.begin() && it->first > tim)
	scream_error_if
	  (return (0), BE_CANNOT_FIND_ELEMENT, PATTERN,
	   "history", h, tim, (void*)NULL);
    }

  scream_log_if(PATTERN, "history", his, tim, it->second);
  return (it->second);
}

