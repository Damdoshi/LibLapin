// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include			"lapin_private.h"

typedef enum			e_anim_state
  {
    BEFORE_ANIMATION,
    FALLING,
    ROPE_TENSE,
    ROPE_SHAKE,
    GET_UP,
    STILL_WITH_TITLE,
    GO_AWAY,
    AFTER_ANIMATION,
    LAST_AS
  }				t_anim_state;

static t_bunny_response		splash_key(t_bunny_event_state		state,
					   t_bunny_keysym		sym,
					   struct bunny_splash_screen	*bss)
{
  double			pitch;

  if (sym == BKS_SPACE)
    {
      if (state == GO_DOWN)
	pitch = 3;
      else
	pitch = 1;
      bunny_sound_pitch(&bss->jingle->sound, pitch);
      bunny_sound_pitch(&bss->boom->sound, pitch);
      bunny_sound_pitch(&bss->falling->sound, pitch);
      bunny_sound_pitch(&bss->outch->sound, pitch);
    }
  if (sym == BKS_ESCAPE && state == GO_DOWN)
    bss->animation_step = LAST_AS;
  return (GO_ON);
}

static t_bunny_response		splash_click(t_bunny_event_state	state,
					     t_bunny_mouse_button	button,
					     struct bunny_splash_screen	*bss)
{
  (void)state;
  (void)button;
  bss->animation_step = LAST_AS;
  return (GO_ON);
}

static void			step(struct bunny_splash_screen		*bss)
{
  bss->time_counter = 0;
  bss->animation_step += 1;
}

static t_bunny_response		splash_loop(struct bunny_splash_screen	*bss)
{
  double			mulspeed = bunny_get_keyboard()[BKS_SPACE] ? 3 : 1;
  double			speed = mulspeed * (1.0 / bunny_get_frequency());

  bss->time_counter += speed;
  switch (bss->animation_step)
    {
    case BEFORE_ANIMATION:
      if (bss->time_counter >= 2.0)
	{
	  bunny_sound_play(&bss->falling->sound);
	  step(bss);
	}
      return (GO_ON);

    case FALLING:
      if (fabs(bss->bunny->rotation) > 5.0 * M_PI / 180.0)
	bss->bunny->rotation *= 0.99;
      else
	bss->bunny->rotation = 0;

      bss->bunny->position.y += speed * bss->bunny_fall_speed;
      if (bss->time_counter >= 1.0 * 0.2 && bss->jingle_played == false)
	{
	  bunny_sound_play(&bss->jingle->sound);
	  bss->jingle_played = true;
	}
      if (bss->time_counter >= 1.0)
	step(bss);
      return (GO_ON);

    case ROPE_TENSE:
      bss->bunny->rotation = 0;
      bss->bunny->position.y += speed * bss->bunny_fall_speed;
      if ((bss->rope_amplitude *= 0.9) < 30)
	{
	  bunny_sound_play(&bss->boom->sound);
	  bunny_sound_play(&bss->outch->sound);
	  bss->rope_wave_length = 1.5 * M_PI / bss->head.screen->height;
	  step(bss);
	}
      return (GO_ON);

    case ROPE_SHAKE:
      bss->shake_amplitude += 1 * mulspeed;
      if ((bss->rope_amplitude *= 0.95) < 1)
	{
	  bss->rope_amplitude = 100;
	  bss->rope_wave_length = 0.1 * M_PI / bss->head.screen->height;
	  bss->shake_amplitude = 0;
	  step(bss);
	}
      return (GO_ON);

    case GET_UP:
      bss->shake_amplitude += 0.1 * mulspeed;
      bss->bunny->position.y -= speed * bss->up_speed;
      if (bss->bunny->position.y < bss->head.screen->height * 0.28)
	step(bss);
      return (GO_ON);

    case STILL_WITH_TITLE:
      bss->shake_amplitude += 0.1 * mulspeed;
      if (bss->time_counter >= 3 && fabs(sin(bss->shake_amplitude)) < 0.4)
	{
	  bss->shake_amplitude = 0;
	  step(bss);
	}
      return (GO_ON);

    case GO_AWAY:
      bss->title->position.y += speed * bss->up_speed;
      bss->title->scale.x *= 1.1;
      bss->title->scale.y *= 1.1;
      bss->bunny->position.y -= speed * bss->up_speed * 2;
      if (bss->bunny->position.y <
	  -bss->bunny->buffer.height * bss->bunny->scale.y * 1.2 &&
	  bss->title->position.y > bss->head.screen->height * 1.2)
	step(bss);
      return (GO_ON);

    case AFTER_ANIMATION:
      if (bss->time_counter >= 1.0)
	step(bss);
      return (GO_ON);

    default:
      bunny_sound_stop(&bss->jingle->sound);
      bunny_sound_stop(&bss->boom->sound);
      bunny_sound_stop(&bss->falling->sound);
      bunny_sound_stop(&bss->outch->sound);
      return (SWITCH_CONTEXT);
    }
  return (GO_ON);
}

static double		exp(double					x,
			    double					limit,
			    double					max_value)
{
  return (x * x * (max_value / (limit * limit)));
}


static t_bunny_response		splash_display(struct bunny_splash_screen *bss)
{
  int				init, y;

  if (bss->animation_step < GO_AWAY)
    bunny_clear(bss->head.screen, BLACK);
  else
    bunny_clear(bss->head.screen, ALPHA(16, BLACK));

  switch (bss->animation_step)
    {
    case BEFORE_ANIMATION:
      break ;
    case FALLING:
    case ROPE_TENSE:
    case ROPE_SHAKE:
      init = y = bss->bunny->position.y;
      while (y > 0)
	{
	  bss->rope->position.x =
	    bss->bunny->position.x
	    + sin((init - y) * bss->rope_wave_length)
	    * bss->rope_amplitude
	    * cos(bss->shake_amplitude)
	    ;
	  bss->rope->position.y = y;
	  bunny_blit(bss->head.screen, bss->rope, NULL);
	  y -= 1;
	}
      bunny_blit(bss->head.screen, bss->bunny, NULL);
      break ;

    case GET_UP:
    case STILL_WITH_TITLE:
    case GO_AWAY:
      for (init = y = -bss->bunny->buffer.height * bss->bunny->scale.y * 1.2;
	   y < bss->bunny->position.y; ++y)
	{
	  bss->rope->position.x =
	    bss->middle_of_screen
	    + exp(y - init, bss->bunny->position.y, bss->rope_amplitude / 10)
	    * sin(bss->shake_amplitude)
	    ;
	  bss->rope->position.y = y;
	  bunny_blit(bss->head.screen, bss->rope, NULL);
	}
      bss->bunny->position.x = bss->rope->position.x;
      bss->bunny->position.y = bss->bunny->position.y;
      bss->bunny->rotation = -sin(bss->shake_amplitude) * 5;

      bunny_blit(bss->head.screen, bss->bunny, NULL);

      if (bss->animation_step != GO_AWAY)
	{
	  bss->title->position.x = bss->middle_of_screen;
	  bss->title->position.y =
	    bss->bunny->position.y
	    - bss->bunny->origin.y * bss->bunny->scale.y
	    + bss->bunny->buffer.height * bss->bunny->scale.y
	    ;
	}
      bunny_blit(bss->head.screen, bss->title, NULL);
      break ;

    default:
      break ;
    }
  if (bss->head.subcontext.display)
    return (bss->head.subcontext.display(bss));
  bunny_display((t_bunny_window*)bss->head.screen);
  return (GO_ON);
}

static t_bunny_response		splash_entering(struct bunny_splash_screen *bss)
{
  if ((bss->bunny = bunny_load_picture(bss->bunny_picture_file)) == NULL)
    goto DeleteBunny;
  if ((bss->rope = bunny_load_picture(bss->rope_picture_file)) == NULL)
    goto DeleteRope;
  if ((bss->title = bunny_load_picture(bss->title_picture_file)) == NULL)
    goto DeleteTitle;
  if ((bss->jingle = bunny_load_effect(bss->jingle_sound_file)) == NULL)
    goto DeleteJingle;
  if ((bss->boom = bunny_load_effect(bss->boom_sound_file)) == NULL)
    goto DeleteBoom;
  if ((bss->outch = bunny_load_effect(bss->outch_sound_file)) == NULL)
    goto DeleteOutch;
  if ((bss->falling = bunny_load_effect(bss->falling_sound_file)) == NULL)
    goto DeleteFalling;

  bss->animation_step = BEFORE_ANIMATION;
  bss->time_counter = 0.0;
  bss->middle_of_screen = bss->head.screen->width / 2;
  bss->jingle_played = false;

  bss->bunny->position.x = bss->middle_of_screen;
  bss->bunny->position.y = -bss->bunny->buffer.height * bss->bunny->scale.y;
  bss->bunny_fall_speed =
    (1.3 * bss->head.screen->height + bss->bunny->buffer.height * bss->bunny->scale.y)
    / 1.0;
  bss->rope_wave_length = (2 * M_PI) / 1080.0;
  bss->bunny->rotation = 45;
  bss->rope_amplitude = 100;
  bss->shake_amplitude = 0;
  bss->up_speed =
    (bss->head.screen->height + bss->bunny->buffer.height * bss->bunny->scale.y)
    / 2.0;

  return (GO_ON);

 DeleteFalling:
  bunny_delete_sound(&bss->outch->sound);
 DeleteOutch:
  bunny_delete_sound(&bss->boom->sound);
 DeleteBoom:
  bunny_delete_sound(&bss->jingle->sound);
 DeleteJingle:
  bunny_delete_clipable(bss->title);
 DeleteTitle:
  bunny_delete_clipable(bss->rope);
 DeleteRope:
  bunny_delete_clipable(bss->bunny);
 DeleteBunny:
  return (EXIT_ON_ERROR);
}

static void			splash_leaving(t_bunny_response		resp,
					       struct bunny_splash_screen *bss)
{
  (void)resp;
  bunny_delete_sound(&bss->outch->sound);
  bunny_delete_sound(&bss->boom->sound);
  bunny_delete_sound(&bss->jingle->sound);
  bunny_delete_clipable(bss->title);
  bunny_delete_clipable(bss->rope);
  bunny_delete_clipable(bss->bunny);
}

const t_bunny_context		gl_bunny_splash_context =
  {
    (t_bunny_key)splash_key,
    NULL,
    (t_bunny_click)splash_click,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    (t_bunny_loop)splash_loop,
    (t_bunny_display)splash_display,
    NULL,
    NULL,
    NULL,
    NULL,
    (t_bunny_loop)splash_entering,
    (t_bunny_leaving_context)splash_leaving
  };
