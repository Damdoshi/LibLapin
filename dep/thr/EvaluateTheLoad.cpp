// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// HBSL - Threads - Workers

#ifndef			__WIN32
# include		"Threads.hpp"

hbs::Workers::Load	hbs::Workers::EvaluateTheLoad(void) const
{
  Load			load;

  pthread_mutex_lock(&tasks_cnt_lock);
  if (threads_working < nbr_worker)
    load = UNDERLOAD;
  else if (tasks_stacked > 0)
    load = OVERLOAD;
  else
    load = NOMINAL;
  pthread_mutex_unlock(&tasks_cnt_lock);
  return (load);
}

#endif
