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

static void		test_astack_lifo(void)
{
  t_bunny_astack	*stk;
  int			elm[4] = {10, 20, 30, 40};
  size_t		i;

  assert((stk = bunny_new_astack()) != NULL);
  assert(bunny_astack_size(stk) == 0);
  assert(bunny_astack_empty(stk));
  assert(bunny_astack_top(stk, int*) == NULL);
  for (i = 0; i < NBRCELL(elm); ++i)
    {
      bunny_astack_push(stk, &elm[i]);
      assert(bunny_astack_size(stk) == i + 1);
      assert(!bunny_astack_empty(stk));
      assert(bunny_astack_top(stk, int*) == &elm[i]);
    }
  for (i = NBRCELL(elm); i > 0; --i)
    {
      assert(bunny_astack_top(stk, int*) == &elm[i - 1]);
      bunny_astack_pop(stk);
      assert(bunny_astack_size(stk) == i - 1);
    }
  assert(bunny_astack_empty(stk));
  assert(bunny_astack_top(stk, int*) == NULL);
}

static void		test_astack_null_payload(void)
{
  t_bunny_astack	*stk;

  assert((stk = bunny_new_astack()) != NULL);
  bunny_astack_push(stk, NULL);
  assert(bunny_astack_size(stk) == 1);
  assert(!bunny_astack_empty(stk));
  assert(bunny_astack_top(stk, void*) == NULL);
  bunny_astack_pop(stk);
  assert(bunny_astack_empty(stk));
}

int			main(void)
{
  test_astack_lifo();
  test_astack_null_payload();
  return (EXIT_SUCCESS);
}
