/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** LibLapin Test
*/

#include		<stdio.h>
#include		<time.h>
#include		<signal.h>
#include		<assert.h>
#include		<stdlib.h>
#include		<lapin.h>

t_bunny_window		*win;
t_bunny_font		*fnt;
unsigned int		i;
int			exittime;

static void		sighandler(int		sig)
{
  (void)sig;
  exit(EXIT_FAILURE);
}

t_bunny_response	loop(void		*d)
{
  (void)d;
  i = i + 1;
  if (exittime != 0 && i > bunny_get_frequency() * exittime)
    return (EXIT_ON_SUCCESS);
  return (GO_ON);
}

t_bunny_response	display(void		*d)
{
  (void)d;
  bunny_fill(&win->buffer, ALPHA(32, BLACK));

  fnt->offset.x = cos(i / 16.0) * 30;
  bunny_clear(&fnt->clipable.buffer, 0);
  bunny_draw(&fnt->clipable);

  bunny_blit(&win->buffer, &fnt->clipable, NULL);
  bunny_display(win);
  return (GO_ON);
}

int			main(int		argc,
			     char		**argv)
{
  (void)argv;
  signal(SIGALRM, sighandler);
  if (argc == 2)
    {
      exittime = 1;
      alarm(2);
    }
  else
    exittime = 0;

  bunny_set_error_descriptor(2);
  assert(fnt = bunny_load_text("fnt.ini"));
  assert(win = bunny_start
	 (fnt->clipable.buffer.width,
	  fnt->clipable.buffer.height,
	  false,
	  "The Window"
	  ));

  bunny_fill(&win->buffer, BLACK);

  bunny_set_display_function(display);
  bunny_set_loop_main_function(loop);
  bunny_loop(win, 25, NULL);

  bunny_delete_clipable(fnt);
  bunny_stop(win);
  return (EXIT_SUCCESS);
}
