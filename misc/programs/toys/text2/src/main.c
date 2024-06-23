/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** Bibliotheque Lapin
*/

#include			<time.h>
#include			<assert.h>
#include			<lapin.h>

t_bunny_response		key(t_bunny_event_state		state,
				    t_bunny_keysym		sym,
				    void			*data)
{
  (void)sym;
  (void)data;
  if (state == GO_DOWN)
    return (EXIT_ON_SUCCESS);
  return (GO_ON);
}

int				main(int	argc,
				     char	**argv)
{
  assert(argc == 2);
  t_bunny_window		*win = bunny_start(800, 600, false, "Text with LibLapin");
  t_bunny_position		size = {10, 14};
  //t_bunny_font			*fnt = bunny_load_font(155, win->buffer.height, argv[1], &size);
  t_bunny_picture		*pic = bunny_new_picture(win->buffer.width, win->buffer.height);
  t_bunny_font			*fnt = bunny_load_font(win->buffer.width, win->buffer.height, argv[1], &size);

  assert(fnt);
  srand(time(NULL));

  bunny_clear(&win->buffer, BLACK);
  bunny_clear(&fnt->clipable.buffer, PINK2);
  bunny_clear(&pic->buffer, GREEN);

  fnt->string = "Celui qui controle l'epice controle l'univers.";
  /*
  fnt->halign = BAL_JUSTIFY;
  fnt->valign = BAL_TOP;
  */
  fnt->halign = BAL_MIDDLE;
  fnt->valign = BAL_MIDDLE;

  size.x = 0;
  size.y = 0;
  bunny_draw(&fnt->clipable);
  bunny_blit(&pic->buffer, &fnt->clipable, &size);
  bunny_blit(&win->buffer, pic, NULL);

  bunny_display(win);
  bunny_set_key_response(key);
  bunny_loop(win, 25, NULL);

  bunny_delete_clipable(&fnt->clipable);
  bunny_stop(win);
  return (EXIT_SUCCESS);
}

