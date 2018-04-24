// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include		"lapin_private.h"

void			async_wrap(void					*data,
				   void					*add)
{
  t_async_order		*ord = (t_async_order*)data;

  (void)add;
  ord->func(ord->data_to_compute, ord->add_ptr);
  if (gl_callback.async_computation_response)
    gl_completed_tasks.push(ord->data_to_compute);
}

bool			bunny_async_computation_push(t_bunny_function	func,
						     void		*dt)
{
  t_async_order		*ord;

  if ((ord = (t_async_order*)bunny_malloc(sizeof(*ord))) == NULL)
    return (false);
  ord->func = func;
  ord->data_to_compute = dt;
  ord->add_ptr = gl_loop_data;
  return (bunny_thread_push(gl_bunny_loop_threadpool, async_wrap, ord, NULL));
}

