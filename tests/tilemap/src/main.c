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
t_bunny_picture		*shadows;
t_bunny_sprite		*spr;

t_bunny_normal_light	lights =
  {
    .active = true,
    .x = 0,
    .y = 0,
    .light_color = {.full = WHITE},
    .light_attenuation = 1.0
  };

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
  bunny_clear(&shadows->buffer, BLACK);
  bunny_tilemap_raytrace
    (tmap, 3, &lights, 1, shadows, tmap->clipable.buffer.width);

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
  bunny_blit(&win->buffer, shadows, NULL);
  bunny_display(win);
  return (GO_ON);
}

int			main(void)
{

  bunny_consistancy();
  bunny_enable_full_blit(true);

  assert(win = bunny_start(800, 800, false, "TileMap!"));
  assert(shadows = bunny_new_picture(win->buffer.width, win->buffer.height));
  //bunny_set_error_descriptor(2);
  if (!(tmap = bunny_load_tilemap("./tilemap.dab")))
    {
      bunny_perror("bunny_load_tilemap");
      return (EXIT_FAILURE);
    }

  if (!(spr = bunny_load_sprite("./dinelo.ini")))
    {
      bunny_perror("bunny_load_sprite");
      return (EXIT_FAILURE);
    }

  bunny_set_loop_main_function(loop);
  bunny_set_key_response(key);
  bunny_set_display_function(display);

  bunny_loop(win, 25, NULL);

  bunny_delete_clipable(&tmap->clipable);
  bunny_stop(win);
  return (EXIT_SUCCESS);
}

