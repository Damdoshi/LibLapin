/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Bibliotheque Lapin
*/

/*!
** \file asynclock.h
** The Asynclock module is useful to insert functions that will be called
** later, for a specific duration or regulary.
**
** This module is quite complex! Pay attention to what you read.
*/

#ifndef			__LAPIN_ASYNCLOCK_H__
# define		__LAPIN_ASYNCLOCK_H__
# if			!defined(__LAPIN_H__)
#  error		You cannot include this file directly.
# endif

/*!
** A timestamp with nanosecond precision.
*/
typedef uint64_t	t_bunny_time;

/*!
** Get the system hour in nanoseconds.
** \return The system hour in ns.
*/
t_bunny_time		bunny_get_time(void);

/*!
** Sleep a specific duration in microseconds.
** Returns the duration that was skipped if a signal occurs
*/
unsigned long long	bunny_usleep(unsigned long long			delay);

/*!
** Sleep a specific duration in nanoseconds.
** Returns the duration that was skipped if a signal occurs
*/
t_bunny_time		bunny_sleep(t_bunny_time			delay);

/*!
** Get the difference between two hours.
** \param bef The oldest hour.
** \param now The youngest hour.
** \param The difference in nanoseconds.
*/
t_bunny_time		bunny_delta_time(t_bunny_time			bef,
					 t_bunny_time			now);

/*!
** Describe if the event must be called after or before the function
** established as the loop main function with bunny_set_loop_main_function.
*/
typedef enum		e_bunny_call_order
  {
    BCO_BEFORE_LOOP_MAIN_FUNCTION,
    BCO_AFTER_LOOP_MAIN_FUNCTION
  }			t_bunny_call_order;

/*
** Described later.
*/
struct			s_bunny_trap;

/*!
** The function that will be called when its matching trap occurs.
** Receive informations about the trap and an arbitrary value.
** \param elapsed The program elapsed time.
** \param trp The trap description structure
** \param data An arbitrary value given when defining the trap.
*/
typedef void		(*t_bunny_trap_function)(double			elapsed_time,
						 struct s_bunny_trap	*trp,
						 void			*data);

/*!
** Represent an event of the main loop that is fakely asynchronous with it.
** Private fields are inside business.
**
**
** The function pointer is the one that will be used when the trap occurs.
** The addiitonal_param is an arbitrary parameter set when creating the trap
** that will be given to the callback function defined.
*/
typedef struct		s_bunny_trap
{
  const char		_private[3 * sizeof(void*)];
  const double		start_time;
  const double		duration;
  t_bunny_trap_function	function;
  void			*additional_param;
}			t_bunny_trap;

/*!
** Define a new trap: a function that will be called under certain circumstances.
**
** - - If start_time is positive : - -
**
** If duration is superior to 0:
** - Each loop if the current time is between start_time and start_time + duration
**
** If duration is 0 or really close to 0:
** - The function will be called only one time if the current time is after start_time
**   and the function was never called
**
** If duration is negative:
** - Every -duration, the function is called again
**
** - - If start_time is negative or zero : - -
**
** The trap will wait for every tasks stacked before it to be played.
** Its behavior will be exacly the same except for the previously specified point.
**
** The function is called with the elapsed time, the returned t_bunny_trap and the
** sent param as parameter.
**
** \param func The function to call under specified conditions
** \param order The function will be called
** \return Return the structure that incarnates the trap. NULL on error.
*/
t_bunny_trap		*bunny_new_trap(t_bunny_trap_function		func,
					t_bunny_call_order		order,
					double				start_time,
					double				duration,
					void				*param);

/*!
** Remove the sent trap from the asynclock. You can call it safely from anywhere,
** even from a t_bunny_trap function: the asynclock will remove it in the end of
** its cycle.
** \param trap The trap to remove, it musts have been created by bunny_new_trap.
*/
void			bunny_delete_trap(t_bunny_trap			*trap);

/*!
** This function manage all traps accordingly to the indicated elapsed_time.
** It updates the current_time accordingly to what you give to it and call
** functions. The t_bunny_call_order is a filter allowing to call only a subset
** of previously registered functions.
**
** /!\ You are NOT supposed to use this function if you use bunny_loop or
** bunny_loop_mw. These functions already call bunny_asynclock!
**
** \param elapsed_time The elasped time since the last call to bunny_asynclock, in seconds.
** If you wish to use bunny_asynclock by yourself (without bunny_loop* functions), you
** should use clock_gettime or gettimeofday to get the time progression.
** In case you use a timeval*, for example, the time in the bunny format will be
** ((double)tv->tv_sec + (double)tv->tv_nsec / 1e9)
**
** \param order Are we before the function set with bunny_loop_main_function or
** after?
** \return How many traps are still registered. Useful to stack tasks to end,
** make a cartoon or things like that.
*/
int			bunny_asynclock(double				elapsed_time,
					t_bunny_call_order		order);

/*!
** Set the bunny clock (the program time, not real time) to the current real time
** \return The new program time.
*/
double			bunny_reset_clock(void);

/*!
** Return the current bunny time.
** This is not a real time clock: it is updated by bunny_asynclock,
** so it is your-program-time.
** \return The current bunny time, in seconds.
*/
double			bunny_get_current_time(void);

# define		bunny_time_old(tim)		(tim < bunny_get_current_time())
# define		bunny_time_alive(tim)		(tim >= bunny_get_current_time())

#endif	/*			__LAPIN_ASYNCLOCK_H__	*/
