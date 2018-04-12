/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
**
*/

#include		<stdio.h>
#include		<assert.h>
#include		<lapin.h>

t_bunny_window		*win;
t_bunny_picture		*picture;
t_bunny_spreading	spread =
  {
    .color = {{.full = ALPHA(8, PINK2)}, {.full = WHITE}},
    .speed = 2,
    .layout = NULL,
    .source_len = 3,
    .sources = {
      {1440 / 2, 900 / 2},
      {1439, 900 / 2},
      {0, 900 / 2}
    },
    .random = true
  };

t_bunny_response	key(t_bunny_event_state			state,
			    t_bunny_keysym			sym,
			    void				*data)
{
  (void)state;
  (void)data;
  if (state == GO_UP)
    return (GO_ON);
  if (sym == BKS_ESCAPE)
    return (EXIT_ON_SUCCESS);

  if (sym == BKS_F1)
    bunny_clear_spreading(&spread);
  if (sym == BKS_F2)
    spread.random = !spread.random;

  if (sym == BKS_F3)
    {
      spread.color[0].argb[ALPHA_CMP] -= 10;
      spread.color[1].argb[ALPHA_CMP] -= 10;
    }
  if (sym == BKS_F4)
    {
      spread.color[0].argb[ALPHA_CMP] += 10;
      spread.color[1].argb[ALPHA_CMP] += 10;
    }

  if (sym == BKS_F5)
    spread.speed -= 1;
  if (sym == BKS_F6)
    spread.speed += 1;
  if (sym == BKS_F7)
    bunny_flip_spreading(&spread);

  return (GO_ON);
}

t_bunny_response	loop(void				*dat)
{
  (void)dat;
  bunny_clear(&win->buffer, BLACK);
  spread.layout->color_mask.argb[ALPHA_CMP] = 32;
  bunny_blit(&win->buffer, spread.layout, NULL);
  spread.layout->color_mask.argb[ALPHA_CMP] = 255;
  bunny_blit_spreading(&win->buffer, NULL, &spread);
  bunny_display(win);
  return (GO_ON);
}

int			main(int				argc,
			     char				**argv)
{
  if (argc == 1)
    assert(spread.layout = bunny_load_picture("layout.png"));
  else
    assert(spread.layout = bunny_load_picture(argv[1]));

  assert(win = bunny_start(1440, 900, false, "ScreenSpreading"));

  printf("F1: Clear.\n");
  printf("F2 : Random.\n");
  printf("F3 : More transparent.\n");
  printf("F4 : More transparent.\n");
  printf("F5 : Slower.\n");
  printf("F6 : Faster.\n");
  printf("F7 : Flip color.\n");

  bunny_set_key_response(key);
  bunny_set_loop_main_function(loop);
  bunny_loop(win, 20, NULL);

  bunny_delete_clipable(spread.layout);
  bunny_delete_spreading(&spread);
  bunny_stop(win);
  return (EXIT_SUCCESS);
}

