// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2026
//
// Cinematic context player

#include			<lapin.h>
#include			<ctype.h>
#include			<errno.h>
#include			<stdio.h>
#include			<stdlib.h>
#include			<string.h>

typedef struct			s_cineplayer
{
  t_bunny_cinematic_screen	cinematic;
  t_bunny_window		*window;
  t_bunny_picture		*native_screen;
  t_bunny_buffer		*screens[2];
  char				language[128];
  double			base_scale_x;
  double			base_scale_y;
  double			window_scale;
}				t_cineplayer;

static void			usage(const char			*prog)
{
  fprintf
    (stderr,
     "Usage: %s cinematic.dab [window_scale] [language]\n"
     "\n"
     "  cinematic.dab  Dabsic cinematic file to play.\n"
     "  window_scale   Optional multiplier for the window size. Default: 1.\n"
     "  language       Optional cinematic text language. Default: FR.\n"
     "\n"
     "Controls:\n"
     "  SPACE / ENTER / click: validate current cinematic step.\n"
     "  ESCAPE: leave the player.\n",
     prog);
}

static bool			parse_scale(const char			*text,
					    double			*out)
{
  char *end;
  double value;

  errno = 0;
  value = strtod(text, &end);
  if (errno != 0 || end == text || *end != '\0' || value <= 0)
    return (false);
  *out = value;
  return (true);
}

static void			normalize_language(const char		*input,
						   char			*output,
						   size_t		outsize)
{
  size_t			i;

  if (outsize == 0)
    return ;
  if (input == NULL)
    input = "FR";
  for (i = 0; input[i] && i + 1 < outsize; ++i)
    output[i] = toupper((unsigned char)input[i]);
  output[i] = '\0';
}

static double			valid_clipable_scale(double		scale)
{
  if (scale <= 0)
    return (1.0);
  return (scale);
}

static bool			compute_window_size(const t_bunny_clipable *clipable,
						    double		scale_x,
						    double		scale_y,
						    int			*width,
						    int			*height)
{
  if (clipable == NULL || width == NULL || height == NULL)
    return (false);
  *width = (int)(clipable->buffer.width * scale_x + 0.5);
  *height = (int)(clipable->buffer.height * scale_y + 0.5);
  return (*width > 0 && *height > 0);
}

static t_bunny_response		cineplayer_entering(void		*data)
{
  t_bunny_cinematic_screen	*cinematic;
  t_cineplayer			*player;

  cinematic = (t_bunny_cinematic_screen*)data;
  player = (t_cineplayer*)cinematic->head.main_structure;
  if (player == NULL || cinematic->cinematic == NULL)
    return (EXIT_ON_ERROR);
  cinematic->cinematic->clipable.scale.x = player->base_scale_x * player->window_scale;
  cinematic->cinematic->clipable.scale.y = player->base_scale_y * player->window_scale;
  return (GO_ON);
}

static bool			build_player(t_cineplayer		*player,
					     const char			*file,
					     double			window_scale,
					     const char			*language)
{
  t_bunny_cinematic		*cinematic;
  int				window_width;
  int				window_height;
  char				title[512];

  memset(player, 0, sizeof(*player));
  normalize_language(language, &player->language[0], sizeof(player->language));
  cinematic = bunny_load_cinematic(file, &player->language[0]);
  if (cinematic == NULL)
    {
      fprintf(stderr, "Cannot load cinematic: %s\n", file);
      return (false);
    }
  player->base_scale_x = valid_clipable_scale(cinematic->clipable.scale.x);
  player->base_scale_y = valid_clipable_scale(cinematic->clipable.scale.y);
  player->window_scale = window_scale;
  if (!compute_window_size(&cinematic->clipable,
                           player->base_scale_x * window_scale,
                           player->base_scale_y * window_scale,
                           &window_width,
                           &window_height))
    {
      fprintf(stderr, "Invalid cinematic dimensions in: %s\n", file);
      bunny_delete_clipable(&cinematic->clipable);
      return (false);
    }
  cinematic->clipable.scale.x = player->base_scale_x * window_scale;
  cinematic->clipable.scale.y = player->base_scale_y * window_scale;

  snprintf(title, sizeof(title), "cineplayer - %s - %ux%u x %.3g",
	   file, (unsigned int)cinematic->clipable.buffer.width,
	   (unsigned int)cinematic->clipable.buffer.height,
	   window_scale);
  player->window = bunny_start(window_width, window_height, false, title);
  if (player->window == NULL)
    {
      fprintf(stderr, "Cannot create window %dx%d.\n", window_width, window_height);
      bunny_delete_clipable(&cinematic->clipable);
      return (false);
    }
  player->screens[0] = &player->window->buffer;
  player->screens[1] = NULL;

  player->cinematic.head.main_structure = player;
  player->cinematic.head.screens = &player->screens[0];
  player->cinematic.head.nbr_screen = 1;
  player->cinematic.head.subcontext.entering_context = cineplayer_entering;

  player->cinematic.cinematic_file = file;
  player->cinematic.language = &player->language[0];
  player->cinematic.clear_screen = true;
  player->cinematic.centered = false;
  player->cinematic.validation_event = BCE_TERMINATE_EVENT;
  player->cinematic.cinematic = cinematic;
  player->cinematic.delete_cinematic_on_leave = true;
  return (true);
}

static void			destroy_player(t_cineplayer		*player)
{
  if (player->window)
    bunny_stop(player->window);
}

int				main(int				argc,
				     char				**argv)
{
  t_cineplayer			player;
  t_bunny_response		ret;
  const char			*language;
  double			window_scale;

  if (argc < 2 || argc > 4)
    {
      usage(argv[0]);
      return (EXIT_FAILURE);
    }
  window_scale = 1.0;
  if (argc >= 3 && !parse_scale(argv[2], &window_scale))
    {
      fprintf(stderr, "Invalid window scale: %s\n", argv[2]);
      return (EXIT_FAILURE);
    }
  language = argc >= 4 ? argv[3] : "FR";
  if (!build_player(&player, argv[1], window_scale, language))
    return (EXIT_FAILURE);
  bunny_enable_full_blit(true);
  bunny_sound_sprite_trap_or_sync(true);
  bunny_set_context(&gl_bunny_cinematic_context);
  ret = bunny_loop(player.window, 50, &player.cinematic);
  destroy_player(&player);
  if (ret == EXIT_ON_ERROR)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

