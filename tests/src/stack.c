/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2026
** Pentacle Technologie 2008-2026
** EFRITS 2022-2026
**
** Bibliothèque Lapin
*/

#include		<assert.h>
#include		<stdlib.h>
#include		"lapin.h"

static void		test_empty_stack(void)
{
  t_bunny_stack		*stk;

  assert((stk = bunny_new_stack()) != NULL);
  assert(bunny_stack_size(stk) == 0);
  assert(bunny_stack_empty(stk));
  assert(bunny_stack_top(stk, int*) == NULL);
  assert(bunny_stack_pop(stk, int*) == NULL);
  assert(bunny_delete_stack(stk) == 0);
}

static void		test_lifo_order(void)
{
  t_bunny_stack		*stk;
  int			elm[8];
  size_t		i;

  assert((stk = bunny_new_stack()) != NULL);
  for (i = 0; i < NBRCELL(elm); ++i)
    {
      elm[i] = (int)(100 + i);
      assert(bunny_stack_push(stk, &elm[i]));
      assert(bunny_stack_size(stk) == i + 1);
      assert(!bunny_stack_empty(stk));
      assert(bunny_stack_top(stk, int*) == &elm[i]);
    }
  for (i = NBRCELL(elm); i > 0; --i)
    {
      assert(bunny_stack_top(stk, int*) == &elm[i - 1]);
      assert(bunny_stack_pop(stk, int*) == &elm[i - 1]);
      assert(bunny_stack_size(stk) == i - 1);
    }
  assert(bunny_stack_empty(stk));
  assert(bunny_stack_top(stk, int*) == NULL);
  assert(bunny_stack_pop(stk, int*) == NULL);
  assert(bunny_delete_stack(stk) == 0);
}

static void		test_null_payload(void)
{
  t_bunny_stack		*stk;

  assert((stk = bunny_new_stack()) != NULL);
  assert(bunny_stack_push(stk, NULL));
  assert(bunny_stack_size(stk) == 1);
  assert(!bunny_stack_empty(stk));
  assert(bunny_stack_top(stk, void*) == NULL);
  assert(bunny_stack_pop(stk, void*) == NULL);
  assert(bunny_stack_empty(stk));
  assert(bunny_delete_stack(stk) == 0);
}

static void		test_allocation_failure_keeps_state(void)
{
  t_bunny_stack		*stk;
  int			a = 1;
  int			b = 2;

  assert((stk = bunny_new_stack()) != NULL);
  assert(bunny_stack_push(stk, &a));
  bunny_malloc_failure(true);
  assert(bunny_stack_push(stk, &b) == false);
  bunny_malloc_failure(false);
  assert(bunny_stack_size(stk) == 1);
  assert(bunny_stack_top(stk, int*) == &a);
  assert(bunny_stack_pop(stk, int*) == &a);
  assert(bunny_delete_stack(stk) == 0);
}

int			main(void)
{
  test_empty_stack();
  test_lifo_order();
  test_null_payload();
  test_allocation_failure_keeps_state();
  return (EXIT_SUCCESS);
}
