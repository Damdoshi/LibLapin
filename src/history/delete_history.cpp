// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

#define			PATTERN "%p history -> %zu"

size_t			bunny_delete_history(t_bunny_history		*_his)
{
  struct bunny_history	*his = (struct bunny_history*)_his;
  size_t		len = his->nbr_frame;

  bunny_history_clear(_his);
  delete his;
  scream_log_if(PATTERN, "history", _his, len);
  return (len);
}

