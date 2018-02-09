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
t_bunny_screen_tweak	tweak =
  {
    .blur_level = 1.0,
    .luminosity = 1.0,
    .color = { 1, 1, 1 },
    .color_blind = BCBT_RED_GREEN_BLUE,
    .invert_color = false,
    .gray_scale = 0,
    .noise_color = BNC_COLOR_NOISE,
    .noise_type = BNT_NO_NOISE,
    .noise_strenght = 0.5
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

  if (sym == BKS_O)
    tweak.blur_level -= 1;
  if (sym == BKS_P)
    tweak.blur_level += 1;

  if (sym == BKS_F1)
    tweak.luminosity -= 0.1;
  if (sym == BKS_F2)
    tweak.luminosity += 0.1;

  if (sym == BKS_F3)
    tweak.color[RED_CMP] -= 0.25;
  if (sym == BKS_F4)
    tweak.color[RED_CMP] += 0.25;

  if (sym == BKS_F5)
    tweak.color[GREEN_CMP] -= 0.25;
  if (sym == BKS_F6)
    tweak.color[GREEN_CMP] += 0.25;

  if (sym == BKS_F7)
    tweak.color[BLUE_CMP] -= 0.25;
  if (sym == BKS_F8)
    tweak.color[BLUE_CMP] += 0.25;

  if (sym == BKS_I)
    tweak.invert_color = !tweak.invert_color;

  if (sym == BKS_G)
    {
      if ((tweak.gray_scale -= 1) < 0)
	tweak.gray_scale = 0;
      printf("Gray scale level: %d.\n", tweak.gray_scale);
    }
  if (sym == BKS_B)
    {
      if ((tweak.gray_scale += 1) > 255)
	tweak.gray_scale = 255;
      printf("Gray scale level: %d.\n", tweak.gray_scale);
    }

  if (sym == BKS_F)
    {
      tweak.color_blind = (tweak.color_blind + 1) % (BCBT_BLUE_RED_GREEN + 1);
      printf("Color blind mode: %d\n", tweak.color_blind);
    }

  if (sym == BKS_C)
    {
      tweak.noise_color = (tweak.noise_color + 1) % (BNC_BLACK_AND_WHITE_NOISE + 1);
      printf("Noise color: %d\n", tweak.noise_color);
    }

  if (sym == BKS_T)
    {
      tweak.noise_type = (tweak.noise_type + 1) % (BNT_ROW_NOISE + 1);
      printf("Noise type: %d\n", tweak.noise_type);
    }

  if (sym == BKS_A)
    {
      tweak.noise_strenght -= 0.2;
      printf("Noise strenght: %f\n", tweak.noise_strenght);
    }
  if (sym == BKS_Z)
    {
      tweak.noise_strenght += 0.2;
      printf("Noise strenght: %f\n", tweak.noise_strenght);
    }

  return (GO_ON);
}

t_bunny_response	loop(void				*dat)
{
  (void)dat;
  bunny_clear(&win->buffer, BLACK);
  bunny_blit_shader(&win->buffer, picture, NULL, bunny_screen_tweak_shader(&tweak));
  bunny_display(win);
  return (GO_ON);
}

int			main(int				argc,
			     char				**argv)
{
  if (argc == 1)
    assert(picture = bunny_load_picture("waterfall.png"));
  else
    assert(picture = bunny_load_picture(argv[1]));
  assert(win = bunny_start(picture->clip_width, picture->clip_height, false, "ScreenTweak"));

  printf("o/p : Blur.\n");
  printf("F1/F2 : Luminosity.\n");
  printf("F3/F4 : Red.\n");
  printf("F5/F6 : Green.\n");
  printf("F7/F8 : Blue.\n");
  printf("i : Invert color.\n");
  printf("f : Color switch for color blind.\n");
  printf("g / b : Gray scale level (0: color, 255: full grayscale).\n");
  printf("c : Switch noise color.\n");
  printf("t : Switch noise type.\n");
  printf("a/z : Noise strenght.\n");

  bunny_set_key_response(key);
  bunny_set_loop_main_function(loop);
  bunny_loop(win, 20, NULL);

  bunny_delete_clipable(picture);
  bunny_stop(win);
  return (EXIT_SUCCESS);
}
