/*
** *****************************************************************************
** damdoshi <damdoshi@eliminator>
** EFRITS - 30/03/2024 10:37:45
**
** - Oscidraw -
**
** *****************************************************************************
*/

#include		<stdlib.h>
#include		<time.h>
#include		"oscidraw.h"

void			move_sleep(void)
{
  bunny_usleep(1000);
}

void			put_pencil(t_program		*program,
				   int			x,
				   int			y)
{
  double		px = x / 200.0;
  double		py = y / 200.0;

  if (!program->lifted && program->screen)
    {
      unsigned int	col[2] = {WHITE, WHITE};
      t_bunny_position	pos[2] = {
	program->pencil,
	{x, y}
      };

      bunny_set_line(&program->screen->buffer, pos, col);
    }
  program->pencil.x = x;
  program->pencil.y = y;
  if (program->card)
    {
      program->card->digital_outputs[0] = true;
      program->card->analog_outputs[0] = px;
      program->card->analog_outputs[1] = py;
      bunny_vm110n_write(program->card);
    }
  program->lifted = false;
  move_sleep();
}

void			lift_pencil(t_program		*program)
{
  if (program->lifted)
    return ;
  program->lifted = true;
  if (program->card)
    {
      program->card->digital_outputs[0] = false;
      bunny_vm110n_write(program->card);
    }
  move_sleep();
}

void			set_pixel(t_program		*program,
				  int			x,
				  int			y)
{
  t_bunny_position	pos = {x, y};
  
  lift_pencil(program);
  put_pencil(program, x, y);
  if (program->screen)
    bunny_set_pixel(&program->screen->buffer, pos, WHITE);
  lift_pencil(program);
}

void			set_line(t_program		*program,
				 t_bunny_position	a,
				 t_bunny_position	b)
{
  put_pencil(program, a.x, a.y);
  put_pencil(program, b.x, b.y);
}

void			set_ball_speed(t_ball		*ball)
{
  double		angle = M_PI * (rand() % 1000000000 / 1000000000.0);
  double		speed = 3 * (rand() % 1000000000) / 1000000000 + 2.0;
  
  ball->spe.x = cos(angle) * speed;
  ball->spe.y = sin(angle) * speed;
}

void			set_ball(t_program		*program,
				 t_ball			*ball)
{
  lift_pencil(program);
  put_pencil(program, ball->pos.x - 2, ball->pos.y - 2);
  put_pencil(program, ball->pos.x + 2, ball->pos.y + 2);
  lift_pencil(program);
  put_pencil(program, ball->pos.x + 2, ball->pos.y - 2);
  put_pencil(program, ball->pos.x - 2, ball->pos.y + 2);
}

void			set_racket(t_program		*program,
				   t_racket		*rack)
{
  lift_pencil(program);
  put_pencil(program, rack->pos.x - RWIDTH / 2, rack->pos.y - RHEIGHT / 2);
  put_pencil(program, rack->pos.x + RWIDTH / 2, rack->pos.y - RHEIGHT / 2);
  put_pencil(program, rack->pos.x + RWIDTH / 2, rack->pos.y + RHEIGHT / 2);
  put_pencil(program, rack->pos.x - RWIDTH / 2, rack->pos.y + RHEIGHT / 2);
  put_pencil(program, rack->pos.x - RWIDTH / 2, rack->pos.y - RHEIGHT / 2);
}

void			move_racket(t_player		*player)
{
  for (size_t i = 1; i < player->nbr_racket && i < NBRCELL(player->racket); ++i)
    {
      int		dist = player->racket[i].pos.y - player->racket[i - 1].pos.y;
      
      if (dist < -3)
	player->racket[i].pos.y += -dist * 0.1;
      if (dist > +3)
	player->racket[i].pos.y -= +dist * 0.1;
    }
}

bool			collide_racket(t_racket		*rack,
				       t_ball		*ball)
{
  return (rack->pos.x - RWIDTH / 2 < ball->pos.x + 2
	  && rack->pos.x + RWIDTH / 2 > ball->pos.x - 2
	  && rack->pos.y - RHEIGHT / 2 < ball->pos.y + 2
	  && rack->pos.y + RHEIGHT / 2 > ball->pos.y - 2);
}

void			move_player(t_player		*player,
				    double		position)
{
  player->racket[0].pos.y = (position / 255.0) * BOARDHEIGHT;
}

t_bunny_response	key(t_bunny_event_state		state,
			    t_bunny_keysym		sym,
			    void			*data)
{
  (void)state;
  (void)sym;
  (void)data;
  return (SWITCH_CONTEXT);
}

t_bunny_response	loop(void			*data)
{
  (void)data;
  return (SWITCH_CONTEXT);
}

int			main(int			argc,
			     char			**argv)
{
  static t_program	program;
  double		now;
  double		previous;
  double		rem;
  bool			noscreen = false;
  bool			nocard = false;

  srand(time(NULL));
  if (argc == 2)
    {
      if (strcmp(argv[1], "noscreen") == 0)
	noscreen = true;
      if (strcmp(argv[1], "nocard") == 0)
	nocard = true;
    }
  if (!nocard)
    program.card = bunny_new_vm110n(0);
  if (!noscreen)
    {
      program.window = bunny_start(1920 / 2, 1080 / 2, false, "Oscidraw Pong");
      program.screen = bunny_new_picture(BOARDWIDTH, BOARDHEIGHT);
      program.screen->scale.x = (double)program.window->buffer.width / program.screen->buffer.width;
      program.screen->scale.y = (double)program.window->buffer.height / program.screen->buffer.height;
      bunny_set_key_response(key);
      bunny_set_loop_main_function(loop);
    }
  
  program.nbr_ball = 1;
  for (size_t i = 0; i < NBRCELL(program.ball); ++i)
    {
      program.ball[i].pos.x = BOARDWIDTH / 2;
      program.ball[i].pos.y = BOARDHEIGHT / 2;
      set_ball_speed(&program.ball[i]);
    }

  program.player[0].nbr_racket = 4;
  for (size_t i = 0; i < NBRCELL(program.player[i].racket); ++i)
    {
      program.player[0].racket[i].pos.x = (i * 2 + 1.5) * RWIDTH;
      program.player[0].racket[i].pos.y = BOARDHEIGHT / 2;
      program.player[0].racket[i].height = RHEIGHT;
    }
  program.player[1].nbr_racket = 4;
  for (size_t i = 0; i < NBRCELL(program.player[i].racket); ++i)
    {
      program.player[1].racket[i].pos.x = BOARDWIDTH - ((i * 2) + 1.5) * RWIDTH;
      program.player[1].racket[i].pos.y = BOARDHEIGHT / 2;
      program.player[1].racket[i].height = RHEIGHT;
    }

  now = previous = bunny_get_current_time();
  while (1)
    {
      if (program.screen)
	bunny_clear(&program.screen->buffer, BLACK);
      if (program.card)
	{
	  bunny_vm110n_read(program.card);
	  move_player(&program.player[0], program.card->analog_inputs[0]);
	  move_player(&program.player[1], program.card->analog_inputs[1]);
	}

      // move_player(&program.player[0], 0);
      // move_player(&program.player[1], 5);

      lift_pencil(&program);
      put_pencil(&program, 0, 0);
      put_pencil(&program, BOARDWIDTH, 0);
      put_pencil(&program, BOARDWIDTH, BOARDHEIGHT);
      put_pencil(&program, 0, BOARDHEIGHT);
      
      for (size_t i = 0; i < NBRCELL(program.player); ++i)
	for (size_t j = 0; j < NBRCELL(program.player[i].racket) && j < program.player[i].nbr_racket; ++j)
	  set_racket(&program, &program.player[i].racket[j]);

      for (size_t i = 0; i < NBRCELL(program.ball) && i < program.nbr_ball; )
	{
	  int		newx = program.ball[i].spe.x + program.ball[i].pos.x;
	  int		newy = program.ball[i].spe.y + program.ball[i].pos.y;

	  if (newx < 0 || newx >= BOARDWIDTH)
	    {
	      if (newx < 0)
		program.player[0].nbr_racket -= 1;
	      else
		program.player[1].nbr_racket -= 1;
	      program.ball[i].pos.x = BOARDWIDTH / 2;
	      program.ball[i].pos.y = BOARDHEIGHT / 2;
	      set_ball_speed(&program.ball[i]);
	      if (program.nbr_ball != 1)
		{
		  program.ball[i] = program.ball[program.nbr_ball - 1];
		  program.nbr_ball -= 1;
		  program.exchange = 0;
		}
	      continue ;
	    }

	  if (program.ball[i].spe.x < 0)
	    {
	      for (size_t j = 0; j < NBRCELL(program.player[0].racket) && j < program.player[0].nbr_racket; ++j)
		if (collide_racket(&program.player[0].racket[j], &program.ball[i]))
		  {
		    program.ball[i].spe.x *= -1;
		    if ((program.exchange += 1) % 3 == 0)
		      program.nbr_ball += program.nbr_ball + 1 < NBRCELL(program.ball) ? 1 : 0;
		  }
	    }
	  else
	    {
	      for (size_t j = 0; j < NBRCELL(program.player[1].racket) && j < program.player[1].nbr_racket; ++j)
		if (collide_racket(&program.player[1].racket[j], &program.ball[i]))
		  {
		    program.ball[i].spe.x *= -1;
		    if ((program.exchange += 1) % 3 == 0)
		      program.nbr_ball += program.nbr_ball + 1 < NBRCELL(program.ball) ? 1 : 0;
		  }
	    }
	  
	  program.ball[i].pos.x += program.ball[i].spe.x;
	  
	  if (newy < 0)
	    {
	      program.ball[i].pos.y = 0;
	      program.ball[i].spe.y *= -1;
	    }
	  if (newy >= BOARDHEIGHT)
	    {
	      program.ball[i].pos.y = BOARDHEIGHT - 1;
	      program.ball[i].spe.y *= -1;
	    }
	  program.ball[i].pos.y += program.ball[i].spe.y;
		  
	  set_ball(&program, &program.ball[i]);
	  i = i + 1;
	}

      if (bunny_get_keyboard()[BKS_Z] || bunny_get_keyboard()[BKS_W])
	if ((program.player[0].racket[0].pos.y -= 1) < RHEIGHT / 2)
	  program.player[0].racket[0].pos.y = RHEIGHT / 2;
      if (bunny_get_keyboard()[BKS_UP])
	if ((program.player[1].racket[0].pos.y -= 1) < RHEIGHT / 2)
	  program.player[1].racket[0].pos.y = RHEIGHT / 2;

      if (bunny_get_keyboard()[BKS_S])
	if ((program.player[0].racket[0].pos.y += 1) >= BOARDHEIGHT - RHEIGHT / 2)
	  program.player[0].racket[0].pos.y = BOARDHEIGHT - RHEIGHT / 2 - 1;
      if (bunny_get_keyboard()[BKS_DOWN])
	if ((program.player[1].racket[0].pos.y += 1) >= BOARDHEIGHT - RHEIGHT / 2)
	  program.player[1].racket[0].pos.y = BOARDHEIGHT - RHEIGHT / 2 - 1;

      move_racket(&program.player[0]);
      move_racket(&program.player[1]);

      // Position de repos du stylo
      set_pixel(&program, 1, 1);
      now = bunny_get_current_time();
      if ((rem = now - previous) < 1.0 / 20)
	bunny_usleep(rem * 1000000);
      previous = now;
      if (program.screen)
	{
	  bunny_loop(program.window, 100, NULL);
	  bunny_blit(&program.window->buffer, program.screen, NULL);
	  bunny_display(program.window);
	}
    }

  bunny_stop(program.window);
  bunny_delete_vm110n(program.card);
  return (0);
}

