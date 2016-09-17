// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// HBSL - Threads - Workers

#ifndef			__WIN32
# include		<string.h>
# include		"Threads.hpp"

void			hbs::Workers::RealAddThread(size_t		num)
{
  std::list<ThreadInfo>::iterator	it;
  size_t		len;
  size_t		i;

  len = threads.size();
  threads.resize(len + num);
  for (it = threads.begin(), i = 0; i < len; ++i, ++it);
  for (; it != threads.end(); ++it, ++i)
    {
      it->pool = this;
      it->id = i;
      memset(&it->task_lock, 0, sizeof(it->task_lock));
      // it->task_lock = PTHREAD_MUTEX_INITIALIZER;
      it->tasks_done = 0;
      it->state = ALIVE;
      it->working = false;
      if (pthread_create(&it->info, NULL, JumpToLoop, (void*)&*it) != 0)
	{
	  if (it != threads.begin())
	    do
	      (--it)->state = ASK_TO_DIE;
	    while (it != threads.begin());
	  throw ;
	}
    }
  nbr_worker += num;
  nbr_thread += num;
  tit = threads.begin();
}

bool			hbs::Workers::AddThread(size_t		num)
{
  try
    {
      RealAddThread(num);
    }
  catch (...)
    {
      return (false);
    }
  return (true);
}

#endif

