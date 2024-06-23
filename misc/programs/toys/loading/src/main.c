/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2018
**
** LibLapin Test
*/

#define				_GNU_SOURCE
#include			<stdio.h>
#include			<assert.h>
#include			<lapin.h>

t_bunny_picture			*gl_pictures[10];
t_bunny_ressource_to_load	gl_pictures_to_load[10];

t_bunny_effect			*gl_effects[10];
t_bunny_ressource_to_load	gl_effects_to_load[10];

t_bunny_response		async(void			*computed,
				      void			*data)
{
  t_bunny_loading_screen	*ld = (t_bunny_loading_screen*)data;
  t_bunny_ressource_to_load	*res = (t_bunny_ressource_to_load*)computed;

  (void)ld;
  printf("Loaded: %s -> %p.\n", res->file, res->target);
  return (GO_ON);
}

t_bunny_response		display(void			*data)
{
  t_bunny_loading_screen	*ld = (t_bunny_loading_screen*)data;
  t_bunny_position		pos[2];
  unsigned int			col[2] = {WHITE, PINK2};
  int				limit;
  int				i;

  bunny_clear(ld->head.screen, BLACK);
  limit = ld->percent_completion * ld->head.screen->width;
  for (i = 0; i < limit; ++i)
    {
      pos[0].x = pos[1].x = i;
      pos[0].y = 0;
      pos[1].y = ld->head.screen->height;
      bunny_set_line(ld->head.screen, &pos[0], &col[0]);
    }
  bunny_display((t_bunny_window*)ld->head.screen);
  return (GO_ON);
}

int				main(void)
{
  t_bunny_loading_screen	loading_screen;
  t_bunny_window		*win;
  int				i;

  memset(&loading_screen, 0, sizeof(loading_screen));

  for (i = 0; i < 10; ++i)
    {
      char			*s;

      asprintf(&s, "./picture%d.png", i);
      gl_pictures_to_load[i].file = s;
      gl_pictures_to_load[i].target = (void**)&gl_pictures[i];

      asprintf(&s, "./snd%d.wav", i);
      gl_effects_to_load[i].file = s;
      gl_effects_to_load[i].target = (void**)&gl_effects[i];
    }

  loading_screen.head.main_structure = &loading_screen;
  loading_screen.head.subcontext.display = &display;
  loading_screen.head.subcontext.async_computation_response = &async;
  assert(loading_screen.head.screen =
	 (t_bunny_buffer*)(win = bunny_start(400, 300, false, "Loading screen")));

  assert(bunny_init_loading_context(&loading_screen));
  assert(bunny_add_to_ressource_list
	 (loading_screen.pictures, &gl_pictures_to_load[0], NBRCELL(gl_pictures))
	 );
  assert(bunny_add_to_ressource_list
	 (loading_screen.effects, &gl_effects_to_load[0], NBRCELL(gl_effects))
	 );

  bunny_clear(loading_screen.head.screen, BLACK);
  bunny_display((t_bunny_window*)loading_screen.head.screen);

  bunny_set_context(&gl_bunny_loading_context);
  bunny_loop(win, 25, &loading_screen);

  bunny_clear_all_loaded_ressources(&loading_screen);

  bunny_stop((t_bunny_window*)loading_screen.head.screen);

  for (i = 0; i < 10; ++i)
    {
      free((char*)gl_pictures_to_load[i].file);
      free((char*)gl_effects_to_load[i].file);
    }
  return (EXIT_SUCCESS);
}

