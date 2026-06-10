// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

/**
 * @doc-symbol bunny_set_wheel_response
 * @doc-module events
 * @doc-kind function
 * @doc-order 150
 * @doc-since 5
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Registers the mouse wheel callback.
 * @param w The callback to call.
 * @see t_bunny_wheel
 *
 * @doc-lang fr
 * @brief Enregistre le callback de molette de souris.
 * @param w Le callback à appeler.
 * @see t_bunny_wheel
 */
void			bunny_set_wheel_response(t_bunny_wheel	w)
{
  gl_callback.wheel = w;
}

/**
 * @doc-symbol bunny_set_text_response
 * @doc-module events
 * @doc-kind function
 * @doc-order 70
 * @doc-since 5
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Registers the text input callback.
 * @param type The callback to call.
 * @see t_bunny_type
 *
 * @doc-lang fr
 * @brief Enregistre le callback de saisie de texte.
 * @param type Le callback à appeler.
 * @see t_bunny_type
 */
void			bunny_set_text_response(t_bunny_type	type)
{
  gl_callback.type = type;
}

/**
 * @doc-symbol bunny_set_move_response
 * @doc-module events
 * @doc-kind function
 * @doc-order 120
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Registers the mouse movement callback.
 * @param move The callback to call.
 * @see t_bunny_move, bunny_get_mouse_position
 *
 * @doc-lang fr
 * @brief Enregistre le callback de déplacement de souris.
 * @param move Le callback à appeler.
 * @see t_bunny_move, bunny_get_mouse_position
 */
void			bunny_set_move_response(t_bunny_move	move)
{
  gl_callback.move = move;
}

/**
 * @doc-symbol bunny_set_lost_focus_response
 * @doc-module events
 * @doc-kind function
 * @doc-order 290
 * @doc-since 7
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Registers the window focus loss callback.
 * @param j The callback to call.
 * @see t_bunny_lost_focus
 *
 * @doc-lang fr
 * @brief Enregistre le callback de perte de focus de fenêtre.
 * @param j Le callback à appeler.
 * @see t_bunny_lost_focus
 */
void			bunny_set_lost_focus_response(t_bunny_lost_focus	j)
{
  gl_callback.lost_focus = j;
}

/**
 * @doc-symbol bunny_set_joy_connect_response
 * @doc-module events
 * @doc-kind function
 * @doc-order 180
 * @doc-since 5
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Registers the joystick connection callback.
 * @param j The callback to call.
 * @see t_bunny_joy_connect, bunny_get_joy_info
 *
 * @doc-lang fr
 * @brief Enregistre le callback de connexion de joystick.
 * @param j Le callback à appeler.
 * @see t_bunny_joy_connect, bunny_get_joy_info
 */
void			bunny_set_joy_connect_response(t_bunny_joy_connect	j)
{
  gl_callback.connect = j;
}

/**
 * @doc-symbol bunny_set_joy_axis_response
 * @doc-module events
 * @doc-kind function
 * @doc-order 200
 * @doc-since 5
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Registers the joystick axis callback.
 * @param j The callback to call.
 * @see t_bunny_joy_axis, bunny_get_joy_axis, bunny_set_joy_axis_minimum_offset
 *
 * @doc-lang fr
 * @brief Enregistre le callback de axe de joystick.
 * @param j Le callback à appeler.
 * @see t_bunny_joy_axis, bunny_get_joy_axis, bunny_set_joy_axis_minimum_offset
 */
void			bunny_set_joy_axis_response(t_bunny_joy_axis	j)
{
  gl_callback.axis = j;
}

/**
 * @doc-symbol bunny_set_connect_response
 * @doc-module events
 * @doc-kind function
 * @doc-order 490
 * @doc-since 11
 * @doc-until latest
 * @doc-level expert
 *
 * @doc-lang en
 * @brief Registers the network connection callback.
 * @param func The callback to call.
 * @see t_bunny_connect_response, bunny_set_message_response
 *
 * @doc-lang fr
 * @brief Enregistre le callback de connexion réseau.
 * @param func Le callback à appeler.
 * @see t_bunny_connect_response, bunny_set_message_response
 */
void			bunny_set_connect_response(t_bunny_connect_response func)
{
  gl_callback.net_connect = func;
}

/**
 * @doc-symbol bunny_set_click_response
 * @doc-module events
 * @doc-kind function
 * @doc-order 90
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Registers the mouse button callback.
 * @param click The callback to call.
 * @see t_bunny_click, bunny_get_mouse_button
 *
 * @doc-lang fr
 * @brief Enregistre le callback de bouton de souris.
 * @param click Le callback à appeler.
 * @see t_bunny_click, bunny_get_mouse_button
 */
void			bunny_set_click_response(t_bunny_click	click)
{
  gl_callback.click = click;
}

/**
 * @doc-symbol bunny_set_close_response
 * @doc-module events
 * @doc-kind function
 * @doc-order 330
 * @doc-since 7
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Registers the window close callback.
 * @param j The callback to call.
 * @see t_bunny_close, bunny_loop_mw
 *
 * @doc-lang fr
 * @brief Enregistre le callback de fermeture de fenêtre.
 * @param j Le callback à appeler.
 * @see t_bunny_close, bunny_loop_mw
 */
void			bunny_set_close_response(t_bunny_close	j)
{
  gl_callback.close = j;
}

/**
 * @doc-symbol bunny_set_get_focus_response
 * @doc-module events
 * @doc-kind function
 * @doc-order 270
 * @doc-since 7
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Registers the window focus gain callback.
 * @param j The callback to call.
 * @see t_bunny_get_focus
 *
 * @doc-lang fr
 * @brief Enregistre le callback de gain de focus de fenêtre.
 * @param j Le callback à appeler.
 * @see t_bunny_get_focus
 */
void			bunny_set_get_focus_response(t_bunny_get_focus	j)
{
  gl_callback.get_focus = j;
}

/**
 * @doc-symbol bunny_set_joy_button_response
 * @doc-module events
 * @doc-kind function
 * @doc-order 240
 * @doc-since 5
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Registers the joystick button callback.
 * @param j The callback to call.
 * @see t_bunny_joy_button, bunny_get_joy_button
 *
 * @doc-lang fr
 * @brief Enregistre le callback de bouton de joystick.
 * @param j Le callback à appeler.
 * @see t_bunny_joy_button, bunny_get_joy_button
 */
void			bunny_set_joy_button_response(t_bunny_joy_button	j)
{
  gl_callback.button = j;
}

/**
 * @doc-symbol bunny_set_key_response
 * @doc-module events
 * @doc-kind function
 * @doc-order 40
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Registers the keyboard key callback.
 * @param key The callback to call.
 * @see t_bunny_key, bunny_get_keyboard
 *
 * @doc-lang fr
 * @brief Enregistre le callback de touche clavier.
 * @param key Le callback à appeler.
 * @see t_bunny_key, bunny_get_keyboard
 */
void			bunny_set_key_response(t_bunny_key	key)
{
  gl_callback.key = key;
}

/**
 * @doc-symbol bunny_set_message_response
 * @doc-module events
 * @doc-kind function
 * @doc-order 470
 * @doc-since 11
 * @doc-until latest
 * @doc-level expert
 *
 * @doc-lang en
 * @brief Registers the network message callback.
 * @param func The callback to call.
 * @see t_bunny_message_response, bunny_set_connect_response
 *
 * @doc-lang fr
 * @brief Enregistre le callback de message réseau.
 * @param func Le callback à appeler.
 * @see t_bunny_message_response, bunny_set_connect_response
 */
void			bunny_set_message_response(t_bunny_message_response func)
{
  gl_callback.net_message = func;
}

/**
 * @doc-symbol bunny_set_resize_response
 * @doc-module events
 * @doc-kind function
 * @doc-order 310
 * @doc-since 7
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Registers the window resize callback.
 * @param j The callback to call.
 * @see t_bunny_resize
 *
 * @doc-lang fr
 * @brief Enregistre le callback de redimensionnement de fenêtre.
 * @param j Le callback à appeler.
 * @see t_bunny_resize
 */
void			bunny_set_resize_response(t_bunny_resize	j)
{
  gl_callback.resize = j;
}

/**
 * @doc-symbol bunny_set_leaving_context_response
 * @doc-module events
 * @doc-kind function
 * @doc-order 520
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Registers the context leaving callback.
 * @param func The callback to call.
 * @see t_bunny_leaving_context, bunny_set_entering_context_response
 *
 * @doc-lang fr
 * @brief Enregistre le callback de sortie de contexte.
 * @param func Le callback à appeler.
 * @see t_bunny_leaving_context, bunny_set_entering_context_response
 */
void			bunny_set_leaving_context_response(t_bunny_leaving_context func)
{
  gl_callback.leaving_context = func;
}

/**
 * @doc-symbol bunny_set_entering_context_response
 * @doc-module events
 * @doc-kind function
 * @doc-order 500
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Registers the context entering callback.
 * @param func The callback to call.
 * @see t_bunny_loop, bunny_set_leaving_context_response
 *
 * @doc-lang fr
 * @brief Enregistre le callback de entrée dans le contexte.
 * @param func Le callback à appeler.
 * @see t_bunny_loop, bunny_set_leaving_context_response
 */
void			bunny_set_entering_context_response(t_bunny_loop func)
{
  gl_callback.entering_context = func;
}
