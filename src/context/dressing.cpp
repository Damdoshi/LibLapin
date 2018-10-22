// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

bunny_declare_context(dressing);

const t_bunny_context	gl_bunny_dressing_context =
  {
    (t_bunny_key)dressing_key,
    bunny_context_type,
    (t_bunny_click)dressing_click,
    (t_bunny_move)dressing_move,
    (t_bunny_wheel)dressing_wheel,
    bunny_context_joy_connect, // Faire les joysticks plus tard
    bunny_context_joy_button,
    bunny_context_joy_axis,
    bunny_context_get_focus,
    bunny_context_lost_focus,
    bunny_context_resize,
    (t_bunny_loop)dressing_loop,
    (t_bunny_display)dressing_display,
    bunny_context_close,
    NULL,
    bunny_context_message,
    bunny_context_connect,
    (t_bunny_loop)dressing_entering,
    (t_bunny_leaving_context)dressing_leaving,
    bunny_context_async_computation,
    bunny_context_event_response
  };

