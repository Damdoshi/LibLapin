// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

typedef t_bunny_gui_box	*t_bunny_new_boxf(t_bunny_gui_box	*parent,
					  t_bunny_configuration	*cnf);
t_bunny_new_boxf	bunny_new_simple_box;
t_bunny_new_boxf	bunny_new_label_box;
t_bunny_new_boxf	bunny_new_browse_box;

const char		*gl_bunny_box_type[BBT_CUSTOM_BOX] = {
  "box",
  "label",
  "browse"
};
const t_bunny_new_box	gl_bunny_new_box[BBT_CUSTOM_BOX] = {
  bunny_new_simple_box,
  bunny_new_label_box,
  bunny_new_browse_box
};
t_bunny_new_box		gl_bunny_custom_new_box = NULL;

bunny_declare_context(bunny_box);
const t_bunny_context	gl_bunny_box_context =
  {
    bunny_context_key,
    bunny_context_type,

    bunny_box_click,
    bunny_box_move,

    bunny_context_wheel,
    bunny_context_joy_connect,
    bunny_context_joy_button,
    bunny_context_joy_axis,
    bunny_context_get_focus,
    bunny_context_lost_focus,
    bunny_context_resize,

    bunny_box_loop,
    bunny_box_display,

    bunny_context_close,
    NULL,
    bunny_context_message,
    bunny_context_connect,

    bunny_box_entering,
    bunny_box_leaving,

    bunny_context_async_computation,
    bunny_context_event_response
  };
