// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

#define			PATTERN "%zu frame_size -> %p"

t_bunny_history		*bunny_new_history(size_t		frame_size)
{
  struct bunny_history	*his;

  if ((his = new (std::nothrow) struct bunny_history) == NULL)
    scream_error_if
      (return (NULL), bunny_errno, PATTERN, "history", frame_size, his);
  his->frame_size = frame_size;
  his->last_frame_time = 0;
  his->oldest_frame_time = 0;
  his->nbr_frame = 0;
  his->last_frame = NULL;
  scream_log_if(PATTERN, "history", frame_size, his);
  return ((t_bunny_history*)his);
}

