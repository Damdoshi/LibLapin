// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// HBSL - Threads - Workers

#ifndef			__WIN32
# include		<signal.h>
# include		<unistd.h>
# include		<string.h>
# include		"Threads.hpp"

hbs::Workers::Workers(size_t		_nbr_thread)
  : nbr_worker(0),
    nbr_thread(0),
    //tasks_cnt_lock(PTHREAD_MUTEX_INITIALIZER),
    tasks_stacked(0),
    threads_working(0)//,
    //msg_lock(PTHREAD_MUTEX_INITIALIZER)
{
  memset(&tasks_cnt_lock, 0, sizeof(tasks_cnt_lock));
  memset(&threads_working, 0, sizeof(threads_working));
  RealAddThread(_nbr_thread);
}

hbs::Workers::~Workers(void)
{
  std::list<ThreadInfo>::iterator	it;

  for (it = threads.begin(); it != threads.end(); ++it)
    it->state = ASK_TO_DIE;
  usleep(1e6);
  for (it = threads.begin(); it != threads.end(); )
    if (it->state != DEAD)
      {
	pthread_kill(it->info, SIGKILL);
	it = threads.erase(it);
      }
    else
      ++it;
}

#endif

