/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** LibLapin - Draw a shape
*/

#include		<stdlib.h> /* EXIT_FAILURE, EXIT_SUCCESS, rand, srand */
#include		<time.h> /* time */
#include		<stdio.h> /* printf */
#include		<lapin.h>

typedef struct		s_program
{
  char			*name;
  t_bunny_window	*win; /* lapin/window.h */
  t_bunny_position	pos[2]; /* lapin/placement.h */
  t_bunny_position	speed[2]; /* lapin/placement.h */
}			t_program;

t_bunny_response	key_response(t_bunny_event_state	state,
				     t_bunny_keysym		sym,
				     void			*data)
{
  char			**str = data;

  /* A key that was pressed has been released (lapin/evnet.h) */
  /* And the key is escape */
  if (state == GO_UP && sym == BKS_ESCAPE)
    {
      printf("%s: Closing the window with escape.\n", *str);
      /* Say we want to exit bunny_loop* and that the program is a success (lapin/events.h) */
      return (EXIT_ON_SUCCESS);
    }
  /* Say we want to stay in bunny_loop* (lapin/events.h) */
  return (GO_ON);
}

t_bunny_response	main_loop(void				*data)
{
  unsigned int		color[2];
  t_program		*prog = data;

  /* random non transparent color */
  /* (BLACK, lapin/color.h) */
  color[0] = rand() | BLACK;
  color[1] = rand() | BLACK;

  /* draw a line between pos[0] and pos[1] */
  /* This function work on window and picture. To work on pixerlarray, it will */
  /* need a function that you must program and assign to gl_bunny_my_set_line */
  /* (lapin/graphics.h) */
  bunny_set_line(&prog->win->buffer, &prog->pos[0], &color[0]);

  /* move line */
  if ((prog->pos[0].x += prog->speed[0].x) < 0 || prog->pos[0].x >= prog->win->buffer.width)
    prog->pos[0].x += 2 *(prog->speed[0].x *= -1);
  if ((prog->pos[0].y += prog->speed[0].y) < 0 || prog->pos[0].y >= prog->win->buffer.height)
    prog->pos[0].y += 2 * (prog->speed[0].y *= -1);

  if ((prog->pos[1].x += prog->speed[1].x) < 0 || prog->pos[1].x >= prog->win->buffer.width)
    prog->pos[1].x += 2 * (prog->speed[1].x *= -1);
  if ((prog->pos[1].y += prog->speed[1].y) < 0 || prog->pos[1].y >= prog->win->buffer.height)
    prog->pos[1].y += 2 * (prog->speed[1].y *= -1);
  
  /* compute every drawing made on the window and display it on screen */
  /* the parameter is the window to refresh */
  /* if you do not do this, the window content will remain undefined */
  /* (lapin/window.h) */
  bunny_display(prog->win);

  /* Say we want to stay in bunny_loop* (lapin/events.h) */
  return (GO_ON);
}

int			main(int				argc,
			     char				**argv)
{
  t_program		program;

  (void)argc; /* we will not use the argc parameter */
  
  /* open a window */
  /* width on window, height of window, fullscreen? true, or false, name of the window */
  /* (lapin/window.h) */
  program.win = bunny_start(800, 600, false, "LibLapin - Shape");
  if (program.win == NULL)
    {
      bunny_printlerr("Cannot open the window."); /* print litteral on stderr. (lapin/misc.h) */
      return (EXIT_FAILURE);
    }
  program.name = argv[0];

  /* init the random generator */
  srand(time(NULL));
  
  /* determine random position for every side of the lide */
  program.pos[0].x = rand() % program.win->buffer.width;
  program.pos[0].y = rand() % program.win->buffer.height;
  program.pos[1].x = rand() % program.win->buffer.width;
  program.pos[1].y = rand() % program.win->buffer.height;

  /* determine random speed */
  program.speed[0].x = rand() % 2 ? 1 : -1;
  program.speed[0].y = rand() % 2 ? 1 : -1;
  program.speed[1].x = rand() % 2 ? 1 : -1;
  program.speed[1].y = rand() % 2 ? 1 : -1;
  
  /* clear the content of the window with PINK2 color */
  /* bunny_clear takes a t_bunny_buffer. Because a window contains a t_bunny_buffer, */
  /* you can use it with t_bunny_window this way */
  /* The second parameter is the color */
  /* (lapin/graphics.h, lapin/color.h) */
  bunny_clear(&program.win->buffer, PINK2);
  
  bunny_printl("Press escape to exit."); /* lapin/misc.h */

  /* set functions that will be called if event of specific types happened */
  /* keydown or keyup, clickdown or clickup, time passes  */
  bunny_set_key_response(key_response); /* lapin/events.h */
  bunny_set_loop_main_function(main_loop); /* lapin/events.h */
    
  /* loop until until the exit button is pushed */
  /* The first parameter is the window, the second the number of frame per seconds */
  /* Also manage events by calling function given previously with bunny_set_*_response */
  /* functions and bunny_set_loop_main_function. */
  /* The third parameter is sent to these functions */
  /* (lapin/events.h) */
  bunny_loop(program.win, 100, &program);

  /* destroy the window (lapin/window.h) */
  bunny_stop(program.win);
  return (EXIT_SUCCESS);
}

