/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** Bibliotheque Lapin
*/

/*!
** \file astack.h
** The astack container is a fully automatic stack container that uses alloca
** to get its memory. Its purpose is to avoid heap allocation when you need a
** fast temporary storage without complex manipulators. Stored data should have
** a lifetime at least as long as the function using the astack.
**
** The astack disappears when the current function returns. Do not return it and
** do not delete it with bunny_delete_stack. Only available on systems that
** support alloca.
*/

#ifndef				__LAPIN_ASTACK_H__
# define			__LAPIN_ASTACK_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif
# if				__GNUC__ || _WIN32 || __WIN32__
#  include			<string.h>
#  include			"stack.h"

/*!
** Structure pushed by bunny_astack_push on t_bunny_astack
*/
/**
 * @doc
 * @doc-symbol t_bunny_astack_node
 * @doc-kind type
 * @doc-module astack
 * @doc-order 100
 * @doc-since 11
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Represents one node of an automatic stack.
 * @description Nodes are allocated with $Sbunny_alloca@ and disappear when the current function returns.
 * @see t_bunny_astack, bunny_astack_push
 *
 * @doc-lang fr
 * @brief Représente un nœud d'une pile automatique.
 * @description Les nœuds sont alloués avec $Sbunny_alloca@ et disparaissent lorsque la fonction courante retourne.
 * @see t_bunny_astack, bunny_astack_push
 */
typedef struct			s_bunny_astack_node
{
  void				*data;
  struct s_bunny_astack_node	*next;
}				t_bunny_astack_node;

/**
 * @doc
 * @doc-symbol t_bunny_astack
 * @doc-kind type
 * @doc-module astack
 * @doc-order 50
 * @doc-since 11
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Represents an automatic stack allocated on the current function stack.
 * @description Do not return an astack and do not delete it with $Sbunny_delete_stack@.
 * @see bunny_new_astack, t_bunny_stack
 *
 * @doc-lang fr
 * @brief Représente une pile automatique allouée sur la pile de la fonction courante.
 * @description Ne renvoyez pas une astack et ne la détruisez pas avec $Sbunny_delete_stack@.
 * @see bunny_new_astack, t_bunny_stack
 */
typedef t_bunny_stack		t_bunny_astack;

/*!
** Create a stack on the stack.
** Pay attention: it will disappeir at the end of the function
** (not at the end of the scope)
** \return A t_bunny_astack, which is a t_bunny_stack
*/
/**
 * @doc
 * @doc-symbol bunny_new_astack
 * @doc-kind function
 * @doc-module astack
 * @doc-order 120
 * @doc-since 11
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Creates an automatic stack.
 * @return-success Returns the automatic stack.
 * @see t_bunny_astack
 *
 * @doc-lang fr
 * @brief Crée une pile automatique.
 * @return-success Renvoie la pile automatique.
 * @see t_bunny_astack
 */
# define			bunny_new_astack()			\
  (t_bunny_stack*)memset						\
  (bunny_alloca(sizeof(t_bunny_stack)), 0, sizeof(t_bunny_stack))

/*!
** Get how many elements there is in the stack.
** \param stack The stack to get the length
** \return The stack size in size_t
*/
/**
 * @doc
 * @doc-symbol bunny_astack_size
 * @doc-kind function
 * @doc-module astack
 * @doc-order 140
 * @doc-since 11
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Returns the number of elements in an automatic stack.
 * @param astack The automatic stack to inspect.
 * @return-success Returns the automatic stack size.
 * @see t_bunny_astack
 *
 * @doc-lang fr
 * @brief Renvoie le nombre d'éléments d'une pile automatique.
 * @param astack La pile automatique à inspecter.
 * @return-success Renvoie la taille de la pile automatique.
 * @see t_bunny_astack
 */
# define			bunny_astack_size(astack)	\
  bunny_stack_size(astack)

/*!
** Test if the stack is empty.
** \param stack The stack to test
** \return True if it is empty
*/
/**
 * @doc
 * @doc-symbol bunny_astack_empty
 * @doc-kind function
 * @doc-module astack
 * @doc-order 150
 * @doc-since 11
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Tests whether an automatic stack is empty.
 * @param astack The automatic stack to inspect.
 * @return-success Returns $Ctrue@ if the automatic stack is empty.
 * @see t_bunny_astack
 *
 * @doc-lang fr
 * @brief Teste si une pile automatique est vide.
 * @param astack La pile automatique à inspecter.
 * @return-success Renvoie $Ctrue@ si la pile automatique est vide.
 * @see t_bunny_astack
 */
# define			bunny_astack_empty(astack)		\
  bunny_stack_empty(astack)

/*!
** Get the element at the top of the stack
** \param stack The stack to get the top element
** \param type The type of the element at the top
** \return The data at the top, NULL if there is none
*/
/**
 * @doc
 * @doc-symbol bunny_astack_top
 * @doc-kind function
 * @doc-module astack
 * @doc-order 160
 * @doc-since 11
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Returns the top element without removing it.
 * @param astack The automatic stack to inspect.
 * @param type The expected type of the stored pointer.
 * @return-success Returns the typed top pointer, or $CNULL@ if the astack is empty.
 * @see t_bunny_astack
 *
 * @doc-lang fr
 * @brief Renvoie l'élément au sommet sans le retirer.
 * @param astack La pile automatique à inspecter.
 * @param type Le type attendu du pointeur stocké.
 * @return-success Renvoie le pointeur typé du sommet, ou $CNULL@ si l'astack est vide.
 * @see t_bunny_astack
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
/**
 * @doc
 * @doc-symbol bunny_astack_push
 * @doc-kind function
 * @doc-module astack
 * @doc-order 180
 * @doc-since 11
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Pushes an element on an automatic stack.
 * @param st The automatic stack to edit.
 * @param da The data pointer to store.
 * @return-success This macro does not return a value.
 * @see t_bunny_astack
 *
 * @doc-lang fr
 * @brief Empile un élément dans une pile automatique.
 * @param st La pile automatique à modifier.
 * @param da Le pointeur de donnée à stocker.
 * @return-success Cette macro ne renvoie pas de valeur.
 * @see t_bunny_astack
 */
# define			bunny_astack_push(st, da)		\
  do									\
    {									\
      t_bunny_astack_node *__nod = (t_bunny_astack_node*)bunny_alloca(sizeof(*__nod));	\
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
/**
 * @doc
 * @doc-symbol bunny_astack_pop
 * @doc-kind function
 * @doc-module astack
 * @doc-order 200
 * @doc-since 11
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Removes the top element of an automatic stack.
 * @param st The automatic stack to edit.
 * @return-success This macro does not return the removed data.
 * @see t_bunny_astack
 *
 * @doc-lang fr
 * @brief Retire l'élément au sommet d'une pile automatique.
 * @param st La pile automatique à modifier.
 * @return-success Cette macro ne renvoie pas la donnée retirée.
 * @see t_bunny_astack
 */
# define			bunny_astack_pop(st)			\
  do									\
    {									\
      *(t_bunny_astack_node**)&(st)->top =				\
	((t_bunny_astack_node*)(st)->top)->next;			\
      *(size_t*)&(st)->length -= 1;					\
    }									\
  while (0)

# endif
#endif	/*			__LAPIN_ASTACK_H__			*/
