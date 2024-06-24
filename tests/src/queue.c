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
  t_bunny_queue		*que;
  int			elm[3] = {2, 3, 4};

  assert((que = bunny_new_queue()) != NULL);
  assert(bunny_queue_size(que) == 0);
  assert(bunny_queue_empty(que));
  assert(bunny_queue_front(que, int*) == NULL);

  assert(bunny_queue_push(que, &elm[0]));
  assert(bunny_queue_size(que) == 1);
  assert(!bunny_queue_empty(que));
  assert(bunny_queue_front(que, int*) == &elm[0]);

  assert(bunny_queue_push(que, &elm[1]));
  assert(bunny_queue_size(que) == 2);
  assert(!bunny_queue_empty(que));
  assert(bunny_queue_front(que, int*) == &elm[0]);

  assert(bunny_queue_push(que, &elm[2]));
  assert(bunny_queue_size(que) == 3);
  assert(!bunny_queue_empty(que));
  assert(bunny_queue_front(que, int*) == &elm[0]);

  assert(bunny_queue_pop(que, int*) == &elm[0]);
  assert(bunny_queue_size(que) == 2);
  assert(!bunny_queue_empty(que));
  assert(bunny_queue_front(que, int*) == &elm[1]);

  assert(bunny_queue_pop(que, int*) == &elm[1]);
  assert(bunny_queue_size(que) == 1);
  assert(!bunny_queue_empty(que));
  assert(bunny_queue_front(que, int*) == &elm[2]);

  assert(bunny_queue_pop(que, int*) == &elm[2]);
  assert(bunny_queue_size(que) == 0);
  assert(bunny_queue_empty(que));
  assert(bunny_queue_front(que, int*) == NULL);
  assert(bunny_queue_pop(que, int*) == NULL);

  assert(bunny_queue_push(que, &elm[0]));
  assert(bunny_queue_size(que) == 1);
  assert(!bunny_queue_empty(que));
  assert(bunny_queue_front(que, int*) == &elm[0]);

  assert(bunny_queue_push(que, &elm[1]));
  assert(bunny_queue_size(que) == 2);
  assert(!bunny_queue_empty(que));
  assert(bunny_queue_front(que, int*) == &elm[0]);

  bunny_malloc_failure(true);
  assert(bunny_queue_push(que, &elm[0]) == false);
  bunny_malloc_failure(false);

  assert(bunny_delete_queue(que) == 2);


  return (EXIT_SUCCESS);
}
