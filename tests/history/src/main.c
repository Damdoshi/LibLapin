/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2020
**
** LibLapin Test
*/

#include		<assert.h>
#include		<lapin.h>

void			dump(int64_t				tick,
			     int				*ptr)
{
  printf("Tick %ld: %d\n", tick, *ptr);
}

bool			march(void				*next,
			      void				*current,
			      int64_t				tick,
			      t_bunny_historical_event		*events,
			      size_t				event_size,
			      void				*data)
{
  const char		*data_string = data;
  int			*nxt = next;
  int			*cur = current;
  size_t		i;

  puts("---------------------------------------");
  printf("Data is '%s'. Tick is %lu. There's %zu events.\n", data_string, tick, event_size);
  printf("Current state is %d at address %p.\n", *cur, cur);
  *nxt = *cur;
  for (i = 0; i < event_size; ++i)
    {
      printf("The first event's value is %d.\n", *(int*)events[i].data);
      *nxt += *(int*)events[i].data;
    }
  printf("At tick %lu, next step value will be %d at address %p\n", tick + 1, *nxt, nxt);
  return (true);
}

int			main(void)
{
  t_bunny_event_history	*his;
  int			data;

  assert((his = bunny_new_event_history()));
  for (data = 0; data <= 5; ++data)
    assert((bunny_history_add_event(his, data, sizeof(data), &data)));
  data -= 1;
  assert((bunny_history_add_event(his, data, sizeof(data), &data)));
  assert((data = bunny_history_count_events_since(his, 3)) == 4);
  t_bunny_historical_event array[data];

  assert(bunny_history_get_events_since(his, 3, &array[0]) == 4);
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

  t_bunny_historical_event previous[1];
  t_bunny_historical_event last[2];

  assert(bunny_history_count_events_of(his, 4) == 1);
  assert(bunny_history_count_events_of(his, 5) == 2);
  assert(bunny_history_get_events_of(his, 4, &previous[0]) == 1);
  assert(previous[0].length == sizeof(data));
  assert(previous[0].tick == 4);
  assert(*(int*)previous[0].data == 4);

  assert(bunny_history_get_events_of(his, 5, &last[0]) == 2);
  assert(last[0].length == sizeof(data));
  assert(last[0].tick == 5);
  assert(*(int*)last[0].data == 5);
  assert(last[1].length == sizeof(data));
  assert(last[1].tick == 5);
  assert(*(int*)last[1].data == 5);

  t_bunny_configuration *cnf;

  assert((cnf = bunny_new_configuration()));
  assert(bunny_save_event_history(his, cnf));
  t_bunny_event_history *hev;

  assert((hev = bunny_read_event_history(cnf)));
  assert(bunny_save_event_history(hev, cnf));
  assert(bunny_history_compare(his, hev));
  bunny_delete_configuration(cnf);
  bunny_delete_event_history(hev);

  //// HISTORIC ELEMENT

  t_bunny_historic_element *elem;
  int			*last_status;
  const char		*data_string = "March step";
  int			initial_status = -5;

  assert((elem = bunny_new_historic_element(march, 10, sizeof(data))));
  assert(bunny_historic_element_compute(elem, 5, his, (void*)data_string) == -1);
  assert((last_status = bunny_historic_element_last_status(elem)) == NULL);
  bunny_historic_element_add_key_frame(elem, 0, &initial_status);
  assert(bunny_historic_element_compute(elem, 6, his, (void*)data_string) == 6);
  assert((last_status = bunny_historic_element_last_status(elem)) != NULL);
  // 0: -5
  // 1: -4
  // 2: -2
  // 3: 1
  // 4: 5
  // 5: 10
  // 5: 15 -> 6
  assert(*last_status == 15);

  // On ajoute un evenement au timestamp 3: le passé change, il faut donc recalculer les états...
  puts("=========================================================");
  puts("Adding an event at 3 (+10) and rewinding to 3.");
  data = 10;
  assert((bunny_history_add_event(his, 3, sizeof(data), &data)));
  assert(bunny_historic_element_rewind(elem, 3));
  assert(bunny_historic_element_compute(elem, 6, his, (void*)data_string) == 6);
  assert((last_status = bunny_historic_element_last_status(elem)) != NULL);
  // 3: 11 (1 + 10)
  // 4: 15
  // 5: 20
  // 5: 25
  assert(*last_status == 25);

  // On va maintenant ajouter une image clef a 4 et tenter de remonter a 3.
  // Le comportement attendu est qu'a la place de remonter a 3, on va remonter a 4 seulement
  // Du fait de l'image clef a 4. Ensuite la valeur de 5 dépendra de l'image clef a 4, evidemment
  puts("=========================================================");
  puts("Setting key value (0) at 4, and rewiding to 3 (that's gonna be refused and only rewind to 4)");
  data = 0;
  assert(bunny_historic_element_add_key_frame(elem, 4, &data)); // On ecrase 15.
  assert(bunny_historic_element_rewind(elem, 3));
  assert(bunny_historic_element_compute(elem, 6, his, (void*)data_string) == 6);
  assert((last_status = bunny_historic_element_last_status(elem)) != NULL);
  // 4: 0 -> 4
  // 5: 4 -> 14 (5 + 5)
  // 6: 14
  bunny_historic_element_dump(elem, (t_bunny_historic_dump)dump);
  assert(*last_status == 14);

  bunny_delete_historic_element(elem);
  bunny_delete_event_history(his);
  return (0);
}

