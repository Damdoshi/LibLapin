// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

struct			bunny_node
{
  void			*data;
  struct bunny_node	*next;
};

struct			bunny_stack
{
  size_t		length;
  struct bunny_node	*top;
};

/*!
** Delete a stack and all of its internal nodes.
**
** Stored data pointers are not freed. Only the container nodes and the stack
** object itself are released.
**
** \param stack The stack to destroy.
** \return The number of elements that were stored in the stack.
*/
/**
 * @doc
 * @doc-symbol bunny_delete_stack
 * @doc-kind function
 * @doc-module stack
 * @doc-order 130
 * @doc-since 11
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Deletes a stack and its internal nodes.
 * @param stack The stack to delete.
 * @return-success Returns the number of elements that were in the stack.
 * @log This symbol writes a log entry in the $Lcontainer@ log domain.
 * @see bunny_new_stack
 *
 * @doc-lang fr
 * @brief Détruit une pile et ses nœuds internes.
 * @param stack La pile à détruire.
 * @return-success Renvoie le nombre d'éléments qui étaient dans la pile.
 * @log Ce symbole écrit une entrée de log dans le domaine $Lcontainer@.
 * @see bunny_new_stack
 */
size_t			bunny_delete_stack(t_bunny_stack	*stack)
{
  struct bunny_node	*nod = (struct bunny_node*)stack->top;
  struct bunny_node	*prv;
  size_t		siz = stack->length;

  while (nod)
    {
      prv = nod->next;
      bunny_free(nod);
      nod = prv;
    }
  bunny_free(stack);
  scream_log_if("%p -> %zu", "container", stack, siz);
  return (siz);
}

#define			PATTERN		"%p stack, %p data -> %s"

/*!
** Push a data pointer on top of a stack.
**
** This is the typed implementation behind the bunny_stack_push macro.
**
** \param _stack The stack to edit.
** \param data The data pointer to store.
** \return True on success, false on allocation error.
*/
bool			_bunny_stack_push(t_bunny_stack		*_stack,
					  const void		*data)
{
  struct bunny_stack	*stack = (struct bunny_stack*)_stack;
  struct bunny_node	*nod = (struct bunny_node*)bunny_malloc(sizeof(*nod));
  size_t		*i = &stack->length;

  if (nod == NULL)
    scream_error_if(return (false), bunny_errno, PATTERN, "container", stack, data, "false");
  nod->data = (void*)data;
  nod->next = stack->top;
  stack->top = nod;
  *i += 1;
  scream_log_if(PATTERN, "container", stack, data, "true");
  return (true);
}

#undef			PATTERN
#define			PATTERN		"%p -> %p"

/*!
** Pop the data pointer stored at the top of a stack.
**
** The returned data is not freed by the container.
**
** \param _stack The stack to edit.
** \return The extracted data pointer, or NULL if the stack is empty.
*/
void			*_bunny_stack_pop(t_bunny_stack		*_stack)
{
  struct bunny_stack	*stack = (struct bunny_stack*)_stack;
  struct bunny_node	*nod;
  void			*dat;
  size_t		*i = &stack->length;

  if ((nod = stack->top) == NULL)
    scream_error_if(return (NULL), BE_CONTAINER_IS_EMPTY, PATTERN, "container", stack, nod);
  stack->top = nod->next;
  dat = nod->data;
  bunny_free(nod);
  *i -= 1;
  scream_log_if(PATTERN, "container", stack, dat);
  return (dat);
}

