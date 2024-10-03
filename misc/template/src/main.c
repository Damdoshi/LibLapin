// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Game

#include		<stdlib.h>
#include		"program.h"

int			main(int		argc,
			     char		**argv)
{
  static t_program	program;
  t_bunny_response	ret;

  (void)argc;
  memset(&program, 0, sizeof(program));
  bunny_join_binary_directory(*argv);
  if (!(program.configuration = bunny_open_configuration("./res/configuration.dab", NULL)))
    {
      fprintf(stderr, "Cannot open configuration.\n");
      return (EXIT_FAILURE);
    }
  t_bunny_position	siz;

  if (bunny_position_configuration("Screen", &siz, program.configuration) != BD_OK)
    {
      fprintf(stderr, "Invalid Screen size.\n");
      return (EXIT_FAILURE);
    }
  if (!(program.screen = bunny_new_picture(siz.x, siz.y)))
    {
      fprintf(stderr, "Cannot create the screen picture.");
      return (EXIT_FAILURE);
    }
  if (siz.x >= 1920 && siz.y >= 1080)
    program.hdscreen = program.screen;
  else if (!(program.hdscreen = bunny_new_picture(1920, 1080)))
    {
      fprintf(stderr, "Cannot create the hdscreen picture.");
      return (EXIT_FAILURE);
    }

  if (!(program.window = bunny_begin("./res/window.dab")))
    {
      fprintf(stderr, "Cannot open window.\n");
      return (EXIT_FAILURE);
    }
  program.context = FIRST_CONTEXT;
  void			*data[LAST_CONTEXT];

#include		"context_pointers.template"

  // Construction de Bunny Splash
  memcpy(&gl_context[BUNNY_SPLASH], &gl_bunny_splash_context, sizeof(t_bunny_context));
  program.bunny_splash.bunny_picture_file = "./res/bunny_splash/bunny.dab";
  program.bunny_splash.rope_picture_file = "./res/bunny_splash/rope.dab";
  program.bunny_splash.title_picture_file = "./res/bunny_splash/title.dab";
  program.bunny_splash.jingle_sound_file = "./res/bunny_splash/jingle.dab";
  program.bunny_splash.boom_sound_file = "./res/bunny_splash/boom.dab";
  program.bunny_splash.outch_sound_file = "./res/bunny_splash/outch.dab";
  program.bunny_splash.falling_sound_file = "./res/bunny_splash/falling.dab";
  t_bunny_response	subcontext_display(void *bss)
  {
    t_bunny_clipable	clipable;

    (void)bss;
    bunny_clipable_copy(&clipable, program.hdscreen);
    bunny_scale_clipable(&program.window->buffer, program.hdscreen, BST_STRETCH, false);
    bunny_blit(&program.window->buffer, program.hdscreen, NULL);
    bunny_display(program.window);
    bunny_clipable_copy(program.hdscreen, &clipable);
    return (LEAVE_EVENT);
  }
  void			subcontext_leaving(t_bunny_response ret,
					   void *_bss)
  {
    (void)ret;
    (void)_bss;
    program.context = BUNNY_SPLASH + 1;
  }
  program.bunny_splash.head.subcontext.display = subcontext_display;
  program.bunny_splash.head.subcontext.leaving_context = subcontext_leaving;
  program.bunny_splash.head.screen = &program.hdscreen->buffer;
  data[BUNNY_SPLASH] = &program.bunny_splash;
  
  do
    {
      bunny_set_context(&gl_context[program.context]);
      ret = bunny_loop(program.window, 50, data[program.context]);
    }
  while (ret == SWITCH_CONTEXT && program.context < LAST_CONTEXT);

  if (program.hdscreen != program.screen)
    bunny_delete_clipable(program.screen);
  bunny_delete_clipable(program.screen);
  bunny_stop(program.window);
  return (EXIT_SUCCESS);
}
