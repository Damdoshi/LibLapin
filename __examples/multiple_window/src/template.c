/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2015
**
** The Lapin Noir Demo for LibLapin1.7
*/

#include		<stdio.h>
#include		<lapin.h>
#include		<alloca.h>

t_bunny_window		**win;
int			r;

t_bunny_response	click(t_bunny_event_state		state,
			      t_bunny_mouse_button		but,
			      void				*dat)
{
  int			i;

  (void)state;
  (void)but;
  (void)dat;
  for (i = 0; i < r; ++i)
    {
      if (bunny_get_window() == win[i])
	bunny_clear(&win[i]->buffer, RED);
      else
	bunny_clear(&win[i]->buffer, BLACK);
      bunny_display(win[i]);
    }
  return (GO_ON);
}

t_bunny_response	key(t_bunny_event_state			state,
			    t_bunny_keysym			sym,
			    void				*dat)
{
  (void)state;
  (void)dat;
  if (sym == BKS_ESCAPE)
    return (EXIT_ON_SUCCESS);
  return (GO_ON);
}

t_bunny_response	closew(const t_bunny_window		*win,
			       void				*data)
{
  (void)win;
  (void)data;
  return (EXIT_ON_CROSS);
}

int			main(void)
{
  int			i;

  puts("Clique sur une fenetre pour la rendre rouge. Ferme en une, cela les fermera toutes");
  
  r = rand() % 3 + 2;
  win = alloca(r * sizeof(*win));
  for (i = 0; i < r; ++i)
    {
      win[i] = bunny_start(320, 240, false, "Window");
      bunny_clear(&win[i]->buffer, BLACK);
      bunny_display(win[i]);
    }

  bunny_set_close_response(closew);
  bunny_set_click_response(click);
  bunny_loop_mw(win, r, 25, NULL);

  for (i = 0; i < r; ++i)
    bunny_stop(win[i]);
  return (0);
}

