// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include		<list>
#include		"Threads.hpp"
#include		"lapin.h"

#ifndef			__WIN32

class			_Launcher
  : public hbs::WorkSpec::Work3<_Launcher, t_bunny_function, void*, const void*>
{
public:
  hbs::IdMessage	operator()(hbs::IdTask				task,
				   t_bunny_function			func,
				   void					*data,
				   const void				*add)
  {
    (void)task;
    func(data, add);
    return (0);
  }

  _Launcher(t_bunny_function	func,
	    void		*data,
	    const void		*add)
    : Work3(*this, func, data, add)
  {}
  ~_Launcher(void) {}
};

extern std::list<hbs::Work*>	_ToDelete;

void			_ClearWorkers(void);

#endif

bool			bunny_thread_foreach(t_bunny_threadpool		*pol,
					     t_bunny_function		func,
					     void			**data,
					     size_t			len,
					     const void			*add_ptr)
{
#ifndef			__WIN32
  hbs::Workers		*work = (hbs::Workers*)pol->_private;
  std::list<hbs::Workers::Task> task;
  size_t		i;

  for (i = 0; i < len; ++i)
    {
      _Launcher		*ptr;

      if ((ptr = new _Launcher(func, data[i], add_ptr)) == NULL)
	{
	  _ClearWorkers();
	  return (false);
	}
      try
	{
	  _ToDelete.push_back(ptr);
	  task.push_back(hbs::Workers::Task(ptr, i));
	}
      catch (...)
	{
	  _ClearWorkers();
	  return (false);
	}
    }
  if (work->Add(task) == false)
    {
      _ClearWorkers();
      return (false);
    }
  return (true);
  
#else
    size_t		i;

    for (i = 0; i < len; ++i)
        func(data[i], add_ptr);
  return (true);
#endif
}

