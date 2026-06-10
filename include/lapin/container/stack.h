/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** Bibliotheque Lapin
*/

/*!
** \file stack.h
** Last-in, first-out container storing raw data pointers.
**
** A stack owns its internal nodes but not the data pointers stored inside.
** Push and pop operations affect the top of the stack.
*/

#ifndef				__LAPIN_STACK_H__
# define			__LAPIN_STACK_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif

/*!
** The handy structure to represent your stack.
*/
/**
 * @doc
 * @doc-symbol t_bunny_stack
 * @doc-kind type
 * @doc-module stack
 * @doc-order 50
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Represents a heap-allocated last-in, first-out stack.
 * @see bunny_new_stack, bunny_delete_stack
 *
 * @doc-lang fr
 * @brief Représente une pile LIFO allouée sur le tas.
 * @see bunny_new_stack, bunny_delete_stack
 */
typedef struct			s_bunny_stack
{
  const size_t			length;
  const void * const * const	top;
}				t_bunny_stack;

/*!
** Create a new stack.
** Return null on failure.
** \return A t_bunny_stack
*/
/**
 * @doc
 * @doc-symbol bunny_new_stack
 * @doc-kind function
 * @doc-module stack
 * @doc-order 120
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Creates an empty stack.
 * @return-success Returns the newly allocated stack.
 * @return-failure Returns $CNULL@ if allocation fails.
 * @see t_bunny_stack, bunny_delete_stack
 *
 * @doc-lang fr
 * @brief Crée une pile vide.
 * @return-success Renvoie la pile nouvellement allouée.
 * @return-failure Renvoie $CNULL@ si l'allocation échoue.
 * @see t_bunny_stack, bunny_delete_stack
 */
# define			bunny_new_stack()			\
  ((t_bunny_stack*)bunny_calloc(1, sizeof(t_bunny_stack)))

/*!
** Delete the stack.
** \param stack The stack to destroy
** \return How many elements was in stack
*/
size_t				bunny_delete_stack(t_bunny_stack	*stack);

/*!
** Get how many elements there is in the stack.
** \param stack The stack to get the length
** \return The stack size in size_t
*/
/**
 * @doc
 * @doc-symbol bunny_stack_size
 * @doc-kind function
 * @doc-module stack
 * @doc-order 140
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Returns the number of elements in a stack.
 * @param stack The stack to inspect.
 * @return-success Returns the stack size.
 * @see t_bunny_stack
 *
 * @doc-lang fr
 * @brief Renvoie le nombre d'éléments d'une pile.
 * @param stack La pile à inspecter.
 * @return-success Renvoie la taille de la pile.
 * @see t_bunny_stack
 */
# define			bunny_stack_size(stack)			\
  ((stack)->length)

/*!
** Test if the stack is empty.
** \param stack The stack to test
** \return True if it is empty
*/
/**
 * @doc
 * @doc-symbol bunny_stack_empty
 * @doc-kind function
 * @doc-module stack
 * @doc-order 150
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Tests whether a stack is empty.
 * @param stack The stack to inspect.
 * @return-success Returns $Ctrue@ if the stack is empty.
 * @see t_bunny_stack
 *
 * @doc-lang fr
 * @brief Teste si une pile est vide.
 * @param stack La pile à inspecter.
 * @return-success Renvoie $Ctrue@ si la pile est vide.
 * @see t_bunny_stack
 */
# define			bunny_stack_empty(stack)		\
  (!(stack)->length)

/*!
** Get the element at the top of the stack
** \param stack The stack to get the top element
** \param type The type of the element at the top
** \return The data at the top, NULL if there is none
*/
/**
 * @doc
 * @doc-symbol bunny_stack_top
 * @doc-kind function
 * @doc-module stack
 * @doc-order 160
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Returns the top element without removing it.
 * @param stack The stack to inspect.
 * @param type The expected type of the stored pointer.
 * @return-success Returns the typed top pointer, or $CNULL@ if the stack is empty.
 * @see t_bunny_stack
 *
 * @doc-lang fr
 * @brief Renvoie l'élément au sommet sans le retirer.
 * @param stack La pile à inspecter.
 * @param type Le type attendu du pointeur stocké.
 * @return-success Renvoie le pointeur typé du sommet, ou $CNULL@ si la pile est vide.
 * @see t_bunny_stack
 */
# define			bunny_stack_top(stack, type)		\
  ((stack)->top ? *((type*)(stack)->top) : (type)NULL)

/*!
** Push an element on the top of the stack
** \param stack The stack to edit
** \param data The data to stack
** \return True if everything went well
*/
bool				_bunny_stack_push(t_bunny_stack		*stack,
						  const void		*data);

/*!
** Push an element on the top of the stack
** \param st The stack to edit
** \param da The data to stack
** \return True if everything went well
*/
/**
 * @doc
 * @doc-symbol bunny_stack_push
 * @doc-kind function
 * @doc-module stack
 * @doc-order 180
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Pushes an element on top of a stack.
 * @param st The stack to edit.
 * @param da The data pointer to store.
 * @return-success Returns $Ctrue@ on success.
 * @see t_bunny_stack
 *
 * @doc-lang fr
 * @brief Empile un élément au sommet d'une pile.
 * @param st La pile à modifier.
 * @param da Le pointeur de donnée à stocker.
 * @return-success Renvoie $Ctrue@ en cas de succès.
 * @see t_bunny_stack
 */
# define			bunny_stack_push(st, da)		\
  _bunny_stack_push(st, (void*)(size_t)da)

/*!
** Remove the element at the top of the stack.
** \param stack The stack to edit
** \return The data that was stacked, NULL if there was none.
*/
void				*_bunny_stack_pop(t_bunny_stack		*stack);

/*!
** Remove the element at the top of the stack and get it
** \param st The stack to edit
** \param ty The type of the extracted data
** \return The data that was stacked, NULL if there was none.
*/
/**
 * @doc
 * @doc-symbol bunny_stack_pop
 * @doc-kind function
 * @doc-module stack
 * @doc-order 200
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Removes and returns the top element.
 * @param st The stack to edit.
 * @param ty The expected returned pointer type.
 * @return-success Returns the typed data pointer, or $CNULL@ if the stack is empty.
 * @see t_bunny_stack
 *
 * @doc-lang fr
 * @brief Retire et renvoie l'élément au sommet.
 * @param st La pile à modifier.
 * @param ty Le type attendu du pointeur renvoyé.
 * @return-success Renvoie le pointeur de donnée typé, ou $CNULL@ si la pile est vide.
 * @see t_bunny_stack
 */
# define			bunny_stack_pop(st, ty)			\
  (ty)_bunny_stack_pop(st)

#endif	/*			__LAPIN_STACK_H__			*/
