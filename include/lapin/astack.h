/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** Bibliotheque Lapin
*/

/*!
** \file astack.h
** The astack container is a fully automatic container
** that use alloca to get its memory. Its purpose is to avoid
** memory allocation when you need a fast storage without
** any needs for complex manipulators.
*/

#ifndef				__LAPIN_ASTACK_H__
# define			__LAPIN_ASTACK_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif
# ifndef			__ANSI__
#  include			<string.h>
#  include			<alloca.h>
#  include			"stack.h"

/*!
** Structure pushed by bunny_astack_push on t_bunny_astack
*/
typedef struct			s_bunny_astack_node
{
  void				*data;
  struct s_bunny_astack_node	*next;
}				t_bunny_astack_node;

typedef t_bunny_stack		t_bunny_astack;

/*!
** Create a stack on the stack.
** Pay attention: it will disappeir at the end of the function
** (not at the end of the scope)
** \return A t_bunny_astack, which is a t_bunny_stack
*/
# define			bunny_new_astack()			\
  (t_bunny_stack*)memset						\
  (alloca(sizeof(t_bunny_stack)), 0, sizeof(t_bunny_stack))

/*!
** Get how many elements there is in the stack.
** \param stack The stack to get the length
** \return The stack size in size_t
*/
# define			bunny_astack_size(astack)	\
  bunny_stack_size(astack)

/*!
** Test if the stack is empty.
** \param stack The stack to test
** \return True if it is empty
*/
# define			bunny_astack_empty(astack)		\
  bunny_stack_empty(astack)

/*!
** Get the element at the top of the stack
** \param stack The stack to get the top element
** \param type The type of the element at the top
** \return The data at the top, NULL if there is none
*/
# define			bunny_astack_top(astack, type)		\
  bunny_stack_top(astack, type)

/*!
** Push a data on stack with a stack allocated node.
** Please, use this function only with t_bunny_astack and avoid
** to put allocation on heap ONLY on this stack:
** These nodes will disappeir with local variable at the end of
** the function (not at the end of the scope).
** \param st A t_bunny_astack
*/
# define			bunny_astack_push(st, da)		\
  do									\
    {									\
      t_bunny_astack_node *__nod = alloca(sizeof(*__nod));		\
									\
      __nod->data = (void*)da;						\
      __nod->next = (t_bunny_astack_node*)(st)->top;			\
      *(void**)&(st)->top = (void*)__nod;				\
      *(size_t*)&(st)->length += 1;					\
    }									\
  while (0)

/*!
** Remove the element at the top of the stack
** It does NOT return it like the bunny_stack_pop function.
** \param st The stack to edit
*/
# define			bunny_astack_pop(st)			\
  do									\
    {									\
      *(t_bunny_astack_node**)&(st)->top) =				\
	((t_bunny_astack_node*)(st)->top)->next;			\
      *(size_t*)&(st)->length -= 1;					\
    }									\
  while (0)

# endif
#endif	/*			__LAPIN_ASTACK_H__			*/
