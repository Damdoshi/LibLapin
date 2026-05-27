/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** Bibliotheque Lapin
*/

/*!
** \file list.h
** Doubly linked list storing raw data pointers.
**
** A list owns its internal nodes but not the data pointers stored inside.
** It can be browsed from front to back or from back to front with its iterator
** macros.
*/

#ifndef				__LAPIN_LIST_H__
# define			__LAPIN_LIST_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif

/*!
** The handy structure to represent an element of your list.
*/
/**
 * @doc
 * @doc-symbol t_bunny_node
 * @doc-kind type
 * @doc-module list
 * @doc-order 100
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Represents one node of a doubly linked list.
 * @see t_bunny_list, bunny_list_begin
 *
 * @doc-lang fr
 * @brief Représente un nœud d'une liste doublement chaînée.
 * @see t_bunny_list, bunny_list_begin
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
/**
 * @doc
 * @doc-symbol t_bunny_list
 * @doc-kind type
 * @doc-module list
 * @doc-order 120
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Represents a doubly linked list.
 * @see bunny_new_list, bunny_delete_list
 *
 * @doc-lang fr
 * @brief Représente une liste doublement chaînée.
 * @see bunny_new_list, bunny_delete_list
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
/**
 * @doc
 * @doc-symbol bunny_new_list
 * @doc-kind function
 * @doc-module list
 * @doc-order 140
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Creates an empty list.
 * @return-success Returns the newly allocated list.
 * @return-failure Returns $CNULL@ if allocation fails.
 * @see t_bunny_list, bunny_delete_list
 *
 * @doc-lang fr
 * @brief Crée une liste vide.
 * @return-success Renvoie la liste nouvellement allouée.
 * @return-failure Renvoie $CNULL@ si l'allocation échoue.
 * @see t_bunny_list, bunny_delete_list
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
/**
 * @doc
 * @doc-symbol bunny_list_size
 * @doc-kind function
 * @doc-module list
 * @doc-order 180
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Returns the number of elements in a list.
 * @param list The list to inspect.
 * @return-success Returns the list size.
 * @see t_bunny_list, t_bunny_node
 *
 * @doc-lang fr
 * @brief Renvoie le nombre d'éléments d'une liste.
 * @param list La liste à inspecter.
 * @return-success Renvoie la taille de la liste.
 * @see t_bunny_list, t_bunny_node
 */
# define			bunny_list_size(list)			((list)->length)

/*!
** Test if the list is empty.
** \param list The list to test
** \return True if it is empty
*/
/**
 * @doc
 * @doc-symbol bunny_list_empty
 * @doc-kind function
 * @doc-module list
 * @doc-order 200
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Tests whether a list is empty.
 * @param list The list to inspect.
 * @return-success Returns $Ctrue@ if the list is empty.
 * @see t_bunny_list, t_bunny_node
 *
 * @doc-lang fr
 * @brief Teste si une liste est vide.
 * @param list La liste à inspecter.
 * @return-success Renvoie $Ctrue@ si la liste est vide.
 * @see t_bunny_list, t_bunny_node
 */
# define			bunny_list_empty(list)			(!(list)->length)

/*!
** Get the element at the front of the list
** \param list The list to get the top element
** \param type The type of the element at the top
** \return The data at the top, NULL if there is none
*/
/**
 * @doc
 * @doc-symbol bunny_list_front
 * @doc-kind function
 * @doc-module list
 * @doc-order 220
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Returns the front element without removing it.
 * @param list The list to inspect.
 * @param type The expected type of the stored pointer.
 * @return-success Returns the typed front pointer, or $CNULL@ if the list is empty.
 * @see t_bunny_list, t_bunny_node
 *
 * @doc-lang fr
 * @brief Renvoie l'élément en tête sans le retirer.
 * @param list La liste à inspecter.
 * @param type Le type attendu du pointeur stocké.
 * @return-success Renvoie le pointeur typé de tête, ou $CNULL@ si la liste est vide.
 * @see t_bunny_list, t_bunny_node
 */
# define			bunny_list_front(list, type)		((list)->front ? ((type)(list)->front->data) : (type)NULL)

/*!
** Get the element at the back of the list
** \param list The list to get the top element
** \param type The type of the element at the top
** \return The data at the top, NULL if there is none
*/
/**
 * @doc
 * @doc-symbol bunny_list_back
 * @doc-kind function
 * @doc-module list
 * @doc-order 240
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Returns the back element without removing it.
 * @param list The list to inspect.
 * @param type The expected type of the stored pointer.
 * @return-success Returns the typed back pointer, or $CNULL@ if the list is empty.
 * @see t_bunny_list, t_bunny_node
 *
 * @doc-lang fr
 * @brief Renvoie l'élément en queue sans le retirer.
 * @param list La liste à inspecter.
 * @param type Le type attendu du pointeur stocké.
 * @return-success Renvoie le pointeur typé de queue, ou $CNULL@ si la liste est vide.
 * @see t_bunny_list, t_bunny_node
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
/**
 * @doc
 * @doc-symbol bunny_list_push_front
 * @doc-kind function
 * @doc-module list
 * @doc-order 260
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Pushes an element at the front of a list.
 * @param lst The list to edit.
 * @param dat The data pointer to store.
 * @return-success Returns $Ctrue@ on success.
 * @see t_bunny_list, t_bunny_node
 *
 * @doc-lang fr
 * @brief Ajoute un élément en tête d'une liste.
 * @param lst La liste à modifier.
 * @param dat Le pointeur de donnée à stocker.
 * @return-success Renvoie $Ctrue@ en cas de succès.
 * @see t_bunny_list, t_bunny_node
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
/**
 * @doc
 * @doc-symbol bunny_list_push_back
 * @doc-kind function
 * @doc-module list
 * @doc-order 280
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Pushes an element at the back of a list.
 * @param lst The list to edit.
 * @param dat The data pointer to store.
 * @return-success Returns $Ctrue@ on success.
 * @see t_bunny_list, t_bunny_node
 *
 * @doc-lang fr
 * @brief Ajoute un élément en queue d'une liste.
 * @param lst La liste à modifier.
 * @param dat Le pointeur de donnée à stocker.
 * @return-success Renvoie $Ctrue@ en cas de succès.
 * @see t_bunny_list, t_bunny_node
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
/**
 * @doc
 * @doc-symbol bunny_list_pop_front
 * @doc-kind function
 * @doc-module list
 * @doc-order 300
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Removes and returns the front element.
 * @param lst The list to edit.
 * @param ty The expected returned pointer type.
 * @return-success Returns the typed data pointer, or $CNULL@ if the list is empty.
 * @see t_bunny_list, t_bunny_node
 *
 * @doc-lang fr
 * @brief Retire et renvoie l'élément en tête.
 * @param lst La liste à modifier.
 * @param ty Le type attendu du pointeur renvoyé.
 * @return-success Renvoie le pointeur de donnée typé, ou $CNULL@ si la liste est vide.
 * @see t_bunny_list, t_bunny_node
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
/**
 * @doc
 * @doc-symbol bunny_list_pop_back
 * @doc-kind function
 * @doc-module list
 * @doc-order 320
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Removes and returns the back element.
 * @param lst The list to edit.
 * @param ty The expected returned pointer type.
 * @return-success Returns the typed data pointer, or $CNULL@ if the list is empty.
 * @see t_bunny_list, t_bunny_node
 *
 * @doc-lang fr
 * @brief Retire et renvoie l'élément en queue.
 * @param lst La liste à modifier.
 * @param ty Le type attendu du pointeur renvoyé.
 * @return-success Renvoie le pointeur de donnée typé, ou $CNULL@ si la liste est vide.
 * @see t_bunny_list, t_bunny_node
 */
# define			bunny_list_pop_back(lst, ty)		(ty)_bunny_list_pop_back(lst)

/*!
** Empty the whole list.
** \param lst The list to empty
*/
/**
 * @doc
 * @doc-symbol bunny_list_clear
 * @doc-kind function
 * @doc-module list
 * @doc-order 340
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Removes every node from a list.
 * @param lst The list to empty.
 * @return-success This macro does not return a value.
 * @see t_bunny_list, t_bunny_node
 *
 * @doc-lang fr
 * @brief Retire tous les nœuds d'une liste.
 * @param lst La liste à vider.
 * @return-success Cette macro ne renvoie pas de valeur.
 * @see t_bunny_list, t_bunny_node
 */
# define			bunny_list_clear(lst)			\
  while (bunny_list_size(lst)) bunny_list_pop_back(lst, void*)

/*!
** Return a sublist filled with elements that makes the filter function pointer
** return true.
** \param list The source list
** \param filter A function pointer that will receive a data from the source list
**        and the param parameter, which can be anything you want.
** \param param A pointer that will be send to filter as second parameter.
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
** \param param A pointer that will be send to cmp as third parameter.
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
/**
 * @doc
 * @doc-symbol bunny_list_data
 * @doc-kind function
 * @doc-module list
 * @doc-order 400
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Reads the data stored in a list node with the requested type.
 * @param node The node to inspect.
 * @param type The expected stored pointer type.
 * @return-success Returns the data stored in the node.
 * @see t_bunny_list, t_bunny_node
 *
 * @doc-lang fr
 * @brief Lit la donnée stockée dans un nœud de liste avec le type demandé.
 * @param node Le nœud à inspecter.
 * @param type Le type attendu du pointeur stocké.
 * @return-success Renvoie la donnée stockée dans le nœud.
 * @see t_bunny_list, t_bunny_node
 */
# define			bunny_list_data(node, type)		(*((type*)&(node)->data))

/*!
** Return an iterator to the first element of the list.
** \param list The list to iterate on
** \return The first node. NULL if the list is empty.
*/
/**
 * @doc
 * @doc-symbol bunny_list_begin
 * @doc-kind function
 * @doc-module list
 * @doc-order 420
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Returns the first node of a list.
 * @param list The list to browse.
 * @return-success Returns the first node, or $CNULL@ if the list is empty.
 * @see t_bunny_list, t_bunny_node
 *
 * @doc-lang fr
 * @brief Renvoie le premier nœud d'une liste.
 * @param list La liste à parcourir.
 * @return-success Renvoie le premier nœud, ou $CNULL@ si la liste est vide.
 * @see t_bunny_list, t_bunny_node
 */
# define			bunny_list_begin(list)			((t_bunny_node*)(list)->front)

/*!
** Return an iterator to the last element of the list.
** \param list The list to iterate on
** \return The last node. NULL if the list is empty.
*/
/**
 * @doc
 * @doc-symbol bunny_list_end
 * @doc-kind function
 * @doc-module list
 * @doc-order 440
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Returns the last node of a list.
 * @param list The list to browse.
 * @return-success Returns the last node, or $CNULL@ if the list is empty.
 * @see t_bunny_list, t_bunny_node
 *
 * @doc-lang fr
 * @brief Renvoie le dernier nœud d'une liste.
 * @param list La liste à parcourir.
 * @return-success Renvoie le dernier nœud, ou $CNULL@ si la liste est vide.
 * @see t_bunny_list, t_bunny_node
 */
# define			bunny_list_end(list)			((t_bunny_node*)(list)->back)

/*!
** Return the next node of the list
** \param node The node we want the next
** \return The next node. NULL if it was the last.
*/
/**
 * @doc
 * @doc-symbol bunny_list_next
 * @doc-kind function
 * @doc-module list
 * @doc-order 460
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Returns the next node.
 * @param node The current node.
 * @return-success Returns the next node, or $CNULL@ at the end.
 * @see t_bunny_list, t_bunny_node
 *
 * @doc-lang fr
 * @brief Renvoie le nœud suivant.
 * @param node Le nœud courant.
 * @return-success Renvoie le nœud suivant, ou $CNULL@ à la fin.
 * @see t_bunny_list, t_bunny_node
 */
# define			bunny_list_next(node)			((t_bunny_node*)(node)->next)

/*!
** Return the previous node of the list
** \param node The node we want the previous
** \return The previous node. NULL if it was the first.
*/
/**
 * @doc
 * @doc-symbol bunny_list_prev
 * @doc-kind function
 * @doc-module list
 * @doc-order 480
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Returns the previous node.
 * @param node The current node.
 * @return-success Returns the previous node, or $CNULL@ at the beginning.
 * @see t_bunny_list, t_bunny_node
 *
 * @doc-lang fr
 * @brief Renvoie le nœud précédent.
 * @param node Le nœud courant.
 * @return-success Renvoie le nœud précédent, ou $CNULL@ au début.
 * @see t_bunny_list, t_bunny_node
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
/**
 * @doc
 * @doc-symbol bunny_list_tie
 * @doc-kind function
 * @doc-module list
 * @doc-order 500
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Copies list data into a vector of the requested element type.
 * @param lst The list to transform.
 * @param typ The element type to copy.
 * @return-success Returns a vector containing copied data in the same order.
 * @see t_bunny_list, t_bunny_node
 *
 * @doc-lang fr
 * @brief Copie les données d'une liste dans un vecteur du type demandé.
 * @param lst La liste à transformer.
 * @param typ Le type d'élément à copier.
 * @return-success Renvoie un vecteur contenant les données copiées dans le même ordre.
 * @see t_bunny_list, t_bunny_node
 */
# define			bunny_list_tie(lst, typ)		\
  _bunny_list_tie(lst, sizeof(typ))

/**
 * @doc
 * @doc-symbol t_bunny_list_foreach
 * @doc-kind type
 * @doc-module list
 * @doc-order 520
 * @doc-since 11
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Defines the callback used to traverse a list.
 * @param node The current listed data pointer.
 * @param param The user pointer forwarded by traversal.
 * @see bunny_list_foreach, bunny_list_fast_foreach
 *
 * @doc-lang fr
 * @brief Définit le callback utilisé pour parcourir une liste.
 * @param node Le pointeur de donnée courant.
 * @param param Le pointeur utilisateur transmis par le parcours.
 * @see bunny_list_foreach, bunny_list_fast_foreach
 */
typedef void			(*t_bunny_list_foreach)(void		*node,
							void		*param);

/*!
** Apply a function on every nodes in the list.
** \param lst The list to edit
** \param func A t_bunny_list_foreach function
** \param par A parameter that will be sent as second parameter of func
*/
void				bunny_list_foreach(t_bunny_list		*list,
						   t_bunny_list_foreach	func,
						   void			*param);

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
							 void		*param),
							void		*param);

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
/**
 * @doc
 * @doc-symbol bunny_list_all
 * @doc-kind function
 * @doc-module list
 * @doc-order 580
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Builds a for-loop clause that browses a list forward.
 * @param lst The list to browse.
 * @param nod The iterator variable.
 * @return-success This macro expands to the expressions of a $Kfor@ loop.
 * @see t_bunny_list, t_bunny_node
 *
 * @doc-lang fr
 * @brief Construit une clause de boucle for parcourant une liste vers l'avant.
 * @param lst La liste à parcourir.
 * @param nod La variable d'itération.
 * @return-success Cette macro se développe en expressions de boucle $Kfor@.
 * @see t_bunny_list, t_bunny_node
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
/**
 * @doc
 * @doc-symbol bunny_list_all_rev
 * @doc-kind function
 * @doc-module list
 * @doc-order 600
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Builds a for-loop clause that browses a list backward.
 * @param lst The list to browse.
 * @param nod The iterator variable.
 * @return-success This macro expands to the expressions of a $Kfor@ loop.
 * @see t_bunny_list, t_bunny_node
 *
 * @doc-lang fr
 * @brief Construit une clause de boucle for parcourant une liste vers l'arrière.
 * @param lst La liste à parcourir.
 * @param nod La variable d'itération.
 * @return-success Cette macro se développe en expressions de boucle $Kfor@.
 * @see t_bunny_list, t_bunny_node
 */
# define			bunny_list_all_rev(lst, nod)		\
  nod = bunny_list_end(lst); nod != NULL; nod = bunny_list_prev(nod)

#endif	/*			__LAPIN_LIST_H__			*/

