/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** LibLapin - Sprite
*/

#include		<stdlib.h> /* EXIT_FAILURE, EXIT_SUCCESS, rand, srand */
#include		<time.h> /* time */
#include		<stdio.h> /* printf */
#include		<lapin.h>

typedef struct		s_program
{
  char			*name;
  t_bunny_window	*win;
}			t_program;

t_bunny_response	key_response(t_bunny_event_state	state,
				     t_bunny_keysym		sym,
				     void			*data)
{
  char			**str = data;

  if (state == GO_UP && sym == BKS_ESCAPE)
    {
      printf("%s: Closing the window with escape.\n", *str);
      return (EXIT_ON_SUCCESS);
    }
  return (GO_ON);
}

t_bunny_response	main_loop(void				*data)
{
  t_program		*prog = data;

  /* clear the content of the window with PINK2 color */
  /* bunny_clear takes a t_bunny_buffer. Because a window contains a t_bunny_buffer, */
  /* you can use it with t_bunny_window this way */
  /* The second parameter is the color */
  bunny_clear(&program.win->buffer, PINK2);

  
  /* compute every drawing made on the window and display it on screen */
  /* the parameter is the window to refresh */
  /* if you do not do this, the window content will remain undefined */
  bunny_display(prog->win);
  return (GO_ON);
}

int			main(int				argc,
			     char				**argv)
{
  t_program		program;

  (void)argc; /* we will not use the argc parameter */
  
  /* open a window */
  /* width on window, height of window, fullscreen? true, or false, name of the window */
  program.win = bunny_start(800, 600, false, "LibLapin - Sprite");
  if (program.win == NULL)
    {
      bunny_printlerr("Cannot open the window."); /* print litteral on stderr. lapin/misc.h */
      return (EXIT_FAILURE);
    }
  program.name = argv[0];

  /* init the random generator */
  srand(time(NULL));
  
  bunny_printl("Press escape to exit."); /* lapin/misc.h */

  /* set functions that will be called if event of specific types happened */
  /* keydown or keyup, clickdown or clickup, time passes  */
  bunny_set_key_response(key_response); /* lapin/basic.h */
  bunny_set_loop_main_function(main_loop); /* lapin/basic.h */
  bunny_set_display_function(display); /* lapin/basic.h */
    
  /* loop until until the exit button is pushed */
  /* The first parameter is the window, the second the number of frame per seconds */
  /* Also manage events by calling function given previously with bunny_set_*_response */
  /* functions and bunny_set_loop_main_function. */
  /* The third parameter is sent to these functions */
  bunny_loop(program.win, 100, &program);

  /* destroy the window */
  bunny_stop(program.win);
  return (EXIT_SUCCESS);
}

