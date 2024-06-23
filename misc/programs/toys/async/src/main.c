/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2018
**
** LibLapin Test
*/

#include		<assert.h>
#include		<stdio.h>
#include		<lapin.h>

t_bunny_window		*win;
size_t			worknbr;
size_t			workdone;

t_bunny_response	async(void		*result,
			      void		*un)
{
  (void)un;
  printf("Work %zu terminated.\n", (size_t)result);
  workdone++;
  if ((size_t)result == 5)
    return (EXIT_ON_SUCCESS);
  return (GO_ON);
}

void			workf(void		*data,
			      void		*un)
{
  (void)un;
  printf("Processing %zu.\n", (size_t)data);
  bunny_usleep(1e6 * 0.33);
}

t_bunny_response	loop(void		*un)
{
  (void)un;
  if (worknbr == 0)
    for (worknbr = 0; worknbr < 6; ++worknbr)
      assert(bunny_async_computation_push(workf, (void*)worknbr));
  printf("--------\n");
  return (GO_ON);
}

t_bunny_response	display(void		*un)
{
  int			i = rand() % 256;

  (void)un;
  bunny_clear(&win->buffer, GRAY(i));
  bunny_display(win);
  return (GO_ON);
}

int			main(void)
{
  assert(win = bunny_start(320, 240, false, "Async test"));
  bunny_set_async_computation(2);
  bunny_set_display_function(display);
  bunny_set_async_computation_response(async);
  bunny_set_loop_main_function(loop);
  bunny_loop(win, 10, NULL);
  bunny_stop(win);
  bunny_set_async_computation(0);
  assert(workdone == worknbr);
  return (EXIT_SUCCESS);
}
