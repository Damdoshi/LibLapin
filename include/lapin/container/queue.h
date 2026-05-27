/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** Bibliotheque Lapin
*/

/*!
** \file queue.h
** First-in, first-out container storing raw data pointers.
**
** A queue owns its internal nodes but not the data pointers stored inside.
** Push operations append at the back and pop operations remove from the front.
*/

#ifndef				__LAPIN_QUEUE_H__
# define			__LAPIN_QUEUE_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif

/*!
** The handy structure to represent your queue.
*/
/**
 * @doc
 * @doc-symbol t_bunny_queue
 * @doc-kind type
 * @doc-module queue
 * @doc-order 100
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Represents a heap-allocated first-in, first-out queue.
 * @see bunny_new_queue, bunny_delete_queue
 *
 * @doc-lang fr
 * @brief Représente une file FIFO allouée sur le tas.
 * @see bunny_new_queue, bunny_delete_queue
 */
typedef struct			s_bunny_queue
{
  const size_t			length;
  const void * const * const	front;
  const void * const * const	back;
}				t_bunny_queue;

/*!
** Create a new queue.
** Return null on failure.
*/
/**
 * @doc
 * @doc-symbol bunny_new_queue
 * @doc-kind function
 * @doc-module queue
 * @doc-order 120
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Creates an empty queue.
 * @return-success Returns the newly allocated queue.
 * @return-failure Returns $CNULL@ if allocation fails.
 * @see t_bunny_queue, bunny_delete_queue
 *
 * @doc-lang fr
 * @brief Crée une file vide.
 * @return-success Renvoie la file nouvellement allouée.
 * @return-failure Renvoie $CNULL@ si l'allocation échoue.
 * @see t_bunny_queue, bunny_delete_queue
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
/**
 * @doc
 * @doc-symbol bunny_queue_size
 * @doc-kind function
 * @doc-module queue
 * @doc-order 140
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Returns the number of elements in a queue.
 * @param queue The queue to inspect.
 * @return-success Returns the queue size.
 * @see t_bunny_queue
 *
 * @doc-lang fr
 * @brief Renvoie le nombre d'éléments d'une file.
 * @param queue La file à inspecter.
 * @return-success Renvoie la taille de la file.
 * @see t_bunny_queue
 */
# define			bunny_queue_size(queue)			((queue)->length)

/*!
** Test if the queue is empty.
** \param queue The queue to test
** \return True if it is empty
*/
/**
 * @doc
 * @doc-symbol bunny_queue_empty
 * @doc-kind function
 * @doc-module queue
 * @doc-order 150
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Tests whether a queue is empty.
 * @param queue The queue to inspect.
 * @return-success Returns $Ctrue@ if the queue is empty.
 * @see t_bunny_queue
 *
 * @doc-lang fr
 * @brief Teste si une file est vide.
 * @param queue La file à inspecter.
 * @return-success Renvoie $Ctrue@ si la file est vide.
 * @see t_bunny_queue
 */
# define			bunny_queue_empty(queue)		(!(queue)->length)

/*!
** Get the element at the top of the queue
** \param queue The queue to get the top element
** \param type The type of the element at the top
** \return The data at the top, NULL if there is none
*/
/**
 * @doc
 * @doc-symbol bunny_queue_front
 * @doc-kind function
 * @doc-module queue
 * @doc-order 160
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Returns the front element without removing it.
 * @param queue The queue to inspect.
 * @param type The expected type of the stored pointer.
 * @return-success Returns the typed front pointer, or $CNULL@ if the queue is empty.
 * @see t_bunny_queue
 *
 * @doc-lang fr
 * @brief Renvoie l'élément en tête sans le retirer.
 * @param queue La file à inspecter.
 * @param type Le type attendu du pointeur stocké.
 * @return-success Renvoie le pointeur typé de tête, ou $CNULL@ si la file est vide.
 * @see t_bunny_queue
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
/**
 * @doc
 * @doc-symbol bunny_queue_push
 * @doc-kind function
 * @doc-module queue
 * @doc-order 180
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Pushes an element at the back of a queue.
 * @param qu The queue to edit.
 * @param da The data pointer to store.
 * @return-success Returns $Ctrue@ on success.
 * @see t_bunny_queue
 *
 * @doc-lang fr
 * @brief Ajoute un élément à la fin d'une file.
 * @param qu La file à modifier.
 * @param da Le pointeur de donnée à stocker.
 * @return-success Renvoie $Ctrue@ en cas de succès.
 * @see t_bunny_queue
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
/**
 * @doc
 * @doc-symbol bunny_queue_pop
 * @doc-kind function
 * @doc-module queue
 * @doc-order 200
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Removes and returns the front element.
 * @param qu The queue to edit.
 * @param ty The expected returned pointer type.
 * @return-success Returns the typed data pointer, or $CNULL@ if the queue is empty.
 * @see t_bunny_queue
 *
 * @doc-lang fr
 * @brief Retire et renvoie l'élément en tête.
 * @param qu La file à modifier.
 * @param ty Le type attendu du pointeur renvoyé.
 * @return-success Renvoie le pointeur de donnée typé, ou $CNULL@ si la file est vide.
 * @see t_bunny_queue
 */
# define			bunny_queue_pop(qu, ty)			(ty)_bunny_queue_pop(qu)

#endif	/*			__LAPIN_QUEUE_H__			*/
