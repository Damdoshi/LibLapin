/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** Bibliotheque Lapin
*/

/*!
** \file stack.h
**
**
**
*/

#ifndef				__LAPIN_STACK_H__
# define			__LAPIN_STACK_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif

/*!
** The handy structure to represent your stack.
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
# define			bunny_stack_size(stack)			\
  ((stack)->length)

/*!
** Test if the stack is empty.
** \param stack The stack to test
** \return True if it is empty
*/
# define			bunny_stack_empty(stack)		\
  (!(stack)->length)

/*!
** Get the element at the top of the stack
** \param stack The stack to get the top element
** \param type The type of the element at the top
** \return The data at the top, NULL if there is none
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
** \param stack The stack to edit
** \param data The data to stack
** \return True if everything went well
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
# define			bunny_stack_pop(st, ty)			\
  (ty)_bunny_stack_pop(st)

#endif	/*			__LAPIN_STACK_H__			*/
