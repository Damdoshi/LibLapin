/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
**
*/

#include		<time.h>
#include		<stdio.h>
#include		<assert.h>
#include		<lapin.h>

t_bunny_window		*win;
t_bunny_pixelarray	*pix;
t_bunny_cipher_key	*cipher_key;

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
  if (sym < BKS_F1 || sym > BKS_F8)
    return (GO_ON);

  if (sym < BKS_F5)
    bunny_cipher_data
      (pix->pixels,
       pix->clipable.buffer.width * pix->clipable.buffer.height * 4,
       sym - BKS_F1,
       cipher_key
       );

  if (sym >= BKS_F5)
    bunny_uncipher_data
      (pix->pixels,
       pix->clipable.buffer.width * pix->clipable.buffer.height * 4,
       sym - BKS_F5,
       cipher_key
       );

  return (GO_ON);
}

t_bunny_response	loop(void				*dat)
{
  (void)dat;
  bunny_clear(&win->buffer, BLACK);
  bunny_blit(&win->buffer, &pix->clipable, NULL);
  bunny_display(win);
  return (GO_ON);
}

int			main(int	argc,
			     char	**argv)
{
  int			i;

  srand(time(NULL));
  assert(argc == 2);

  cipher_key = bunny_alloca(sizeof(*cipher_key) + 32);
  cipher_key->length = 32;
  for (i = 0; i < cipher_key->length; ++i)
    cipher_key->key[i] = rand() % 256;

  assert(pix = bunny_load_pixelarray(argv[1]));
  assert(win = bunny_start
	 (pix->clipable.clip_width, pix->clipable.clip_height, false, "Entropy test")
	 );

  printf("F1/F4: XOR\nF2/F5: CAESAR\nF3/F6: SHAKER\nF4/F8: SWITCH\n");

  bunny_set_key_response(key);
  bunny_set_loop_main_function(loop);
  bunny_loop(win, 20, NULL);

  bunny_delete_clipable(pix);
  bunny_stop(win);
  return (EXIT_SUCCESS);
}
