/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** LibLapin Test
*/

#include		<assert.h>
#include		<stdlib.h>
#include		<stdio.h>
#include		<lapin.h>

t_bunny_window		*win;
t_bunny_tilemap		*tmap;
t_bunny_sprite		*spr;

t_bunny_response	key(t_bunny_event_state		state,
			    t_bunny_keysym		sym,
			    void			*unused)
{
  (void)unused;
  if (state == GO_UP)
    return (GO_ON);

  if (sym == BKS_ESCAPE)
    return (EXIT_ON_SUCCESS);
  return (GO_ON);
}

t_bunny_response	loop(void			*unused)
{
  (void)unused;

  if (bunny_get_keyboard()[BKS_F3])
    spr->clipable.position.x -= 3;
  if (bunny_get_keyboard()[BKS_F4])
    spr->clipable.position.x += 3;

  if (bunny_get_keyboard()[BKS_Z] || bunny_get_keyboard()[BKS_W])
    tmap->camera.y -= 3.0;
  if (bunny_get_keyboard()[BKS_S])
    tmap->camera.y += 3.0;
  if (bunny_get_keyboard()[BKS_Q] || bunny_get_keyboard()[BKS_A])
    tmap->camera.x -= 3.0;
  if (bunny_get_keyboard()[BKS_D])
    tmap->camera.x += 3.0;

  if (bunny_get_keyboard()[BKS_F1])
    tmap->clipable.rotation -= 3.0;
  if (bunny_get_keyboard()[BKS_F2])
    tmap->clipable.rotation += 3.0;

  if (bunny_get_keyboard()[BKS_LEFT])
    tmap->rotation -= 3.0;
  if (bunny_get_keyboard()[BKS_RIGHT])
    tmap->rotation += 3.0;
  if (bunny_get_keyboard()[BKS_UP])
    tmap->zoom.x = (tmap->zoom.y *= 1.05);
  if (bunny_get_keyboard()[BKS_DOWN])
    tmap->zoom.x = (tmap->zoom.y *= 0.95);

  bunny_sprite_animate(spr, 1.0 / bunny_get_frequency());

  return (GO_ON);
}


t_bunny_response	display(void			*unused)
{
  static int		x;

  (void)unused;
  if ((x += 1) / 100 % 2)
    bunny_fill(&win->buffer, PINK2);
  else
    bunny_fill(&win->buffer, PINK);

  bunny_fill(&tmap->clipable.buffer, RED);

  tmap->layer_clip[0] = 0;
  tmap->layer_clip[1] = 1;
  bunny_draw(&tmap->clipable);

  bunny_blit(&tmap->clipable.buffer, &spr->clipable, NULL);

  tmap->layer_clip[0] = 1;
  tmap->layer_clip[1] = 1;
  bunny_draw(&tmap->clipable);

  //

  bunny_blit(&win->buffer, &tmap->clipable, NULL);
  bunny_display(win);
  return (GO_ON);
}

int			main(int	argc,
			     char	**argv)
{
  const char		*file = "./tilemap.dab";

  bunny_consistancy();
  bunny_enable_full_blit(true);

  assert(win = bunny_start_style(800, 800, DEFAULT_WIN_STYLE | ANTIALIASING, "TileMap!"));
  //bunny_set_error_descriptor(2);
  if (argc >= 2)
    file = argv[1];

  if (!(tmap = bunny_load_tilemap_wh(file, 300, 300)))
    {
      bunny_perror("bunny_load_tilemap");
      return (EXIT_FAILURE);
    }

  if (argc >= 2)
    {
      tmap->clipable.scale.x = 2;
      tmap->clipable.scale.y = 2;
      tmap->clipable.origin.x = 150;
      tmap->clipable.origin.y = 150;
      tmap->clipable.position.x = 400;
      tmap->clipable.position.y = 400;

      bunny_tilemap_set_camera(tmap, bunny_accurate_position(tmap->map_size.x / 2, tmap->map_size.y / 2));
    }

  if (!(spr = bunny_load_sprite("./dinelo.ini")))
    {
      bunny_perror("bunny_load_sprite");
      return (EXIT_FAILURE);
    }

  bunny_set_loop_main_function(loop);
  bunny_set_key_response(key);
  bunny_set_display_function(display);

  tmap->clipable.smooth = true;
  spr->clipable.smooth = true;

  bunny_loop(win, 200, NULL);

  bunny_delete_clipable(&tmap->clipable);
  bunny_stop(win);
  return (EXIT_SUCCESS);
}

