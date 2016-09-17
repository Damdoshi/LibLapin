// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// HBSL - Threads - Workers

#ifndef				__WIN32
# include			"Threads.hpp"

void				hbs::Workers::Loop(ThreadInfo		&info)
{
  while (info.state == ALIVE || info.tasks.size())
    {
      // Looping until there is something to do
      pthread_mutex_lock(&info.task_lock);
      info.working = false;
      while (info.tasks.empty())
	pthread_cond_wait(&info.condvar, &info.task_lock);

      // There is something to do, so lets do it
      hbs::Workers::Task	ts;
      hbs::IdMessage		msg;

      ts = info.tasks.front();
      info.tasks.pop();
      info.tasks_done += 1;
      info.working = true;
      pthread_mutex_unlock(&info.task_lock);

      // Say that a thread is working
      pthread_mutex_lock(&tasks_cnt_lock);
      threads_working++;
      pthread_mutex_unlock(&tasks_cnt_lock);

      // Do the work
      if ((msg = (*ts.first)(ts.second)) != hbs::NoMessage)
	SetMessage(Message(ts.first, msg));

      // Note that the task is done and that there is one threads that will go to bed
      pthread_mutex_lock(&tasks_cnt_lock);
      tasks_stacked--;
      threads_working--;
      pthread_mutex_unlock(&tasks_cnt_lock);
    }
  info.state = DEAD;
}

#endif
