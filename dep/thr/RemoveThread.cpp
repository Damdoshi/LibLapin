// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// HBSL - Threads - Workers

#ifndef			__WIN32
# include		"Threads.hpp"

void			hbs::Workers::RemoveThread(size_t		thread)
{
  std::list<ThreadInfo>::iterator	it;

  if (thread == 0)
    {
      for (it = threads.begin(); it != threads.end(); ++it)
	if (it->state == ALIVE)
	  {
	    nbr_worker -= 1;
	    thread -= 1;
	    pthread_cond_signal(&it->condvar);
	    it->state = ASK_TO_DIE;
	  }
    }
  else
    for (it = threads.begin(); it != threads.end() && thread > 0; ++it)
      if (it->state == ALIVE)
	{
	  it->state = ASK_TO_DIE;
	  nbr_worker -= 1;
	  thread -= 1;
	  pthread_cond_signal(&it->condvar);
	}
}

#endif

