/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** Bibliotheque Lapin
*/

/*!
** \file queue.h
**
**
**
*/

#ifndef				__LAPIN_QUEUE_H__
# define			__LAPIN_QUEUE_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif

/*!
** The handy structure to represent your queue.
*/
typedef struct			s_bunny_queue
{
  const size_t			length;
  const void * const * const	front;
}				t_bunny_queue;

/*!
** Create a new queue.
** Return null on failure.
*/
# define			bunny_new_queue()			\
  ((t_bunny_queue*)bunny_calloc(1, sizeof(t_bunny_queue)))

/*!
** Delete the queue.
** \param queue The queue to destroy
** \return How many elements was in queue
*/
size_t				bunny_delete_queue(t_bunny_queue	*queue);

/*!
** Get how many elements there is in the queue.
** \param queue The queue to get the length
** \return The queue size in size_t
*/
# define			bunny_queue_size(queue)			((queue)->length)

/*!
** Test if the queue is empty.
** \param queue The queue to test
** \return True if it is empty
*/
# define			bunny_queue_empty(queue)		(!(queue)->length)

/*!
** Get the element at the top of the queue
** \param queue The queue to get the top element
** \param type The type of the element at the top
** \return The data at the top, NULL if there is none
*/
# define			bunny_queue_front(queue, type)		((queue)->front ? *((type*)(queue)->front) : (type)NULL)

/*!
** Push an element at the back of the queue
** \param queue The queue to edit
** \param data The data to queue
** \return True if everything went well
*/
bool				_bunny_queue_push(t_bunny_queue		*queue,
						  const void		*data);

/*!
** Push an element at the back of the queue
** \param queue The queue to edit
** \param data The data to queue
** \return True if everything went well
*/
# define			bunny_queue_push(qu, da)		_bunny_queue_push(qu, (void*)(size_t)da)

/*!
** Remove the element at the front of the queue.
** \param queue The queue to edit
** \return The data that was queueed, NULL if there was none.
*/
void				*_bunny_queue_pop(t_bunny_queue		*queue);

/*!
** Remove the element at the front of the queue and get it.
** \param qu The queue to edit
** \param ty The type of the extracted data
** \return The data that was queueed, NULL if there was none.
*/
# define			bunny_queue_pop(qu, ty)			(ty)_bunny_queue_pop(qu)

#endif	/*			__LAPIN_QUEUE_H__			*/
