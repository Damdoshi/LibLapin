/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2018
**
** Sound Rope
*/

#include		<string.h>
#include		<stdio.h>
#include		"sound_rope.h"

bunny_declare_context(soundrope);

int			main(int	argc,
			     char	**argv)
{
  static t_sound_rope	rope;
  t_bunny_list		*ifiles;
  char			*ptr;
  int			i;

  // Handle parameters
  if (argc != 4 && argc != 2)
    {
      fprintf(stderr,
	      "\n%s: Invalid usage. Correct is:\n\n"
	      "\t%s [not_sound_sprite_source_file]+ outputfile.format\n\n"
	      "\t%s sound_sprite_source_file\n\n"
	      "\tValid formats are: ini, json, lua, xml, and dab\n"
	      "\tAn additionnal ogg file will be generated aside.\n\n",
	      argv[0], argv[0], argv[0]
	      );
      return (EXIT_FAILURE);
    }
  rope.output_configuration_file = argv[argc - 1];
  if ((rope.output_format = bunny_which_format(rope.output_configuration_file)) == BC_CUSTOM)
    {
      fprintf(stderr,
	      "%s: Invalid output format.\n"
	      "\tValid formats are: ini, json, lua, xml, dab\n",
	      argv[0]
	      );
      return (EXIT_FAILURE);
    }
  assert(rope.output_sound_file = bunny_strdup(rope.output_configuration_file));
  if ((ptr = strrchr(rope.output_sound_file, '.')) != NULL)
    strcpy(ptr, ".ogg");

  // Software configuration file
  t_bunny_configuration	*cnf;

  if ((cnf = bunny_open_configuration("soundrope.ini", NULL)) != NULL)
    {
      bunny_configuration_getf(cnf, &rope.silence_separator, "SeparatorDuration");
      bunny_configuration_getf(cnf, &rope.cli_mode, "CLIMode");
      bunny_delete_configuration(cnf);
    }

  // Load target data
  if (argc != 2)
    {
      assert(ifiles = bunny_new_list());
      for (i = 1; i < argc - 1; ++i)
	assert(bunny_list_push_back(ifiles, argv[i]));
      assert(rope.input_files = bunny_list_tie(ifiles, char*));
      bunny_delete_list(ifiles);

      if (sound_rope_mux_load(&rope) == false)
	return (EXIT_FAILURE);
      if (sound_rope_mux_generate(&rope) == false)
	return (EXIT_FAILURE);
    }
  else
    {
      if (sound_rope_load(&rope) == false)
	return (EXIT_FAILURE);
    }

  // Edit mode
  if (rope.cli_mode == false)
    {
      assert(rope.win = bunny_start(1024, 240, false, "SoundRope"));

      bunny_set_click_response(soundrope_click);
      bunny_set_move_response(soundrope_move);
      bunny_set_loop_main_function(soundrope_loop);
      bunny_set_display_function(soundrope_display);

      bunny_loop(rope.win, 25, &rope);
      bunny_stop(rope.win);
    }
  else if (sound_rope_save(&rope) == false)
    return (EXIT_FAILURE);

  return (EXIT_SUCCESS);
}

