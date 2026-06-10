// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

typedef t_bunny_gui_box	*t_bunny_new_boxf(t_bunny_gui_box	*parent,
					  t_bunny_configuration	*cnf);
t_bunny_new_boxf	bunny_new_simple_box;
t_bunny_new_boxf	bunny_new_label_box;

/**
 * @doc
 * @doc-symbol gl_bunny_box_type
 * @doc-kind variable
 * @doc-module context
 * @doc-order 410
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Names of built-in GUI box types.
 * @see t_bunny_box_system
 *
 * @doc-lang fr
 * @brief Noms des types de boîtes GUI intégrées.
 * @see t_bunny_box_system
 */
const char		*gl_bunny_box_type[BBT_CUSTOM_BOX] = {
  "box",
  "label"
};
/**
 * @doc
 * @doc-symbol gl_bunny_new_box
 * @doc-kind variable
 * @doc-module context
 * @doc-order 451
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Constructor table for built-in GUI box types.
 * @see t_bunny_box_system
 *
 * @doc-lang fr
 * @brief Table de constructeurs des types de boîtes GUI intégrées.
 * @see t_bunny_box_system
 */
const t_bunny_new_box	gl_bunny_new_box[BBT_CUSTOM_BOX] = {
  bunny_new_simple_box,
  bunny_new_label_box
};
/**
 * @doc
 * @doc-symbol gl_bunny_custom_new_box
 * @doc-kind variable
 * @doc-module context
 * @doc-order 452
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Optional constructor used for custom GUI boxes.
 * @see t_bunny_box_system
 *
 * @doc-lang fr
 * @brief Constructeur optionnel utilisé pour les boîtes GUI personnalisées.
 * @see t_bunny_box_system
 */
t_bunny_new_box		gl_bunny_custom_new_box = NULL;

bunny_declare_context(bunny_box);
/**
 * @doc
 * @doc-symbol gl_bunny_box_context
 * @doc-kind variable
 * @doc-module context
 * @doc-order 470
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Built-in context implementing the GUI box system.
 * @see t_bunny_box_system
 *
 * @doc-lang fr
 * @brief Contexte intégré implémentant le système GUI box.
 * @see t_bunny_box_system
 */
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
    bunny_context_message,
    bunny_context_connect,

    bunny_box_entering,
    bunny_box_leaving,

    bunny_context_async_computation,
    bunny_context_event_response
  };
