
#include		<lapin.h>
#include		<math.h>

extern int		memory_check;

typedef struct		s_list
{
  t_bunny_picture	*pic;
  t_bunny_position	pos;
  double		speed;
  struct s_list		*next;
}			t_list;

typedef struct
{
  t_bunny_window	*win;
  t_bunny_picture	*pic;
  t_bunny_picture	*font;
  t_list		*list;
  int			cnt;
  int			triangle;
}			t_prog;

static t_bunny_response	key(t_bunny_event_state	state,
			    t_bunny_keysym	key,
			    void		*data)
{
  (void)state;
  (void)data;
  if (key == BKS_ESCAPE)
    return (EXIT_ON_SUCCESS);
  return (GO_ON);
}

void			say(t_bunny_picture		*font,
			    t_bunny_buffer		*pic,
			    const t_bunny_position	*p,
			    const char			*str,
			    bool			up)
{
  t_bunny_position	pos;
  t_bunny_position	siz;
  int			i;

  siz.x = (5 + 1) * font->scale.x;
  siz.y = 7 * font->scale.y;
  font->clip_y_position = 0;
  font->clip_width = 5;
  font->clip_height = 7;
  pos.x = p->x;
  pos.y = p->y;
  for (i = 0; str[i]; ++i)
    {
      if (str[i] == ' ')
	pos.x += siz.x;
      else
	{
	  font->clip_x_position = str[i] * 5;
	  bunny_blit(pic, font, &pos);
	  pos.x += siz.x;
	}
      if (!up)
	pos.y += 10;
      else
	pos.y -= 10;
    }
}

static t_bunny_response	mainloop(void		*p)
{
  t_prog		*prog;
  t_list		*new;
  t_bunny_position	pos[3];
  unsigned int		col[3];
  int			i;

  prog = p;
  bunny_fill(&prog->win->buffer, ALPHA(32, BLACK));
  if (prog->pic != NULL)
    {
      pos[0].x = (prog->win->buffer.width - prog->pic->buffer.width) / 2;
      pos[0].y = (prog->win->buffer.height - prog->pic->buffer.height) / 2;
      bunny_blit(&prog->win->buffer, prog->pic, &pos[0]);
    }

  prog->cnt = (prog->cnt + 5) % 360;

  if (prog->cnt % 25 == 0 && prog->triangle < 100)
    {
      prog->triangle += 1;
      new = bunny_malloc(sizeof(*new));
      if ((new->pic = bunny_new_picture(rand() % 300 + 300, rand() % 300 + 300)) == NULL)
	{
	  bunny_free(new);
	  return (EXIT_ON_ERROR);
	}
      new->pos.x = rand() % prog->win->buffer.width;
      new->pos.y = rand() % prog->win->buffer.height;
      new->pic->origin.x = new->pic->buffer.width / 2;
      new->pic->origin.y = new->pic->buffer.height / 2;
      while ((new->speed = (rand() % 3000 - 1500) / 500.0) == 0);
      new->next = prog->list;
      prog->list = new;
      for (i = 0; i < 3; ++i)
	{
	  pos[i].x = (rand() % new->pic->buffer.width + new->pic->buffer.width) / 2;
	  pos[i].y = (rand() % new->pic->buffer.height + new->pic->buffer.height) / 2;
	  col[i] = rand() | BLACK;
	}
      bunny_set_polygon(&new->pic->buffer, pos, col);
    }
  for (new = prog->list; new != NULL; new = new->next)
    {
      new->pic->rotation += new->speed;
      bunny_blit(&prog->win->buffer, new->pic, &new->pos);
    }

  if (prog->font != NULL)
    {
      pos[0].x = (prog->win->buffer.width - prog->font->scale.x * 6 * 14) / 2;
      pos[0].y = prog->win->buffer.height * (sin( M_PI * prog->cnt / 180.0) * 0.75 + 0.5);
      say(prog->font, &prog->win->buffer, &pos[0], "Lapins Noirs!\x7F", prog->cnt < 90 || prog->cnt > 270);
    }


  bunny_display(prog->win);
  return (GO_ON);
}

static int		clean(t_prog		*prog,
			      int		out)
{
  t_list		*new;
  t_list		*mem;;

  for (new = prog->list; mem != NULL; new = mem)
    {
      bunny_delete_clipable(new->pic);
      mem = new->next;
      bunny_free(new);
    }
  if (prog->pic != NULL)
    bunny_delete_clipable(prog->pic);
  if (prog->font != NULL)
    bunny_delete_clipable(prog->font);
  bunny_stop(prog->win);
  return (out);
}

int			main(void)
{
  static t_prog		prog;

  memory_check = 1;
  //if ((prog.win = bunny_start(800, 600, false, "Lapins Noirs!")) == NULL)
  if ((prog.win = bunny_start(1280, 720, false, "Lapins Noirs!")) == NULL)
    return (EXIT_FAILURE);
  prog.pic = bunny_load_picture("bigbunny.png");
  if ((prog.font = bunny_load_picture("font.png")) != NULL)
    {
      prog.font->scale.x = 4;
      prog.font->scale.y = 4;
    }
  prog.pic->color_mask.full = 0x80808080;

  prog.cnt = 0;
  prog.list = NULL;
  prog.triangle = 0;
  bunny_set_key_response(key);
  bunny_set_loop_main_function(mainloop);
  if (bunny_loop(prog.win, 60, &prog) == EXIT_ON_ERROR)
    return (clean(&prog, EXIT_FAILURE));
  return (clean(&prog, EXIT_SUCCESS));
}

