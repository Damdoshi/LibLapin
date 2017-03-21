/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** Bibliotheque Lapin
*/

/*!
** \file list.h
**
**
**
*/

#ifndef				__LAPIN_LIST_H__
# define			__LAPIN_LIST_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif

/*!
** The handy structure to represent an element of your list.
*/
typedef struct			s_bunny_node
{
  void *			data;
  struct s_bunny_node * const	next;
  struct s_bunny_node * const	prev;
}				t_bunny_node;

/*!
** The handy structure to represent your list.
*/
typedef struct			s_bunny_list
{
  const size_t			length;
  t_bunny_node * const		front;
  t_bunny_node * const		back;
}				t_bunny_list;

/*!
** Create a new list.
** Return null on failure.
*/
# define			bunny_new_list()			\
  ((t_bunny_list*)bunny_calloc(1, sizeof(t_bunny_list)))

/*!
** Delete the list.
** \param list The list to destroy
** \return How many elements was in list
*/
size_t				bunny_delete_list(t_bunny_list		*list);

/*!
** Get how many elements there is in the list.
** \param list The list to get the length
** \return The list size as size_t
*/
# define			bunny_list_size(list)			((list)->length)

/*!
** Test if the list is empty.
** \param list The list to test
** \return True if it is empty
*/
# define			bunny_list_empty(list)			(!(list)->length)

/*!
** Get the element at the front of the list
** \param list The list to get the top element
** \param type The type of the element at the top
** \return The data at the top, NULL if there is none
*/
# define			bunny_list_front(list, type)		((list)->front ? ((type)(list)->front->data) : (type)NULL)

/*!
** Get the element at the back of the list
** \param list The list to get the top element
** \param type The type of the element at the top
** \return The data at the top, NULL if there is none
*/
# define			bunny_list_back(list, type)		((list)->back ? ((type)(list)->back->data) : (type)NULL)

/*!
** Push an element at the front of the list
** \param list The list to edit
** \param data The data to list
** \return True if everything went well
*/
bool				_bunny_list_push_front(t_bunny_list	*list,
						       const void	*data);

/*!
** Push an element at the front of the list
** \param list The list to edit
** \param data The data to list
** \return True if everything went well
*/
# define			bunny_list_push_front(lst, dat)		_bunny_list_push_front(lst, (void*)(size_t)(dat))

/*!
** Push an element at the back of the list
** \param list The list to edit
** \param data The data to list
** \return True if everything went well
*/
bool				_bunny_list_push_back(t_bunny_list	*list,
						      const void	*data);

/*!
** Push an element at the front of the list
** \param list The list to edit
** \param data The data to list
** \return True if everything went well

*/
# define			bunny_list_push_back(lst, dat)		_bunny_list_push_back(lst, (void*)(size_t)(dat))


/*!
** Remove the element at the front of the list.
** \param list The list to edit
** \return The data that was listed, NULL if there was none.
*/
void				*_bunny_list_pop_front(t_bunny_list	*list);

/*!
** Remove the element at the front of the list and get it
** \param lst The list to edit
** \param ty The type of the retrieved element
** \return The data that was listed, NULL if there was none.
*/
# define			bunny_list_pop_front(lst, ty)		(ty)_bunny_list_pop_front(lst)

/*!
** Remove the element at the front of the list.
** \param list The list to edit
** \return The data that was listed, NULL if there was none.
*/
void				*_bunny_list_pop_back(t_bunny_list	*list);

/*!
** Remove the element at the front of the list and get it
** \param lst The list to edit
** \param ty The type of the retrieved element
** \return The data that was listed, NULL if there was none.
*/
# define			bunny_list_pop_back(lst, ty)		(ty)_bunny_list_pop_back(lst)

/*!
** Empty the whole list.
** \param lst The list to empty
*/
# define			bunny_list_clear(lst)			\
  while (bunny_list_size(lst)) bunny_list_pop_back(lst, void*)

/*!
** Return a sublist filled with elements that makes the filter function pointer
** return true.
** \param list The source list
** \param filter A function pointer that will receive a data from the source list
**        and the param parameter, which can be anything you want.
** \param A pointer that will be send to filter as second parameter.
** \return A sublist filled with matching data, NULL on error.
*/
t_bunny_list			*bunny_list_filter(t_bunny_list		*list,
						   bool			(*filter)
						   (const void		*listed,
						    void		*param),
						   void			*param);

/*!
** Sort the sent list accordingly to the compare function.
** \param list The source list
** \param cmp A function pointer that will compare its first param to
**        the second. Works like strcmp.
** \param A pointer that will be send to cmp as third parameter.
*/
void				bunny_list_sort(t_bunny_list		*list,
						int			(*cmp)
						(const void		*a,
						 const void		*b,
						 void			*param),
						void			*param);

/*!
** Get the data inside the node with the correct type.
** \param node A t_bunny_node pointer
** \param type The type of the data that is contained by the node
** \return The data inside the node with the correct type
*/
# define			bunny_list_data(node, type)		(*((type*)&(node)->data))

/*!
** Return an iterator to the first element of the list.
** \param list The list to iterate on
** \return The first node. NULL if the list is empty.
*/
# define			bunny_list_begin(list)			((t_bunny_node*)(list)->front)

/*!
** Return an iterator to the last element of the list.
** \param list The list to iterate on
** \return The last node. NULL if the list is empty.
*/
# define			bunny_list_end(list)			((t_bunny_node*)(list)->back)

/*!
** Return the next node of the list
** \param node The node we want the next
** \return The next node. NULL if it was the last.
*/
# define			bunny_list_next(node)			((t_bunny_node*)(node)->next)

/*!
** Return the previous node of the list
** \param node The node we want the previous
** \return The previous node. NULL if it was the first.
*/
# define			bunny_list_prev(node)			((t_bunny_node*)(node)->prev)

struct s_bunny_vector;

/*!
** Put all data inside the sent list into a vector of elemsize chunk.
** Chunks are copied with memcpy.
** \param list The list to transform
** \param elemsize The size in byte of elements inside list
** \return A vector that contains duplicated datas from the list, in the
**         the same order.
*/
struct s_bunny_vector		*_bunny_list_tie(const t_bunny_list	*list,
						size_t			elemsize);

/*!
** Pull all data inside the sent list (that must be a list of the sent type) into
** a vector of the sent type. Chunks are copied with memcpy.
** \param lst The list to transform
** \param typ The type of elements in list
** \return A vector that contains duplicated datas from the list, in the
**         same order.
*/
# define			bunny_list_tie(lst, typ)		_bunny_list_tie(lst, sizeof(typ))

typedef void			(*t_bunny_list_foreach)(void		*node,
							void		*param);

/*!
** Apply a function on every nodes in the list.
** \param lst The list to edit
** \param nod A free to use t_bunny_node.
** \param func A t_bunny_list_foreach function
** \param par A parameter that will be sent as second parameter of func
*/
# define			bunny_list_foreach(lst, nod, func, par)	\
  for (nod = bunny_list_begin(lst);					\
       nod != NULL;							\
       nod = bunny_list_next(nod))					\
    func(bunny_list_data(nod, void*), (void*)par);

/*!
** Apply a function on every nodes in the list with multiple threads.
** \param pool The thread pool that will share its threads
** \param list The list to edit
** \param func The function to apply
** \param param The second parameter sent to func
** \return False to notice you an error happened with threads: all datas
**         were not treated by threads, some of them were treated by the
**         main thread because of thread pool memory exhaustion.
**         True if all was ok.
**
** You should use bunny_thread_wait_completion at the end of your thread cycle.
*/
bool				bunny_list_fast_foreach(t_bunny_threadpool *pool,
							t_bunny_list	*list,
							 void		(*func)
							(void		*nod,
							 const void	*param),
							const void	*param);

/*!
** Browse a list in the direct order.
** To be used in a for statement, giving a t_bunny_list* and a t_bunny_node*
** as parameter:
** t_bunny_list *lts = get_list();
** t_bunny_node *nod;
**
** for (bunny_list_all(lst, nod))
** { ... }
**
** \param lst The list to browse
** \param nod The node to use inside the for loop
*/
# define			bunny_list_all(lst, nod)		\
  nod = bunny_list_begin(lst); nod != NULL; nod = bunny_list_next(nod)

/*!
** Browse a list in the reverse order.
** To be used in a for statement, giving a t_bunny_list* and a t_bunny_node*
** as parameter:
** t_bunny_list *lts = get_list();
** t_bunny_node *nod;
**
** for (bunny_list_all_rev(lst, nod))
** { ... }
**
** \param lst The list to browse
** \param nod The node to use inside the for loop
*/
# define			bunny_list_all_rev(lst, nod)		\
  nod = bunny_list_end(lst); nod != NULL; nod = bunny_list_prev(nod)

#endif	/*			__LAPIN_LIST_H__			*/

