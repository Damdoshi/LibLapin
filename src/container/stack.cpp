// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2017
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
  scream_log_if("%p -> %zu", stack, siz);
  return (siz);
}

#define			PATTERN		"%p stack, %p data -> %s"

bool			_bunny_stack_push(t_bunny_stack		*_stack,
					  const void		*data)
{
  struct bunny_stack	*stack = (struct bunny_stack*)_stack;
  struct bunny_node	*nod = (struct bunny_node*)bunny_malloc(sizeof(*nod));
  size_t		*i = &stack->length;

  if (nod == NULL)
    scream_error_if(return (false), bunny_errno, PATTERN, stack, data, "false");
  nod->data = (void*)data;
  nod->next = stack->top;
  stack->top = nod;
  *i += 1;
  scream_log_if(PATTERN, stack, data, "true");
  return (true);
}

#undef			PATTERN
#define			PATTERN		"%p -> %p"

void			*_bunny_stack_pop(t_bunny_stack		*_stack)
{
  struct bunny_stack	*stack = (struct bunny_stack*)_stack;
  struct bunny_node	*nod;
  void			*dat;
  size_t		*i = &stack->length;

  if ((nod = stack->top) == NULL)
    scream_error_if(return (NULL), BE_CONTAINER_IS_EMPTY, PATTERN, stack, nod);
  stack->top = nod->next;
  dat = nod->data;
  bunny_free(nod);
  *i -= 1;
  scream_log_if(PATTERN, stack, dat);
  return (dat);
}

