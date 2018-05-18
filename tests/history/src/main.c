/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** LibLapin Test
*/

#include		<assert.h>
#include		<lapin.h>

int			main(void)
{
  t_bunny_history	*history;
  int			val;

  assert(history = bunny_new_history(sizeof(val)));
  assert(history->frame_size == sizeof(val));
  for (val = 0; val < 10; ++val)
    assert(bunny_history_add_frame(history, val, &val) != 0);
  for (val = 0; val < 10; ++val)
    assert(*(int*)bunny_history_get_frame(history, val) == val);

  assert(history->last_frame_time == 9);
  assert(history->oldest_frame_time == 0);
  assert(history->nbr_frame == 10);
  assert(*(int*)history->last_frame == 9);

  bunny_history_erase_before(history, 3);
  bunny_history_erase_after(history, 8);
  bunny_history_erase_frame(history, 5);

  assert(bunny_history_get_frame(history, 1) == NULL);
  assert(bunny_history_get_frame(history, 2) == NULL);
  assert(*(int*)bunny_history_get_frame(history, 5) == 4);
  assert(*(int*)bunny_history_get_frame(history, 9) == 8);
  assert(*(int*)bunny_history_get_frame(history, 10) == 8);

  assert(history->nbr_frame == 5);
  assert(history->oldest_frame_time == 3);
  assert(*(int*)history->last_frame == 8);

  bunny_history_erase_frame(history, 8);
  assert(*(int*)history->last_frame == 7);
  assert(history->nbr_frame == 4);

  bunny_history_erase_frame(history, 7);
  assert(*(int*)history->last_frame == 6);
  assert(history->nbr_frame == 3);

  bunny_history_erase_frame(history, 6);
  assert(*(int*)history->last_frame == 4);
  assert(history->nbr_frame == 2);

  bunny_history_erase_frame(history, 4);
  assert(*(int*)history->last_frame == 3);
  assert(history->nbr_frame == 1);

  bunny_history_erase_frame(history, 3);
  assert(history->last_frame == NULL);
  assert(history->nbr_frame == 0);

  for (val = 0; val < 10; ++val)
    assert(bunny_history_add_frame(history, val, &val) != 0);
  bunny_history_clear(history);
  assert(history->nbr_frame == 0);
  bunny_delete_history(history);

  return (0);
}

