// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include		<list>
#include		"Threads.hpp"
#include		"lapin.h"

#ifndef			__WIN32

std::list<hbs::Work*>	_ToDelete;

void			_ClearWorkers(void)
{
  std::list<hbs::Work*>::iterator it;

  for (it = _ToDelete.begin(); it != _ToDelete.end(); ++it)
    delete *it;
  _ToDelete.clear();
}

void			bunny_thread_wait_completion(t_bunny_threadpool	*pol)
{
  hbs::Workers		*w = (hbs::Workers*)pol->_private;
  hbs::Workers::Message	msg;

  while (w->GetHowManyTasks())
    usleep(300);
  while (w->GetMessage(msg));
  _ClearWorkers();
}

#else

void			bunny_thread_wait_completion(t_bunny_threadpool	*pol)
{
  (void)pol;
}

#endif


