// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// HBSL - Threads - Workers

#ifndef			__WIN32
# include		"Threads.hpp"

bool			hbs::Workers::Add(hbs::Work		&work,
					  hbs::IdTask		ts)
{
  pthread_mutex_lock(&tit->task_lock);
  try
    {
      tit->tasks.push(hbs::Workers::Task(&work, ts));

      pthread_mutex_lock(&tasks_cnt_lock);
      tasks_stacked += 1;
      pthread_mutex_unlock(&tasks_cnt_lock);
    }
  catch (const std::bad_alloc	&e)
    {
      pthread_mutex_unlock(&tit->task_lock);
      return (false);
    }

  pthread_cond_signal(&tit->condvar);
  pthread_mutex_unlock(&tit->task_lock);

  if (++tit == threads.end())
    tit = threads.begin();

  return (true);
}

bool				hbs::Workers::Add(std::list<Task>	&tasks)
{
  std::list<ThreadInfo>::iterator	itti;
  std::list<Task>::iterator	it;

  for (itti = threads.begin(); itti != threads.end(); ++itti)
    if (itti->state == ALIVE)
      pthread_mutex_lock(&itti->task_lock);

  for (itti = threads.begin(), it = tasks.begin(); it != tasks.end();
       itti = (++itti == threads.end() ? threads.begin() : itti))
    if (itti->state == ALIVE)
      {
	tasks_stacked++;
	try
	  {
	    itti->tasks.push(*it);
	  }
	catch (const std::bad_alloc	&e)
	  {
	    tasks_stacked--;
	    for (itti = threads.begin(); itti != threads.end(); ++itti)
	      if (itti->state == ALIVE)
		{
		  pthread_cond_signal(&itti->condvar);
		  pthread_mutex_unlock(&itti->task_lock);
		}
	    return (false);
	  }
	it = tasks.erase(it);
      }

  for (itti = threads.begin(); itti != threads.end(); ++itti)
    if (itti->state == ALIVE)
      {
	pthread_cond_signal(&itti->condvar);
	pthread_mutex_unlock(&itti->task_lock);
      }
  return (true);
}

#endif

