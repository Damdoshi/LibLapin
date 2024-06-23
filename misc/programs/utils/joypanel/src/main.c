/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2019
**
** Joystick panel
*/

#include			"joypanel.h"

// Declare all context prototypes (=> callbacks/responses)
bunny_declare_context(joypanel);

// Forge a context thanks to declared prototypes
static t_bunny_anonymous_context context =
  {
    .key = joypanel_key,
    .loop = joypanel_loop,
    .display = joypanel_display,
    .button = joypanel_joy_button,
    .axis = joypanel_joy_axis,
    .connect = joypanel_joy_connect,
  };

int				main(void)
{
  static t_program		program;
  t_bunny_response		response;

  if (!(program.joystick = bunny_malloc(sizeof(*program.joystick) * LAST_BUNNY_JOYSTICK)))
    {
      bunny_printlerr("Cannot reserve space for joysticks.");
      return (EXIT_FAILURE);
    }

  // Initial joystick status.
  bunny_update_joysticks();
  for (program.nbr_joystick = 0;
       program.nbr_joystick < (int)LAST_BUNNY_JOYSTICK;
       ++program.nbr_joystick)
    if ((program.joystick[program.nbr_joystick] = bunny_get_joy_info(program.nbr_joystick))
	-> name == NULL)
      break ;

  // Open window
  if (joypanel_start(&program) == false)
    {
      bunny_free(program.joystick);
      bunny_printlerr("Cannot open the window.");
      return (EXIT_FAILURE);
    }

  // Load title font - no text will be displayed if it fails - errors are dropped.
  if ((program.title = bunny_load_text("./title.ini")))
    bunny_draw(&program.title->clipable);
  program.text = bunny_load_text("./text.ini");
  program.label = bunny_load_text("./label.ini");

  // Main program is going to be executed. Set callback context, loop and clear when done
  bunny_set_context((t_bunny_context*)&context);
  response = bunny_loop(program.window, 30, &program);
  bunny_stop(program.window);

  // Delete fonts
  bunny_delete_clipable(program.title);
  bunny_delete_clipable(program.text);
  bunny_delete_clipable(program.label);
  bunny_free(program.joystick);

  return (response == EXIT_ON_ERROR ? EXIT_FAILURE : EXIT_SUCCESS);
}

