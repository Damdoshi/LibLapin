/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Bibliotheque Lapin
*/

#include		<lapin.h>
#include		<assert.h>
#include		<string.h>

int			main(void)
{
  t_bunny_dressed_sprite*dressed_sprite;
  t_bunny_sprite	*sprite;
  t_bunny_window	*win;
  t_bunny_map		*wardrobe;
  int			i;

  bunny_set_error_descriptor(2);
  // bunny_set_log_filter("syntax");

  assert(wardrobe = bunny_new_wardrobe());
  assert(dressed_sprite = bunny_load_dressed_sprite("./sprite.dab", wardrobe));

  assert(dressed_sprite->sprite.clipable.clip_width == 120);
  assert(dressed_sprite->sprite.clipable.clip_height == 120);

  assert(win = bunny_start
	 (dressed_sprite->sprite.clipable.clip_width,
	  dressed_sprite->sprite.clipable.clip_height,
	  false, "DressedSprite"
	  ));

  for (i = 0; i < 10; ++i)
    {
      bunny_blit(&win->buffer, &dressed_sprite->sprite.clipable, NULL);
      bunny_display(win);
      bunny_usleep(1e5);
      bunny_sprite_animate(&dressed_sprite->sprite, 1);
    }

  assert(sprite = bunny_render_dressed_sprite(dressed_sprite));
  assert(sprite->clipable.clip_width == 120);
  assert(sprite->clipable.clip_height == 120);

  // Draw the generated sprite on screen
  for (i = 0; i < 10; ++i)
    {
      bunny_blit(&win->buffer, &sprite->clipable, NULL);
      bunny_display(win);
      bunny_usleep(1e5);
      bunny_sprite_animate(sprite, 1);
    }

  bunny_delete_clipable(&sprite->clipable);
  assert(bunny_dressed_sprite_wear(dressed_sprite, "TheArmor", "White"));
  assert(sprite = bunny_render_dressed_sprite(dressed_sprite));

  // Draw the generated sprite on screen
  for (i = 0; i < 10; ++i)
    {
      bunny_blit(&win->buffer, &sprite->clipable, NULL);
      bunny_display(win);
      bunny_usleep(1e5);
      bunny_sprite_animate(sprite, 1);
    }

  bunny_delete_clipable(&dressed_sprite->sprite.clipable);
  bunny_delete_clipable(&sprite->clipable);
  bunny_stop(win);
  return (EXIT_SUCCESS);
}
