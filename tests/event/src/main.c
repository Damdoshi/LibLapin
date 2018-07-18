/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** LibLapin Test
*/

#include		<stdio.h>
#include		<assert.h>
#include		<lapin.h>

t_bunny_window		*win;

t_bunny_response	event(const t_bunny_event	*event,
			      void			*data)
{
  static int		cnt;
  const char		*ptr;
  size_t		i;

  (void)data;
  printf("Event type: %d, ", event->type);
  for (i = 0, ptr = (char*)event; i < sizeof(event); ++i)
    printf("%x", ptr[i]);
  printf("\n");
  if (++cnt > 20)
    return (EXIT_ON_SUCCESS);
  return (GO_ON);
}

int			main(void)
{
  assert(win = bunny_start(320, 240, false, "event reporter test"));
  bunny_set_event_response(event);
  bunny_loop(win, 25, NULL);
  bunny_stop(win);
  return (EXIT_SUCCESS);
}

