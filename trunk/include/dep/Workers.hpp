// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// HBSL - Threads - Workers

#ifndef					__HBSL_THREADS_WORKERS_HPP__
# define				__HBSL_THREADS_WORKERS_HPP__
# ifndef				__WIN32
#  include				<stdexcept>
#  include				<utility>
#  include				<queue>
#  include				<list>
#  include				<pthread.h>
#  include				"Work.hpp"

namespace				hbs
{
  //! Workers is a thread pool made to work with the Work class
  /*!
  ** The Workers class allows the user to ask for a specific amount
  ** of thread. The amount of thread can be changed. You also
  ** can watch the load balancy and act in consequence.
  **
  ** You can add works in the Workers class, one at time, or
  ** several in one single call. Getting returned message is
  ** easy thanks to the GetMessage function.
  **
  ** You can watch how many threads are running, so you
  ** can fork instead of adding new threads if you think
  ** you are full.
  */
  class					Workers
  {
  public:
    /*!
    ** \def
    ** The Task pair binds the Id of a task with its work.
    */
    typedef std::pair<Work*, IdTask>	Task;

    /*!
    ** \def The Message pair binds the Id of a message with its work.
    */
    typedef std::pair<Work*, IdMessage>	Message;

    /*!
    ** \enum Load
    ** The Load enumeration indicates the level of load in
    ** the thread pool with the current amount of threads.
    */
    enum				Load
      {
	OVERLOAD,
	NOMINAL,
	UNDERLOAD
      };

  private:
    enum				State
      {
	ALIVE,
	ASK_TO_DIE,
	DEAD
      };

    struct				ThreadInfo
    {
      hbs::Workers			*pool;
      size_t				id;
      pthread_t				info;
      State				state;
      pthread_cond_t			condvar;
      std::queue<Task>			tasks;
      pthread_mutex_t			task_lock;
      int				tasks_done;
      bool				working;
    };

    size_t				nbr_worker;
    size_t				nbr_thread;
    std::list<ThreadInfo>		threads;
    std::list<ThreadInfo>::iterator	tit;

    mutable pthread_mutex_t		tasks_cnt_lock;
    size_t				tasks_stacked;
    size_t				threads_working;

    std::queue<Message>			messages;
    pthread_mutex_t			msg_lock;

    // These three funcctions might throw std::bad_alloc
    // Loop might throw any kind of exception thrown by a library user
    // JumpToLoop catch all and return after logging a little about these
    void				Loop(ThreadInfo				&info);
    void				SetMessage(hbs::Workers::Message	msg);
    static void				*JumpToLoop(void			*info);

    void				RealAddThread(size_t			thread);

  public:
    //! Add a specific amount of threads inside the thread pool
    /*!
    ** Add a specific amount of threads inside the thread pool. You should never
    ** use AddThread when threads are working.
    ** \param thread How many threads you want to add.
    ** \return Return false on error if HBSL_NO_THROW is set.
    ** \throw std::runtime_error The function may throw if the creation of a thread
    ** fail. All threads are killed before throwing, if some were previously successfuly
    ** launched.
    ** \throw std::bad_alloc The function may throw if there is not enough space
    ** in memory to enlarge the list of threads.
    */
    bool				AddThread(size_t			thread);

    //! Remove a specific amount of threads inside the thread pool
    /*!
    ** The RemoveThread function remove a specified quantity of threads. Note that
    ** threads may not die instantly: The thread pool will wait that their current
    ** work is done.
    ** \param thread How many threads you want to remove.
    */
    void				RemoveThread(size_t			thread = 0);

    //! Return how many threads are running right know, ignoring threads awaiting for removal.
    size_t				GetHowManyWorkers(void) const;
    //! Return how many threads are running right know.
    size_t				GetHowManyThreads(void) const;

    //! Add a single task to do.
    /*!
    ** \brief Add Add a single task to do.
    ** \param work The class that contains the code that will be executed by a thread
    ** \param ts A subtask specification.
    ** \return Return false on error.
    */
    bool				Add(hbs::Work				&work,
					    hbs::IdTask				ts = hbs::NoDetails);
    //! Add several task to do
    /*!
    ** \brief Add Add several tasks to do in the thread pool. You should use this function
    ** instead of calling several time the Add function that push a single task in order
    ** to avoid several mutex locking and unlocked.
    ** \param tasks A queue of Task, std::pair that contains a Work pointer and a subtask
    ** id. Elements will be removed if successfully registered.
    ** \return Return false if the list is not empty, so some elements failed to be registered.
    */
    bool				Add(std::list<Task>			&tasks);

    //! How many tasks are awaiting to be treated in the thread pool.
    size_t				GetHowManyTasks(void) const;

    //! How many threads are waiting in the thread pool.
    size_t				GetAwaitingThreads(void) const;

    //! Ask if not all works are done and if not all threads are waiting
    bool				IsWorking(void) const;

    //! Get message returned from asked tasks
    /*!
    ** \brief GetMessage Get a message returned from a Work class to the thread pool.
    ** GetMessage also remove dead threads from the structure while returning false.
    ** You should only use GetMessage after all threads end their work.
    ** \param msg A buffer you have to sent that will be filled with the message.
    ** \return Return false if the msg parameter was untouched, true if a message
    ** was written.
    */
    bool				GetMessage(hbs::Workers::Message	&msg);

    //! Ask for an performance evaluation.
    /*!
    ** \brief EvaluateTheLoad This function evaluates thanks to the number of threads,
    ** the length of the task queue and the current working threads the load of the
    ** thread pool.
    ** \return The function return the load balancy. Over, under or nominal load.
    */
    Load				EvaluateTheLoad(void) const;

    //! Build the tread pool with a specific quantity of threads
    /*!
    ** \brief Workers Workers build the thread pool with a specific quantity fo threads
    ** \param nbr_thread The number of threads you want in your thread pool. This can
    ** be 0 if you only want to create a thread pool that you will extend later.
    ** \throw std::system_error The function may throw if the creation of a thread
    ** fail. All threads are killed before throwing, if some were previously successfuly
    ** launched.
    ** \throw std::bad_alloc The function may throw if there is not enough space
    ** in memory to enlarge the list of threads.
    */
    Workers(size_t			nbr_thread = 3);
    //! Destroy the threads and the thread pool
    /*!
    ** \brief ~Workers The destructor ask to all thread to stop. It waits one
    ** seconde before killing them if they did not stop.
    ** If you wait that all threads end their work, of course, it is better.
    */
    virtual ~Workers(void);
  };
}

# endif
#endif	//				__HBSL_THREADS_WORKERS_HPP__
