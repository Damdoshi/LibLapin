/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** LibLapin - Opening a window
*/

#include		<stdlib.h> /* EXIT_FAILURE, EXIT_SUCCESS */
#include		<stdio.h> /* printf */
#include		<lapin.h>

int			main(void)
{
  t_bunny_window	*win; /* (lapin/window.h) */

  /* open a window */
  /* (lapin/window.h) */
  /* width on window, height of window, fullscreen? true, or false, name of the window */
  win = bunny_start(800, 600, false, "LibLapin - Opening a Window");
  if (win == NULL)
    {
      bunny_printlerr("Cannot open the window."); /* print litteral on stderr. (lapin/misc.h) */
      return (EXIT_FAILURE);
    }
  bunny_printl("Properties of the window:"); /* print litteral on stdout. (lapin/misc.h) */
  printf("Name: %s.\n", win->name);
  printf("Width: %zu.\n", win->buffer.width);
  printf("Height: %zu.\n", win->buffer.height);

  /* clear the content of the window with PINK2 color. (lapin/graphics.h, lapin/color.h) */
  /* bunny_clear takes a t_bunny_buffer. Because a window contains a t_bunny_buffer, */
  /* you can use it with t_bunny_window this way */
  /* The second parameter is the color */
  bunny_clear(&win->buffer, PINK2);

  /* compute every drawing made on the window and display it on screen, (lapin/window.h) */
  /* the parameter is the window to refresh */
  /* if you do not do this, the window content will remain undefined */
  bunny_display(win);
  
  /* loop until until the exit button is pushed. (lapin/event.h) */
  /* the window, the number of frame per seconds, and a third parameter you will see later */
  bunny_loop(win, 25, NULL);

  /* destroy the window (lapin/window.h) */
  bunny_stop(win);
  return (EXIT_SUCCESS);
}

