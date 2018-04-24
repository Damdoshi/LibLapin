/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Bibliotheque Lapin
*/

/*!
** \file threads.h
** An easy to use thread pool that allow you to exploit the multiple threads of your
** system without making anything more complex than a for like construction.
*/

#ifndef				__LAPIN_THREADS_H__
# define			__LAPIN_THREADS_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif

/*!
** A t_bunny_threadpool represents the threadpool for the library.
** It starts with a private field, and then the number of threads
*/
typedef struct			s_bunny_threadpool
{
  const void * const		_private;
  size_t			nbr_threads;
}				t_bunny_threadpool;

/*!
** The bunny_new_threadpool function creates a threadpool with the given amounth
** of threads.
** \param nbr The amount of threads you want
** \return A t_bunny_threadpool or NULL on error.
*/
t_bunny_threadpool		*bunny_new_threadpool(size_t			nbr);

/*!
** Delete the threadpool. Kill threads before returning.
** \param pol The threadpool to destroy.
*/
void				bunny_delete_threadpool(t_bunny_threadpool	*pol);

/*!
** The type of function where threads can jump.
** \param The data which came from the collection given to the bunny_thread_foreach.
** This data is only manipulated by this function.
** \param A void* pointer which is from the last parameter of bunny_thread_foreach.
** This data can be accessed by every threads, so pay attention to race condition!
** It is mainly here to be read, not written!
*/
typedef void			(*t_bunny_function)(void			*data,
						    void			*add_ptr);

/*!
** Make every threads inside pol call func with a part of data and add_ptr as parameter.
** \param pol The threadpool
** \param func The function that threads will call
** \param data An array of pointer to data that will be splitted in order to be sent
** to the t_bunny_function as first parameter.
** \param len The length of the data array
** \param A pointer that will be transmitted to t_bunny_function as second parameter.
** \return False if not enough memory was available to launch the foreach or
** if a critical error happened in the thread launching system. True if everything went
** well.
*/
bool				bunny_thread_foreach(t_bunny_threadpool		*pol,
						     t_bunny_function		func,
						     void			**data,
						     size_t			len,
						     void			*add_ptr);

/*!
** Push a single task at the top of the thread pool.
** \param pol The threadpool
** \param func The function that a thread will call
** \param data The data that will be treated by the thread in func
** \param A pointer that will be transmitted to func.
** \return False if not enough memory was available, true if everything went well.
*/
bool				bunny_thread_push(t_bunny_threadpool		*pol,
						  t_bunny_function		func,
						  void				*data,
						  void				*add_ptr);

/*!
** This function does not return while every threads are not back in the threadpool sleeping.
** Useful to wait between two foreach, when their order is important.
** \param pol The threadpool.
*/
void				bunny_thread_wait_completion(t_bunny_threadpool	*pol);

/*!
** This function allow you to define how many threads will be working
** behind the bunny_loop to achieve asynchronous computation sent with
** bunny_async_computation_push and bunny_async_computation_foreach.
** The previous threadpool if it exists will be destroyed if it manages a different
** amount of threads.
** This threadpool is automatically freed at the end of the program if it was
** not freed manually before.
** \param nbr The amount of threads. 0 to only destroy it.
** \return If the creation of the threadpool succeed or not. True if 0 was sent.
*/
bool				bunny_set_async_computation(size_t		nbr);

/*!
** This function push a single task inside the bunny loop thread pool.
** When it will be complete, it will trigger an event.
** \param func The function to call.
** \param dt The data that will be treated by the function.
** \param ad An additional pointer that will be transmited to func.
*/
bool				bunny_async_computation_push(t_bunny_function	func,
							     void		*dt);

/*!
** Make every threads inside the bunny_loop threadpool call func with a part of
** data and add_ptr as parameter.
** \param func The function that threads will call
** \param data An array of pointer to data that will be splitted in order to be sent
** to the t_bunny_function as first parameter.
** \param len The length of the data array
** \param A pointer that will be transmitted to t_bunny_function as second parameter.
** \return False if not enough memory was available to launch the foreach or
** if a critical error happened in the thread launching system. True if everything went
** well.
*/
bool				bunny_async_computation_foreach(t_bunny_function func,
								void		**data,
								size_t		len);

#endif	/*			__LAPIN_THREADS_H__	*/

