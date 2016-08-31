// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// HBSL - Threads - Workers

#ifndef			__WIN32
# include		"Threads.hpp"

void			hbs::Workers::SetMessage(hbs::Workers::Message		msg)
{
  pthread_mutex_lock(&msg_lock);
  messages.push(msg);
  pthread_mutex_unlock(&msg_lock);
}

#endif
