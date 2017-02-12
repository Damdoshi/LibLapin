// Jason Brillante "Toilette"
// Hanged Bunny Studio 2à&'-2015
//
// HBSL - Threads - Task

#ifndef				__HBSL_THREADS_WORK_HPP__
# define			__HBSL_THREADS_WORK_HPP__
# include			<stdint.h>
# include			<limits>

namespace			hbs
{
  /*!
  ** \def The IdTask type represent an order.
  ** Users should define an enumeration instead
  ** of directly use IdTask as an integer.
  */
  typedef int64_t		IdTask;

  /*!
  ** \def The IdMessage type represent a direct
  ** response to the sent task. Users should define
  ** an enumeration instead of directly use IdMessage
  ** as an integer.
  */
  typedef int64_t		IdMessage;

  /*!
  ** \def The NoMessage symbolic constant is
  ** the default return value that any kind of single
  ** task class should return.
  ** If Workers return this value, it means that
  ** the thread died because of a crash.
  */
  enum
    {
      NoMessage			= 0
    };
  /*!
  ** \def The NoDetails symbolic constant is
  ** the default value that a single task class
  ** should take.
  */
  enum
    {
      NoDetails			= 0
    };

  //! Work is an interface that allow classes to be threaded by the Workers class
  /*!
  ** The Work class is an interface that will allow the class which inherit
  ** to be used by the thread pool hbs::Workers. The design is really simple:
  ** you the work is registered in the Workers class with an integer that
  ** will be sent to the operator() function. The function will return another
  ** integer that will be stored inside the Workers class until the GetMessage
  ** function is called.
  */
  class				Work
  {
  public:
    /*!
    ** \brief The function that will be called by the thread pool.
    ** \param detail Can be useful if a work class contains several tasks
    ** \return Any kind of message that would need to be returned.
    */
    virtual hbs::IdMessage	operator()(hbs::IdTask	detail = hbs::NoDetails) = 0;

    virtual ~Work(void) {}
  };

  //! Contains Work classes with a specific amount of parameters to build with
  namespace			WorkSpec
  {
    template<typename Class>
    struct			Work0 : public hbs::Work
    {
      typedef hbs::IdMessage	(Class::*Func)(hbs::IdTask		task);
      Class			&c;
      Func			ptr;

      hbs::IdMessage		operator()(hbs::IdTask			task)
      {
	return ((c.*ptr)(task));
      }

      Work0(Class		&cl)
	: c(cl),
	  ptr(&Class::operator())
      {}
      ~Work0(void)
      {}
    };

    template<typename Class, typename P1>
    struct			Work1 : public hbs::Work
    {
      typedef hbs::IdMessage	(Class::*Func)(hbs::IdTask		task,
					       P1			p1);
      Class			&c;
      Func			ptr;
      P1			p1;

      hbs::IdMessage		operator()(hbs::IdTask			task)
      {
	return ((c.*ptr)(task, p1));
      }

      Work1(Class		&cl,
	    const P1		&_p1)
      	: c(cl),
	  ptr(&Class::operator()),
	  p1(_p1)
      {}
      ~Work1(void)
      {}
    };

    template<typename Class, typename P1, typename P2>
    struct			Work2 : public hbs::Work
    {
      typedef hbs::IdMessage	(Class::*Func)(hbs::IdTask		task,
					       P1			p1,
					       P2			p2);
      Class			&c;
      Func			ptr;
      P1			p1;
      P2			p2;

      hbs::IdMessage		operator()(hbs::IdTask			task)
      {
	return ((c.*ptr)(task, p1, p2));
      }

      Work2(Class		&cl,
	    const P1		&_p1,
	    const P2		&_p2)
       	: c(cl),
	  ptr(&Class::operator()),
	  p1(_p1),
	  p2(_p2)
      {}
      ~Work2(void)
      {}
    };

    template<typename Class, typename P1, typename P2, typename P3>
    struct			Work3 : public hbs::Work
    {
      typedef hbs::IdMessage	(Class::*Func)(hbs::IdTask		task,
					       P1			p1,
					       P2			p2,
					       P3			p3);
      Class			&c;
      Func			ptr;
      P1			p1;
      P2			p2;
      P3			p3;

      hbs::IdMessage		operator()(hbs::IdTask			task)
      {
	return ((c.*ptr)(task, p1, p2, p3));
      }

      Work3(Class		&cl,
	    const P1		&_p1,
	    const P2		&_p2,
	    const P3		&_p3)
	: c(cl),
	  ptr(&Class::operator()),
	  p1(_p1),
	  p2(_p2),
	  p3(_p3)
      {}
      ~Work3(void)
      {}
    };
  }
}

#endif	//			__HBS_POOL_Work_HPP__
