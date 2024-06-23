/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Webcam && Headtracking module
*/

#include		<lapin.h>
#include		<stdio.h>
#include		<assert.h>

typedef enum		e_screen
  {
    RED_SCREEN,		/* WITH SICKLE AND HAMER ON IT */
    BLUE_SCREEN,	/* OF DEATH */
    LAST_SCREEN,
  }			t_screen;

typedef struct		s_demo
{
  t_bunny_window	*win;
  t_bunny_time		previous;
  t_screen		screen;
}			t_demo;

t_bunny_response	exit_escape(t_bunny_event_state	state,
				    t_bunny_keysym	sym,
				    void		*d)
{
  (void)d;
  if (state == GO_DOWN && sym == BKS_ESCAPE)
    return (EXIT_ON_SUCCESS);
  return (GO_ON);
}

t_bunny_response	wait_five_seconds(t_demo	*demo)
{
  if (bunny_get_time() - demo->previous > 5 * 1e9)
    return (SWITCH_CONTEXT);
  return (GO_ON);
}

t_bunny_response	entering_red(t_demo		*demo)
{
  printf("We are red!\n");
  demo->screen = BLUE_SCREEN;
  demo->previous = bunny_get_time();
  return (GO_ON);
}

t_bunny_response	entering_blue(t_demo		*demo)
{
  printf("We are blue!\n");
  demo->screen = RED_SCREEN;
  demo->previous = bunny_get_time();
  return (GO_ON);
}

t_bunny_response	bluescreen_display(t_demo	*demo)
{
  bunny_clear(&demo->win->buffer, BLUE);
  bunny_display(demo->win);
  return (GO_ON);
}

t_bunny_response	redscreen_display(t_demo	*demo)
{
  bunny_clear(&demo->win->buffer, RED);
  bunny_display(demo->win);
  return (GO_ON);
}

const t_bunny_anonymous_context	screens[LAST_SCREEN] = {
  [RED_SCREEN] = {
    .entering_context = entering_red,
    .key = exit_escape,
    .loop = wait_five_seconds,
    .display = redscreen_display
  },
  [BLUE_SCREEN] = {
    .entering_context = entering_blue,
    .key = exit_escape,
    .loop = wait_five_seconds,
    .display = bluescreen_display
  }
};

int			main(void)
{
  t_demo		demo;
  t_bunny_response	resp;

  assert(demo.win = bunny_start(800, 600, false, "The Window"));
  demo.screen = RED_SCREEN;

  do
    {
      bunny_set_context((t_bunny_context*)&screens[demo.screen]);
      resp = bunny_loop(demo.win, 25, &demo);
    }
  while (resp == SWITCH_CONTEXT);
  bunny_stop(demo.win);
  return (EXIT_SUCCESS);
}

