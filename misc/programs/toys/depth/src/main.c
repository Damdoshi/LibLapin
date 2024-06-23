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
t_bunny_tilemap		*tdup;
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
  if (bunny_get_keyboard()[BKS_F5])
    spr->clipable.position.y -= 3;
  if (bunny_get_keyboard()[BKS_F6])
    spr->clipable.position.y += 3;

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
    if ((tmap->zoom.x = (tmap->zoom.y *= 0.95)) < 0.1)
      tmap->zoom.x = tmap->zoom.y = 0.1;

  if (bunny_get_keyboard()[BKS_SPACE])
    {
      tdup->zoom = tmap->zoom;
      tdup->rotation = tmap->rotation;
    }

  bunny_sprite_animate(spr, 1.0 / bunny_get_frequency());

  return (GO_ON);
}

static void		render_tilemap(t_bunny_tilemap	*tm)
{
  bunny_fill(&tm->clipable.buffer, RED);

  tm->layer_clip[0] = 0;
  tm->layer_clip[1] = 1;
  bunny_draw(&tm->clipable);

  bunny_blit(&tm->clipable.buffer, &spr->clipable, NULL);

  tm->layer_clip[0] = 1;
  tm->layer_clip[1] = 1;
  bunny_draw(&tm->clipable);
}

t_bunny_response	display(void			*unused)
{
  static int		x;

  (void)unused;
  if ((x += 1) / 100 % 2)
    bunny_fill(&win->buffer, PINK2);
  else
    bunny_fill(&win->buffer, PINK);

  render_tilemap(tmap);
  render_tilemap(tdup);

  tdup->clipable.rotation = tmap->clipable.rotation;
  tdup->clipable.scale = tmap->clipable.scale;

  bunny_blit(&win->buffer, &tmap->clipable, NULL);
  //bunny_blit(&win->buffer, &tdup->clipable, NULL);

  bunny_display(win);
  return (GO_ON);
}

int			main(int	argc,
			     char	**argv)
{
  const char		*file = "./tilemap.dab";
  int			cnt;

  // bunny_consistancy();
  bunny_set_log_mode(true);
  bunny_enable_full_blit(true);
  bunny_set_log_filter("tilemap");
  bunny_set_error_descriptor(2);

  assert((win = bunny_start_style(800, 800, DEFAULT_WIN_STYLE | ANTIALIASING, "TileMap!")));
  //bunny_set_error_descriptor(2);
  if (argc >= 2)
    file = argv[1];

  if (!(tmap = bunny_load_tilemap_wh(file, 300, 300)))
    {
      bunny_perror("bunny_load_tilemap");
      return (EXIT_FAILURE);
    }

  // CHECK CUSTOM PROPERTIES

  //
  if (tmap->properties)
    {
      puts("Tilemap properties:----------");
      bunny_print_string_map(tmap->properties, 1, cnt);
      puts("-----------------------------");
    }
  //
  for (int i = 0; i < tmap->nbr_layers; ++i)
    if (tmap->layers[i].properties)
      {
	printf("Tilelayer %s properties:-----------\n", tmap->layers[i].name);
	bunny_print_string_map(tmap->layers[i].properties, 1, cnt);
	puts("-----------------------------");
      }
  for (int i = 0; i < tmap->nbr_tilesets; ++i)
    {
      //
      if (tmap->tilesets[i].properties)
	{
	  printf("Tileset %s properties:----------\n", tmap->tilesets[i].name);
	  bunny_print_string_map(tmap->tilesets[i].properties, 1, cnt);
	  puts("-----------------------------");
	}
      //
      for (int j = 0; j < tmap->tilesets[i].nbr_tiles; ++j)
	if (tmap->tilesets[i].tile_properties_id[j].properties)
	  {
	    printf("Tileset %s, tile %d property----------\n", tmap->tilesets[i].name, j);
	    bunny_print_string_map(tmap->tilesets[i].tile_properties_id[j].properties, 1, cnt);
	    puts("-----------------------------");
	  }
    }

  if (argc >= 2)
    {
      tmap->clipable.scale.x = 2;
      tmap->clipable.scale.y = 2;
      tmap->clipable.origin.x = tmap->clipable.buffer.width / 2;
      tmap->clipable.origin.y = tmap->clipable.buffer.height / 2;
      tmap->clipable.position.x = win->buffer.width / 2;
      tmap->clipable.position.y = win->buffer.height / 2;

      bunny_tilemap_set_camera(tmap, bunny_accurate_position(tmap->map_size.x / 2, tmap->map_size.y / 2));
    }

  if (!(tdup = bunny_tilemap_new_viewpoint(tmap, 100, 100)))
    {
      bunny_perror("bunny_tilemap_new_viewpoint");
      bunny_delete_clipable(&tmap->clipable);
      return (EXIT_FAILURE);
    }

  tdup->clipable.origin.x = tdup->clipable.buffer.width / 2;
  tdup->clipable.origin.y = tdup->clipable.buffer.height / 2;
  tdup->clipable.position.x = 2 * win->buffer.width / 3;
  tdup->clipable.position.y = 2 * win->buffer.height / 3;

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

