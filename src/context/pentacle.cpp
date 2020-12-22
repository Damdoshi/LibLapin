// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include			"lapin_private.h"

#define				RAD(x)						(M_PI * x / 180.0)

struct				vertex_array
{
  size_t			length;
  t_bunny_vertex		vertex[30]; // 5 branches, 2 triangles par branches, 3 coordonnées par triangle
};

static struct vertex_array	gl_normal_pentacle;
static struct vertex_array	gl_pentacle;

typedef enum			e_anim_state
  {
    BEFORE_ANIMATION,
    FALLING,
    PAUSE,
    TRANSFORMATION,
    NEW_PAUSE,
    SHIFT_LEFT,
    TEXT_DISPLAY,
    NEW_NEW_PAUSE,
    FINAL_BLACK,
    LAST_AS
  }				t_anim_state;

static void			turn(t_bunny_accurate_position			*p,
				     double					m)
{
  t_bunny_accurate_position	n;
  double			angle = M_PI * m / 180.0;

  n.x = p->x * cos(angle) - p->y * sin(angle);
  n.y = p->x * sin(angle) + p->y * cos(angle);
  p->x = n.x;
  p->y = n.y;
}


static void			square(int					x,
				       int					y,
				       int					w,
				       int					h,
				       t_bunny_buffer				*clip)
{
  t_bunny_position		pos[3];
  unsigned int			col[3];
  t_bunny_color			color;

  color.full = RED;
  color.argb[RED_CMP] = 128;

  pos[0].x = x;
  pos[0].y = y;
  pos[1].x = x;
  pos[1].y = y + h;
  pos[2].x = x + w;
  pos[2].y = y;
  col[0] = BLACK;
  col[1] = BLACK;
  col[2] = color.full;
  bunny_set_polygon(clip, &pos[0], &col[0]);

  pos[0].x = x + w;
  pos[0].y = y;
  pos[1].x = x;
  pos[1].y = y + h;
  pos[2].x = x + w;
  pos[2].y = y + h;
  col[0] = color.full;
  col[1] = BLACK;
  col[2] = color.full;
  bunny_set_polygon(clip, &pos[0], &col[0]);
}

static t_bunny_response		pentacle_key(t_bunny_event_state		state,
					     t_bunny_keysym			sym,
					     struct bunny_pentacle_screen	*bss)
{
  double			pitch;

  if (sym == BKS_SPACE)
    {
      if (state == GO_DOWN)
	pitch = 3;
      else
	pitch = 1;
      bunny_sound_pitch(&bss->jingle->sound, pitch);
    }
  if ((sym == BKS_ESCAPE || sym == BKS_RETURN) && state == GO_DOWN)
    bss->animation_step = LAST_AS;
  return (GO_ON);
}

static t_bunny_response		pentacle_click(t_bunny_event_state		state,
					       t_bunny_mouse_button		button,
					       struct bunny_pentacle_screen	*bss)
{
  (void)state;
  (void)button;
  if (state == GO_UP)
    return (GO_ON);
  bss->animation_step = LAST_AS;
  return (GO_ON);
}

static void			step(struct bunny_pentacle_screen		*bss)
{
  bss->time_counter = 0;
  bss->animation_step += 1;
}

static t_bunny_response		pentacle_loop(struct bunny_pentacle_screen	*bss)
{
  double			mulspeed = bunny_get_keyboard()[BKS_SPACE] ? 3 : 1;
  double			speed = mulspeed * (1.0 / bunny_get_frequency());

  bss->time_counter += speed;
  switch (bss->animation_step)
    {
    case BEFORE_ANIMATION:
      if (bss->time_counter >= 0.5)
	{
	  if (bss->jingle)
	    bunny_sound_play(&bss->jingle->sound);
	  step(bss);
	}
      return (GO_ON);

    case FALLING:
      if (bss->time_counter >= 0.75)
	step(bss);
      return (GO_ON);
    case PAUSE:
      if (bss->time_counter >= 0.5)
	step(bss);
      return (GO_ON);
    case TRANSFORMATION:
      if (bss->time_counter >= 0.2)
	step(bss);
      return (GO_ON);
    case NEW_PAUSE:
      if (bss->time_counter >= 0.5)
	step(bss);
      return (GO_ON);
    case SHIFT_LEFT:
    case TEXT_DISPLAY:
      if (bss->time_counter >= 0.2)
	step(bss);
      return (GO_ON);
    case NEW_NEW_PAUSE:
    case FINAL_BLACK:
      if (bss->time_counter >= 1.0)
	step(bss);
      return (GO_ON);
    default:
      if (bss->jingle)
	bunny_sound_stop(&bss->jingle->sound);
      return (SWITCH_CONTEXT);
    }
  return (GO_ON);
}

static void			center_vertices(t_bunny_vertex_array		*v,
						t_bunny_size			siz,
						t_bunny_position		p,
						double				sizcoef)
{
  if (siz.x < siz.y)
    siz.y = siz.x;
  else
    siz.x = siz.y;

  for (size_t i = 0; i < v->length; ++i)
    {
      v->vertex[i].pos.x *= siz.y * sizcoef;
      v->vertex[i].pos.y *= siz.y * sizcoef;
      v->vertex[i].pos.x += p.x;
      v->vertex[i].pos.y += p.y;
    }
}

static t_bunny_response		pentacle_display(struct bunny_pentacle_screen *bss)
{
  char				pentacle_mem[sizeof(gl_normal_pentacle)];
  t_bunny_vertex_array		*pentacle = (t_bunny_vertex_array*)&pentacle_mem;
  t_bunny_color			color;
  size_t			i;

  bunny_fill(bss->head.screen, ALPHA(64, BLACK));

  if (bss->animation_step < NEW_PAUSE)
    memcpy(pentacle, &gl_normal_pentacle, sizeof(gl_normal_pentacle));
  else
    memcpy(pentacle, &gl_pentacle, sizeof(gl_pentacle));
  switch (bss->animation_step)
    {
    case BEFORE_ANIMATION:
      bunny_clear(bss->head.screen, BLACK);
      break ;
    case FALLING:
      color.full = BLACK;
      if (bss->time_counter < 0.25)
	color.argb[RED_CMP] = 128 * bss->time_counter / 0.25;
      else
	color.argb[RED_CMP] = 128;
      for (i = 0; i < pentacle->length; ++i)
	{
	  turn(&pentacle->vertex[i].pos, (1.0 - bss->time_counter / 0.75) * bss->falling_rotation);
	  pentacle->vertex[i].color = color.full;
	}
      [[fallthrough]];
    case PAUSE:
      {
	double coef;

	if (bss->animation_step == FALLING)
	  coef = (1.0 - bss->time_counter / 0.75) * 2.0 + 0.33;
	else
	  coef = 0.33;
	center_vertices(pentacle, bss->size_of_screen, bss->middle_of_screen, coef);
	bunny_set_geometry(bss->head.screen, BGY_TRIANGLES, pentacle, NULL);
	break ;
      }
    case TRANSFORMATION:
      if (bss->time_counter == 0)
	bunny_fill(bss->head.screen, RED);
      for (i = 0; i < pentacle->length; ++i)
	{
	  pentacle->vertex[i].pos.x =
	    (gl_pentacle.vertex[i].pos.x - gl_normal_pentacle.vertex[i].pos.x) * (bss->time_counter / 0.2)
	    + gl_normal_pentacle.vertex[i].pos.x
	    ;
	  pentacle->vertex[i].pos.y =
	    (gl_pentacle.vertex[i].pos.y - gl_normal_pentacle.vertex[i].pos.y) * (bss->time_counter / 0.2)
	    + gl_normal_pentacle.vertex[i].pos.y
	    ;
	}
      [[fallthrough]];
    case NEW_PAUSE:
      {
	center_vertices(pentacle, bss->size_of_screen, bss->middle_of_screen, 0.33);
	bunny_set_geometry(bss->head.screen, BGY_TRIANGLES, pentacle, NULL);
	break ;
      }
    case SHIFT_LEFT:
    case TEXT_DISPLAY:
    case NEW_NEW_PAUSE:
      {
	t_bunny_size pos;
	double dest;
	double step;
	double ori;

	if (bss->animation_step == SHIFT_LEFT)
	  step = bss->time_counter / 0.2;
	else
	  step = 1;

	ori = bss->middle_of_screen.x;
	dest = (bss->size_of_screen.x - (bss->size_of_screen.y * 0.33 * 2)) / 2;
	pos.x = (dest - ori) * step + ori;
	pos.y = bss->middle_of_screen.y;
	center_vertices(pentacle, bss->size_of_screen, pos, 0.33);
	bunny_set_geometry(bss->head.screen, BGY_TRIANGLES, pentacle, NULL);
	if (bss->animation_step < TEXT_DISPLAY)
	  break ;
	if (bss->animation_step == TEXT_DISPLAY)
	  bss->text->clipable.clip_width = (bss->time_counter / 0.2) * bss->text->clipable.buffer.width;
	square(bss->text->clipable.position.x,
	       bss->text->clipable.position.y - bss->text->clipable.buffer.height * 0.05,
	       bss->text->clipable.clip_width,
	       bss->text->clipable.buffer.height * 0.1,
	       bss->head.screen
	       );
	  square(bss->text->clipable.position.x,
		 bss->text->clipable.position.y - bss->text->clipable.buffer.height * 0.05 + bss->text->clipable.buffer.height,
		 bss->text->clipable.clip_width,
		 bss->text->clipable.buffer.height * 0.1,
		 bss->head.screen
		 );
	bunny_blit(bss->head.screen, &bss->text->clipable, NULL);
      }
      [[fallthrough]];
    case FINAL_BLACK:
    default:
      break ;
    }
  if (bss->head.subcontext.display)
    return (bss->head.subcontext.display(bss));
  bunny_display((t_bunny_window*)bss->head.screen);
  return (GO_ON);
}

void				spread_coords(struct vertex_array		*vec,
					      t_bunny_accurate_position		*coords,
					      double				thick,
					      size_t				len)
{
  t_bunny_accurate_position	farr;
  t_bunny_accurate_position	farr_close;
  t_bunny_accurate_position	here;
  t_bunny_accurate_position	here_close;

  int				i;
  int				j;

  for (i = 0; i < 5; ++i)
    coords[i].x -= 90; // Pointe vers le haut

  for (i = 0, j = 0; i < 5; ++i)
    {
      here.x = -cos(RAD(coords[i].x)) * coords[i].y;
      here.y = sin(RAD(coords[i].x)) * coords[i].y;
      here_close.x = here.x * thick;
      here_close.y = here.y * thick;

      farr.x = -cos(RAD(coords[(i + 2) % len].x)) * coords[(i + 2) % len].y;
      farr.y = sin(RAD(coords[(i + 2) % len].x)) * coords[(i + 2) % len].y;
      farr_close.x = farr.x * thick;
      farr_close.y = farr.y * thick;

      vec->vertex[j++].pos = here;
      vec->vertex[j++].pos = farr;
      vec->vertex[j++].pos = farr_close;
      vec->vertex[j++].pos = here;
      vec->vertex[j++].pos = here_close;
      vec->vertex[j++].pos = farr_close;
    }
  for (i = 0; i < (int)vec->length; ++i)
    {
      t_bunny_color		col;

      col.full = BLACK;
      col.argb[RED_CMP] = 128;
      vec->vertex[i].color = col.full;
    }
}


static t_bunny_response		pentacle_entering(struct bunny_pentacle_screen *bss)
{
  t_bunny_size			font_size;
  int				i;

  bss->animation_step = BEFORE_ANIMATION;
  bss->time_counter = 0.0;
  bss->size_of_screen.x = bss->head.screen->width;
  bss->size_of_screen.y = bss->head.screen->height;
  bss->middle_of_screen.x = bss->head.screen->width / 2;
  bss->middle_of_screen.y = bss->head.screen->height / 2;
  bss->jingle_played = false;

  font_size.x = bss->size_of_screen.x * 0.10;
  font_size.y = bss->size_of_screen.y * 0.08;
  if (bss->text == NULL)
    if ((bss->text = bunny_load_font
	 (bss->size_of_screen.x * 0.45, font_size.y * 3,
	  bss->font_file, &font_size)) == NULL)
      return (EXIT_ON_ERROR);
  bss->text->string = "Pentacle\nTechnologie";
  bss->text->clipable.color_mask.full = RED;
  bss->text->offset.x = 10;
  bss->text->offset.y = (bss->text->clipable.clip_height - 2 * font_size.y) / 2 - 10;
  bunny_draw(&bss->text->clipable);
  bss->text->clipable.position.x = bss->middle_of_screen.x;
  bss->text->clipable.position.y = (bss->size_of_screen.y - bss->text->clipable.buffer.height) / 2;
  bss->text->clipable.clip_width = 0;

  if (bss->jingle_sound_file)
    {
      if (bss->jingle == NULL)
	if ((bss->jingle = bunny_load_effect(bss->jingle_sound_file)) == NULL)
	  {
	    bunny_delete_clipable(&bss->text->clipable);
	    return (EXIT_ON_ERROR);
	  }
    }
  else
    bss->jingle = NULL;

  if (gl_normal_pentacle.length == 0)
    {
      double			thick;
      t_bunny_accurate_position coords[5] = // X pour l'angle, Y pour la distance
	{
	 {-10, 0.65},
	 {59, 1.00},
	 {135, 1.2},
	 {216, 1.00},
	 {261, 0.65}
	};

      thick = 1.0 - bss->thickness;
      gl_pentacle.length = gl_normal_pentacle.length = NBRCELL(gl_normal_pentacle.vertex);
      spread_coords(&gl_pentacle, &coords[0], thick, NBRCELL(coords));
      for (i = 0; i < NBRCELL(coords); ++i)
	{
	  coords[i].x = i * (360.0 / 5.0);
	  coords[i].y = 1.0;
	}
      spread_coords(&gl_normal_pentacle, &coords[0], thick, NBRCELL(coords));
    }
  return (GO_ON);
}

static void			pentacle_leaving(t_bunny_response		resp,
						 struct bunny_pentacle_screen *bss)
{
  (void)resp;
  if (bss->jingle)
    bunny_delete_sound(&bss->jingle->sound);
  if (bss->text)
    bunny_delete_clipable(&bss->text->clipable);
}

const t_bunny_context		gl_bunny_pentacle_context =
  {
   (t_bunny_key)pentacle_key,
   bunny_context_type,
   (t_bunny_click)pentacle_click,
   bunny_context_move,
   bunny_context_wheel,
   bunny_context_joy_connect,
   bunny_context_joy_button,
   bunny_context_joy_axis,
   bunny_context_get_focus,
   bunny_context_lost_focus,
   bunny_context_resize,
   (t_bunny_loop)pentacle_loop,
   (t_bunny_display)pentacle_display,
   bunny_context_close,
   NULL,
   bunny_context_message,
   bunny_context_connect,
   (t_bunny_loop)pentacle_entering,
   (t_bunny_leaving_context)pentacle_leaving,
   bunny_context_async_computation,
   bunny_context_event_response
  };
