/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** LibLapin - Sprite
*/

#include		<stdlib.h> /* EXIT_FAILURE, EXIT_SUCCESS, rand, srand */
#include		<time.h> /* time */
#include		<stdio.h> /* printf */
#include		<errno.h> /* errno, thanks cpt obvious */
#include		<lapin.h>

#define			LOOP_PER_SECONDS			50
#define			SCALE_PER_SECONDS			2.0
#define			DEGREE_PER_SECONDS			180.0

typedef struct		s_program
{
  char			*name;
  t_bunny_window	*win; /* (lapin/window.h) */
  t_bunny_picture	*pic; /* lapin/graphics.h) */
  t_bunny_position	pos; /* (lapin/placement.h) */
  int			loop_hz;
  double		pic_frame;
  double		pic_speed;
}			t_program;

t_bunny_response	key_response(t_bunny_event_state	state,
				     t_bunny_keysym		sym,
				     void			*data)
{
  char			**str = data;

  /* A key that was pressed has been released (lapin/events.h) */
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

static int		get_frame(t_bunny_picture		*pic,
				  double			*current_frame,
				  double			*speed)
{
  int			frame_count;

  frame_count = pic->buffer.width / pic->clip_width;
  if ((*current_frame += *speed) < 0)
    *current_frame += (double)frame_count;
  else if (*current_frame >= frame_count)
    *current_frame -= (double)frame_count;
  return (*current_frame);
}

t_bunny_response	main_loop(void				*data)
{
  t_program		*prog = data;
  double		scale;
  double		rotation;

  /* set the frame that will be displayed on screen when display() will be called */
  prog->pic->clip_x_position = prog->pic->clip_width
    * get_frame(prog->pic, &prog->pic_frame, &prog->pic_speed);

  /* how the scale growth per seconds */
  scale = SCALE_PER_SECONDS / prog->loop_hz;

  /* how the sprite turn per seconds */
  rotation = DEGREE_PER_SECONDS / prog->loop_hz;

  /* bunny_get_keyboard is in lapin/events.h */
  
  /* if the UP key is pressed, then increase the scale of the sprite */
  if (bunny_get_keyboard()[BKS_UP])
    prog->pic->scale.y = (prog->pic->scale.x += scale);
  /* if the DOWN key is pressed, then decrease the scale of the sprite */
  if (bunny_get_keyboard()[BKS_DOWN])
    prog->pic->scale.y = (prog->pic->scale.x -= scale);
  /* if the RIGHT key is pressed, then decrease the rotation */
  if (bunny_get_keyboard()[BKS_RIGHT])
    prog->pic->rotation -= rotation;
  /* if the LEFT key is pressed, then increase the rotation */
  if (bunny_get_keyboard()[BKS_LEFT])
    prog->pic->rotation += rotation;

  /* Say we want to stay in bunny_loop* (lapin/events.h) */
  return (GO_ON);
}

t_bunny_response	display(const void			*data)
{
  const t_program	*prog = data;

  /* clear the content of the window with BLACK color, with only 32/255 opacity */
  /* bunny_clear takes a t_bunny_buffer. Because a window contains a t_bunny_buffer, */
  /* you can use it with t_bunny_window this way */
  /* The second parameter is the color */
  /* (lapin/graphics.h, lapin/color.h) */
  bunny_fill(&prog->win->buffer, ALPHA(32, BLACK));

  /* draw the picture on screen at the sent position */
  /* the picture will only measure pic->clip_width, pic->clip height pixels */
  /* and be extracted from the position pic->clip_x_position, pic->clip_y_position */
  bunny_blit(&prog->win->buffer, prog->pic, &prog->pos);
  
  /* compute every drawing made on the window and display it on screen */
  /* the parameter is the window to refresh */
  /* if you do not do this, the window content will remain undefined */
  /* lapin/window.h) */
  bunny_display(prog->win);

  /* Say we want to stay in bunny_loop* (lapin/events.h) */
  return (GO_ON);
}

int			main(int				argc,
			     char				**argv)
{
  t_program		program;
  double		tmp;
  char			*p;

  if (argc != 3)
    {
      printf("%s: A picture file is required as first parameter and an animation speed as second (frame/s).\n", *argv);
      return (EXIT_FAILURE);
    }
  
  /* open a window */
  /* width on window, height of window, fullscreen? true, or false, name of the window */
  /* (lapin/window.h) */
  program.win = bunny_start(800, 600, false, "LibLapin - Sprite");
  if (program.win == NULL)
    {
      bunny_printlerr("Cannot open the window."); /* print litteral on stderr. (lapin/misc.h) */
      return (EXIT_FAILURE);
    }
  /* load a picture from a file (lapin/graphics.h) */
  if ((program.pic = bunny_load_picture(argv[1])) == NULL)
    {
      printf("%s: Cannot load file '%s'.\n", *argv, argv[1]);
      return (EXIT_FAILURE);
    }
  /* test that the size is correct for the program's use of the picture... */
  if (program.pic->buffer.height != 100 && program.pic->buffer.width % 100 != 0)
    {
      printf("%s: The picture file '%s' is not suit for this program.\n"
	     "The picture must be 100 pixel tall and its width must be a multiple of 100.\n",
	     *argv, argv[1]
	     );
      return (EXIT_FAILURE);
    }

  /* the main loop frequency */
  program.loop_hz = LOOP_PER_SECONDS;

  /* the first frame from the picture that will be displayed on screen */
  program.pic_frame = 0;

  /* get the animation speed parameter */
  tmp = strtof(argv[2], &p);
  if (p == argv[2])
    {
      printf("%s: The given value as animation speed is not a number.\n", *argv);
      return (EXIT_FAILURE);
    }
  /* check that no overflow or underflow happened */
  if (errno == ERANGE)
    {
      printf("%s: Invalid value given as animation speed.\n", *argv);
      return (EXIT_FAILURE);
    }
  /* check that the given speed is valid: must NOT be zero */
  if (fabs(tmp) < 0.1)
    {
      printf("%s: Animation speed is too close to zero (%f). Minimum is 0.1.\n",
	     *argv, tmp);
      return (EXIT_FAILURE);
    }
  /* compute how many frame are passing by per main loop, finally! */
  program.pic_speed = program.loop_hz / tmp;
  
  /* set the size of the picture that will be displayed on screen */
  /* this is not a resize! this is a crop! */
  program.pic->clip_width = 100;
  program.pic->clip_height = 100;

  /* prepare a placement structure to center the sprite on the window */
  program.pos.x = program.win->buffer.width / 2;
  program.pos.y = program.win->buffer.height / 2;

  /* place the axis of the sprite at the middle of the frame */
  /* */
  program.pic->origin.x = program.pic->clip_width / 2;
  program.pic->origin.y = program.pic->clip_height / 2;
  
  program.name = argv[0];

  /* init the random generator */
  srand(time(NULL));
  
  bunny_printl("Press escape to exit."); /* lapin/misc.h */

  /* set functions that will be called if event of specific types happened */
  /* keydown or keyup, clickdown or clickup, time passes and  */
  /* the main loop was called at lest one time during the previous delay */
  bunny_set_key_response(key_response); /* (lapin/events.h) */
  bunny_set_loop_main_function(main_loop); /* (lapin/events.h) */
  bunny_set_display_function(display); /* (lapin/events.h) */
    
  /* loop until until the exit button is pushed */
  /* The first parameter is the window, the second the number of frame per seconds */
  /* Also manage events by calling function given previously with bunny_set_*_response */
  /* functions and bunny_set_loop_main_function. */
  /* The third parameter is sent to these functions */
  /* (lapin/events.h) */
  bunny_loop(program.win, 100, &program);

  /* destroy the window */
  bunny_stop(program.win);
  return (EXIT_SUCCESS);
}

