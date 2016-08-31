// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// HBSL - Threads - Workers

#ifndef			__WIN32
# include		"Threads.hpp"

bool			hbs::Workers::GetMessage(hbs::Workers::Message		&msg)
{
  if (messages.empty())
    {
      /// Remove dead threads
      if (nbr_worker != nbr_thread)
	{
	  std::list<ThreadInfo>::iterator	it;

	  for (it = threads.begin(); it != threads.end(); )
	    if (it->state == DEAD)
	      {
		it = threads.erase(it);
		nbr_thread -= 1;
	      }
	    else
	      ++it;
	  tit = threads.begin();
	}
      return (false);
    }

  pthread_mutex_lock(&msg_lock);
  msg = messages.front();
  messages.pop();
  pthread_mutex_unlock(&msg_lock);
  return (true);
}

#endif
