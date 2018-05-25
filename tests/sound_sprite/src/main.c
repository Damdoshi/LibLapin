/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** LibLapin Test
*/

#include		<assert.h>
#include		<lapin.h>

t_bunny_window		*win;

t_bunny_response	key(t_bunny_event_state	state,
			    t_bunny_keysym	sym,
			    void		*d)
{
  t_bunny_sound_sprite	*sprite = d;

  if (sym == BKS_ESCAPE)
    return (EXIT_ON_SUCCESS);
  if (bunny_sound_is_playing(&sprite->soundset.sound))
    return (GO_ON);
  if (state == GO_DOWN)
    {
      if (sym == BKS_F1)
	assert(bunny_sound_sprite_play_slice(sprite, BST_TRACK_01, "f1"));
      else if (sym == BKS_F2)
	assert(bunny_sound_sprite_play_slice(sprite, BST_TRACK_01, "f2"));
      else if (sym == BKS_F3)
	assert(bunny_sound_sprite_play_slice(sprite, BST_TRACK_01, "f3"));
      else if (sym == BKS_F4)
	assert(bunny_sound_sprite_play_slice(sprite, BST_TRACK_01, "f4"));

      else if (sym == BKS_F5)
	assert(bunny_sound_sprite_play_slice(sprite, BST_TRACK_01, "f5"));
      else if (sym == BKS_F6)
	assert(bunny_sound_sprite_play_slice(sprite, BST_TRACK_01, "f6"));
      else if (sym == BKS_F7)
	assert(bunny_sound_sprite_play_slice(sprite, BST_TRACK_01, "f7"));
      else if (sym == BKS_F8)
	assert(bunny_sound_sprite_play_slice(sprite, BST_TRACK_01, "f8"));

      else if (sym == BKS_ESCAPE)
	bunny_sound_sprite_stop_slice(sprite);
    }
  return (GO_ON);
}

t_bunny_response	display(void		*d)
{
  t_bunny_sound_sprite	*sprite = d;

  if (bunny_sound_sprite_is_talking(sprite))
    {
      bunny_fill(&win->buffer, rand() | BLACK);
      bunny_display(win);
    }
  return (GO_ON);
}

int			main(int		argc,
			     char		**argv)
{
  t_bunny_sound_sprite	*sprite;

  bunny_set_error_descriptor(2);
  assert(win = bunny_start(320, 240, false, "Sound sprite test"));
  bunny_clear(&win->buffer, PINK2);
  bunny_display(win);
  if (argc == 2)
    assert(sprite = bunny_load_sound_sprite(argv[1]));
  else
    assert(sprite = bunny_load_sound_sprite("./sound_sprite.dab"));
  bunny_set_key_response(key);
  bunny_set_display_function(display);
  bunny_loop(win, 50, sprite);
  bunny_stop(win);
  return (EXIT_SUCCESS);
}

