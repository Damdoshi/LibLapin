/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2024
** Pentacle Technologie 2008-2024
** EFRITS 2022-2024
**
** Bibliothèque Lapin
*/

#include		<assert.h>
#include		"lapin.h"

int			main(void)
{
  t_bunny_stack		*stk;
  int			elm[3] = {2, 3, 4};

  assert((stk = bunny_new_stack()) != NULL);
  assert(bunny_stack_size(stk) == 0);
  assert(bunny_stack_empty(stk));
  assert(bunny_stack_top(stk, int*) == NULL);

  assert(bunny_stack_push(stk, &elm[0]));
  assert(bunny_stack_size(stk) == 1);
  assert(!bunny_stack_empty(stk));
  assert(bunny_stack_top(stk, int*) == &elm[0]);

  assert(bunny_stack_push(stk, &elm[1]));
  assert(bunny_stack_size(stk) == 2);
  assert(!bunny_stack_empty(stk));
  assert(bunny_stack_top(stk, int*) == &elm[1]);

  assert(bunny_stack_push(stk, &elm[2]));
  assert(bunny_stack_size(stk) == 3);
  assert(!bunny_stack_empty(stk));
  assert(bunny_stack_top(stk, int*) == &elm[2]);

  assert(bunny_stack_pop(stk, int*) == &elm[2]);
  assert(bunny_stack_size(stk) == 2);
  assert(!bunny_stack_empty(stk));
  assert(bunny_stack_top(stk, int*) == &elm[1]);

  assert(bunny_stack_pop(stk, int*) == &elm[1]);
  assert(bunny_stack_size(stk) == 1);
  assert(!bunny_stack_empty(stk));
  assert(bunny_stack_top(stk, int*) == &elm[0]);

  assert(bunny_stack_pop(stk, int*) == &elm[0]);
  assert(bunny_stack_size(stk) == 0);
  assert(bunny_stack_empty(stk));
  assert(bunny_stack_top(stk, int*) == NULL);
  assert(bunny_stack_pop(stk, int*) == NULL);

  assert(bunny_stack_push(stk, &elm[0]));
  assert(bunny_stack_size(stk) == 1);
  assert(!bunny_stack_empty(stk));
  assert(bunny_stack_top(stk, int*) == &elm[0]);

  assert(bunny_stack_push(stk, &elm[1]));
  assert(bunny_stack_size(stk) == 2);
  assert(!bunny_stack_empty(stk));
  assert(bunny_stack_top(stk, int*) == &elm[1]);

  bunny_malloc_failure(true);
  assert(bunny_stack_push(stk, &elm[0]) == false);
  bunny_malloc_failure(false);

  assert(bunny_delete_stack(stk) == 2);


  return (EXIT_SUCCESS);
}
