/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2020
**
** LibLapin Test
*/

#include		<assert.h>
#include		<lapin.h>

int			main(void)
{
  t_bunny_event_history	*his;
  int			data;

  assert((his = bunny_new_event_history()));
  for (data = 0; data <= 5; ++data)
    assert((bunny_history_add_event(his, data, sizeof(data), &data)));
  data -= 1;
  assert((bunny_history_add_event(his, data, sizeof(data), &data)));
  assert((data = bunny_history_count_events(his, 3)) == 4);
  t_bunny_historical_event array[data];

  assert(bunny_history_get_events(his, 3, &array[0]) == 4);
  assert(array[0].length == sizeof(data));
  assert(array[1].length == sizeof(data));
  assert(array[2].length == sizeof(data));
  assert(array[3].length == sizeof(data));
  assert(array[0].tick == 3);
  assert(array[1].tick == 4);
  assert(array[2].tick == 5);
  assert(array[3].tick == 5);
  assert(*(int*)array[0].data == 3);
  assert(*(int*)array[1].data == 4);
  assert(*(int*)array[2].data == 5);
  assert(*(int*)array[3].data == 5);
  bunny_delete_event_history(his);
  return (0);
}

