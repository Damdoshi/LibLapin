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

static void		test_empty_queue(void)
{
  t_bunny_queue		*que;

  assert((que = bunny_new_queue()) != NULL);
  assert(bunny_queue_size(que) == 0);
  assert(bunny_queue_empty(que));
  assert(bunny_queue_front(que, int*) == NULL);
  assert(bunny_queue_pop(que, int*) == NULL);
  assert(bunny_delete_queue(que) == 0);
}

static void		test_fifo_order(void)
{
  t_bunny_queue		*que;
  int			elm[8];
  size_t		i;

  assert((que = bunny_new_queue()) != NULL);
  for (i = 0; i < NBRCELL(elm); ++i)
    {
      elm[i] = (int)(200 + i);
      assert(bunny_queue_push(que, &elm[i]));
      assert(bunny_queue_size(que) == i + 1);
      assert(!bunny_queue_empty(que));
      assert(bunny_queue_front(que, int*) == &elm[0]);
    }
  for (i = 0; i < NBRCELL(elm); ++i)
    {
      assert(bunny_queue_front(que, int*) == &elm[i]);
      assert(bunny_queue_pop(que, int*) == &elm[i]);
      assert(bunny_queue_size(que) == NBRCELL(elm) - i - 1);
    }
  assert(bunny_queue_empty(que));
  assert(bunny_queue_front(que, int*) == NULL);
  assert(bunny_queue_pop(que, int*) == NULL);
  assert(bunny_delete_queue(que) == 0);
}

static void		test_reuse_after_empty(void)
{
  t_bunny_queue		*que;
  int			a = 1;
  int			b = 2;

  assert((que = bunny_new_queue()) != NULL);
  assert(bunny_queue_push(que, &a));
  assert(bunny_queue_pop(que, int*) == &a);
  assert(bunny_queue_empty(que));
  assert(bunny_queue_push(que, &b));
  assert(bunny_queue_size(que) == 1);
  assert(bunny_queue_front(que, int*) == &b);
  assert(bunny_queue_pop(que, int*) == &b);
  assert(bunny_delete_queue(que) == 0);
}

static void		test_null_payload(void)
{
  t_bunny_queue		*que;

  assert((que = bunny_new_queue()) != NULL);
  assert(bunny_queue_push(que, NULL));
  assert(bunny_queue_size(que) == 1);
  assert(!bunny_queue_empty(que));
  assert(bunny_queue_front(que, void*) == NULL);
  assert(bunny_queue_pop(que, void*) == NULL);
  assert(bunny_queue_empty(que));
  assert(bunny_delete_queue(que) == 0);
}

static void		test_allocation_failure_keeps_state(void)
{
  t_bunny_queue		*que;
  int			a = 1;
  int			b = 2;

  assert((que = bunny_new_queue()) != NULL);
  assert(bunny_queue_push(que, &a));
  bunny_malloc_failure(true);
  assert(bunny_queue_push(que, &b) == false);
  bunny_malloc_failure(false);
  assert(bunny_queue_size(que) == 1);
  assert(bunny_queue_front(que, int*) == &a);
  assert(bunny_queue_pop(que, int*) == &a);
  assert(bunny_delete_queue(que) == 0);
}

int			main(void)
{
  test_empty_queue();
  test_fifo_order();
  test_reuse_after_empty();
  test_null_payload();
  test_allocation_failure_keeps_state();
  return (EXIT_SUCCESS);
}
