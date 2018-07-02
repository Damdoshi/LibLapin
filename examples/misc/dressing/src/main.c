/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** LibLapin Test
*/

#include		<assert.h>
#include		<lapin.h>

t_bunny_dressing_screen	gl_dressing_screen = {
  .head = {
    .subcontext = {
      .key = NULL
    }
  }
};

int			main(void)
{
  t_bunny_window	*win;

  bunny_set_error_descriptor(2);
  if (bunny_init_dressing_context("./dressing.dab", &gl_dressing_screen) == false)
    {
      bunny_perror("bunny_init_dressing_context_file");
      return (EXIT_FAILURE);
    }
  assert(win = bunny_start(800, 600, false, "Dressing Screen"));
  gl_dressing_screen.head.screen = &win->buffer;
  bunny_set_context(&gl_bunny_dressing_context);
  bunny_loop(win, 25, &gl_dressing_screen);
  bunny_clear_dressing_context(&gl_dressing_screen);
  bunny_stop(win);
  return (EXIT_SUCCESS);
}

