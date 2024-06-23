/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2022
** EFRITS SAS 2022-2023
** Pentacle Technologie 2008-2023
**
** Triangle collision
*/

#include		<lapin.h>
#include		<time.h>

unsigned int		col[2] = {WHITE, WHITE};
unsigned int		scol[2] = {PINK2, PINK2};
t_bunny_position	pos[4];
t_bunny_size		siz = {1440, 900};
t_bunny_window		*win;
bool			cold;

t_bunny_response	key(t_bunny_event_state	state,
			    t_bunny_keysym	sym,
			    void		*a)
{
  (void)a;
  (void)state;
  if (sym == BKS_ESCAPE)
    return (EXIT_ON_SUCCESS);
  return (GO_ON);
}

bool			triangle_collision(t_bunny_position	*triangle,
					   t_bunny_position	mos)
{
  int			neg = 0;
  int			pos = 0;

  for (int i = 0; i < 3; ++i)
    {
      t_bunny_position	mt[2];
      double		z;

      mt[0].x = mos.x - triangle[i].x;
      mt[0].y = mos.y - triangle[i].y;
      mt[1].x = mos.x - triangle[i + 1].x;
      mt[1].y = mos.y - triangle[i + 1].y;
      z = mt[0].x * mt[1].y - mt[1].x * mt[0].y;
      if (fabs(z) < 0.0001)
	{
	  neg += 1;
	  pos += 1;
	}
      else if (z < 0)
	neg += 1;
      else
	pos += 1;
    }
  return (neg == 3 || pos == 3);
}

t_bunny_response	loop(void		*a)
{
  t_bunny_position	mpos = *bunny_get_mouse_position();

  (void)a;
  cold = triangle_collision(&pos[0], mpos);
  return (GO_ON);
}

t_bunny_response	move(const t_bunny_position *ref,
			     void		*a)
{
  (void)ref;
  (void)a;
  return (GO_ON);
}

t_bunny_response	display(void		*a)
{
  t_bunny_position	barycenter = {0, 0};
  t_bunny_position	rad = {5, 5};
  
  (void)a;
  bunny_clear(&win->buffer, BLACK);
  for (int i = 0; i < 3; ++i)
    {
      barycenter.x += pos[i].x;
      barycenter.y += pos[i].y;
      bunny_set_line(&win->buffer, &pos[i], cold ? &scol[0] : &col[0]);
    }
  barycenter.x /= 3;
  barycenter.y /= 3;
  bunny_set_disk(&win->buffer, barycenter, rad, cold ? scol[0] : col[0], BLACK, 0);
  bunny_display(win);
  return (GO_ON);
}

int			main(void)
{
  double		tier = (2 * M_PI / 3) * 10000.0;
  double		ang = 0;
  int			dir = time(NULL);
  int			i;

  if (dir % 2)
    puts("Trig");
  else
    puts("Anti Trig");
  srand(dir / 2);
  win = bunny_start(siz.x, siz.y, false, "Triangle Collision");
  for (i = 0; i < 3; ++i)
    {
      if (dir % 2)
	ang += fmod(rand(), tier) / 10000.0;
      else
	ang -= fmod(rand(), tier) / 10000.0;
      pos[i].x = (1 + cos(ang) * 0.5) * siz.x / 2;
      pos[i].y = (1 + sin(ang) * 0.5) * siz.y / 2;
    }
  pos[3] = pos[0];

  bunny_set_key_response(key);
  bunny_set_move_response(move);
  bunny_set_loop_main_function(loop);
  bunny_set_display_function(display);
  bunny_loop(win, 50, NULL);
  bunny_stop(win);
  return (0);
}
