// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// HBSL - Threads - Workers

#ifndef			__WIN32
# include		"Threads.hpp"

void			*hbs::Workers::JumpToLoop(void				*data)
{
  ThreadInfo		&info = *(hbs::Workers::ThreadInfo*)data;

  try
    {
      info.pool->Loop(info);
    }
  catch (...)
    {
      return (NULL);
    }
  info.pool->nbr_worker -= 1;
  info.state = DEAD;
  return (NULL);
}

#endif

