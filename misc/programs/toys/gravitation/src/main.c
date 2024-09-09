
#include	<lapin.h>

typedef struct	s_par
{
  t_bunny_accurate_position pos;
  t_bunny_accurate_position spd;
  double	weight;
}		t_par;
t_bunny_window *win;
t_par		par[3];
double		grav = 6.67430e-11;

t_bunny_response key(t_bunny_event_state state, t_bunny_keysym sym, void *a)
{
  (void)a;
  if (state == GO_UP)
    return (GO_ON);
  if (sym == BKS_ESCAPE)
    return (EXIT_ON_SUCCESS);
  if (sym == BKS_UP)
    grav *= 2;
  if (sym == BKS_DOWN)
    grav /= 2;
  printf("Grav %f\n", grav);
  return (GO_ON);
}

t_bunny_response loop(void *n)
{
  (void)n;
  for (int i = 0; i < NBRCELL(par); ++i)
    for (int j = i + 1; j < NBRCELL(par); ++j)
      {
	double dist = sqrt(pow(par[i].pos.y - par[j].pos.y, 2) + pow(par[i].pos.x - par[j].pos.x, 2));
	double strength = (grav * par[i].weight * par[j].weight) / (dist * dist);
	double ang = atan2(par[i].pos.y - par[j].pos.y, par[i].pos.x - par[j].pos.x);

	par[i].spd.x += cos(ang) * strength;
	par[i].spd.y += sin(ang) * strength;
      }
  for (int i = 0; i < NBRCELL(par); ++i)
    {
      par[i].pos.x += par[i].spd.x;
      if (par[i].pos.x < 0 || par[i].pos.x > win->buffer.width)
	par[i].spd.x *= -1;
      par[i].pos.y += par[i].spd.y;
      if (par[i].pos.y < 0 || par[i].pos.y > win->buffer.height)
	par[i].spd.y *= -1;
    }
  return (GO_ON);
}

t_bunny_response display(void *n)
{
  (void)n;
  bunny_clear(&win->buffer, BLACK);
  for (int i = 0; i < NBRCELL(par); ++i)
    {
      t_bunny_position pos = {(int)par[i].pos.x, (int)par[i].pos.y};
      t_bunny_position rad = {5, 5};

      bunny_set_disk(&win->buffer, pos, rad, WHITE, WHITE, 0);
    }
  bunny_display(win);
  return (GO_ON);
}

int		main(void)
{
  win = bunny_start(1440, 900, false, "Window");
  int		i;

  par[0].pos.x = 1440 / 2.0;
  par[0].pos.y = 900 / 2.0;
  par[0].spd.x = 0;
  par[0].spd.y = 0;
  par[0].weight = 1e18;
  for (i = 1; i < NBRCELL(par); ++i)
    {
      par[i].pos.x = rand() % 1440;
      par[i].pos.y = rand() % 900;
      par[i].spd.x = (rand() % 2000) / 1000.0 - 1.0;
      par[i].spd.y = (rand() % 2000) / 1000.0 - 1.0;
      par[0].weight = 1e9;
    }

  bunny_set_key_response(key);
  bunny_set_loop_main_function(loop);
  bunny_set_display_function(display);
  bunny_loop(win, 150, NULL);
  bunny_stop(win);
  return (0);
}
