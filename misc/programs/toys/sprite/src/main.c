/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** LibLapin Test
*/

#include		<stdio.h>
#include		<time.h>
#include		<stdlib.h>
#include		<signal.h>
#include		<assert.h>
#include		<lapin.h>

#define			cassert(a, b)					\
  do {									\
    if (a != b) {							\
      printf("%ld (ref) is different from %ld\n", (int64_t)a, (int64_t)b); \
      assert(a == b);							\
    }									\
  } while (0)

static void		sighandler(int		sig)
{
  (void)sig;
  exit(EXIT_FAILURE);
}

int			main(int		argc,
			     char		**argv)
{
  t_bunny_sprite	*sprite;
  unsigned int		i;

  (void)argv;
  srand(time(NULL));
  signal(SIGALRM, sighandler);
  if (argc == 2)
    alarm(2);
  (void)argv;

  bunny_set_error_descriptor(2);
  assert(sprite = bunny_load_sprite("./res/double_forward.dab"));

  for (i = 0; i < 6; ++i)
    {
      cassert(bunny_sprite_get_animation(sprite), bunny_sprite_animation_name("FirstLine"));
      cassert(sprite->current_frame, i);
      cassert(sprite->clipable.clip_x_position, (int)i * 100);
      cassert(sprite->clipable.clip_y_position, 0);

      bunny_sprite_animate(sprite, 0.34);
    }
  for (i = 0; i < 3; ++i)
    {
      cassert(bunny_sprite_get_animation(sprite), bunny_sprite_animation_name("SecondLine"));
      cassert(sprite->current_frame, i);
      cassert(sprite->clipable.clip_x_position, 500 - (int)i * 100);
      cassert(sprite->clipable.clip_y_position, 100);
      bunny_sprite_animate(sprite, 0.34);
    }
  for (i = 0; i < 9; ++i)
    {
      cassert(bunny_sprite_get_animation(sprite), bunny_sprite_animation_name("SecondLine"));
      cassert(sprite->current_frame, 3 + i / 3);
      cassert(sprite->clipable.clip_x_position, 500 - (3 + (int)i / 3) * 100);
      cassert(sprite->clipable.clip_y_position, 100);
      bunny_sprite_animate(sprite, 0.34);
    }

  cassert(bunny_sprite_get_animation(sprite), bunny_sprite_animation_name("FirstLine"));
  cassert(sprite->current_frame, 0);
  cassert(sprite->clipable.clip_x_position, 0);
  cassert(sprite->clipable.clip_y_position, 0);

  bunny_delete_clipable(sprite);

  assert(sprite = bunny_load_sprite("./res/backforth.dab"));
  for (i = 0; i < 12; ++i)
    {
      cassert(sprite->current_frame, i);
      if (i >= 6)
	cassert(sprite->clipable.clip_x_position, (12 - (int)i - 1) * 100);
      else
	cassert(sprite->clipable.clip_x_position, (int)i * 100);
      cassert(sprite->clipable.clip_y_position, 0);

      cassert(bunny_sprite_get_animation(sprite), bunny_sprite_animation_name("FirstLine"));
      bunny_sprite_animate(sprite, 0.34);
    }

  printf("Success\n");
  return (EXIT_SUCCESS);
}

