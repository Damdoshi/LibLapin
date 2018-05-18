// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

#define			PATTERN "%p history -> %zu"

size_t			bunny_history_clear(t_bunny_history	*h)
{
  struct bunny_history	*his = (struct bunny_history*)h;
  std::map<size_t, void*>::iterator it;
  size_t		del;

  for (it = his->history.begin(); it != his->history.end(); ++it)
    bunny_free(it->second);

  del = his->nbr_frame;
  his->history.clear();

  his->nbr_frame = 0;
  his->last_frame = NULL;
  his->last_frame_time = 0;
  his->oldest_frame_time = 0;

  scream_log_if(PATTERN, "history", his, del);
  return (del);
}

