// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2017
//
// Bibliotheque Lapin

#include		<list>
#include		"Threads.hpp"
#include		"lapin_private.h"

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

#endif

extern std::list<hbs::Work*>	_ToDelete;

#define			PATTERN						\
  "%p threadpool, %p function, %p data, %p additional data -> %s"

bool			bunny_thread_push(t_bunny_threadpool		*pol,
					  t_bunny_function		func,
					  void				*data,
					  const void			*param)
{
#ifndef			__WIN32
  hbs::Workers		*workers = (hbs::Workers*)pol->_private;
  hbs::Work		*work;

  if ((work = new (std::nothrow) _Launcher(func, data, param)) == NULL)
    scream_error_if(return (false), ENOMEM, PATTERN, pol, func, data, param, "false");
  try
    {
      _ToDelete.push_back(work);
    }
  catch (...)
    {
      delete work;
      scream_error_if(return (false), ENOMEM, PATTERN, pol, func, data, param, "false");
    }
  if (workers->Add(*work) == false)
    {
      _ToDelete.pop_back();
      delete work;
      scream_error_if(return (false), bunny_errno, PATTERN, pol, func, data, param, "false");
      return (false);
    }
  scream_log_if(PATTERN, pol, func, data, param, "true");
  return (true);
#else
  (void)pol;
  func(data, param);
  scream_log_if(PATTERN, pol, func, data, param, "true");
  return (true);
#endif
}

