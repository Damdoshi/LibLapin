/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Bibliotheque Lapin
*/

/*!
** \file enum.h
** Collection of symbolic constants used by differents functions from events to vector font.
*/

#ifndef				__LAPIN_ENUM_H__
# define			__LAPIN_ENUM_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif

/*!
** The maximum buttons the library can manage on a single joystick
*/
/**
 * @doc-symbol LAST_BUNNY_BUTTON
 * @doc-module events
 * @doc-kind macro
 * @doc-order 5
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Maximum number of buttons stored for each joystick.
 * @description This constant defines the second dimension of the array returned by bunny_get_joy_button.
 * @see bunny_get_joy_button, t_bunny_joy_button
 *
 * @doc-lang fr
 * @brief Nombre maximal de boutons mémorisés pour chaque joystick.
 * @description Cette constante définit la seconde dimension du tableau renvoyé par bunny_get_joy_button.
 * @see bunny_get_joy_button, t_bunny_joy_button
 */
# define			LAST_BUNNY_BUTTON		32

/*!
** The axis a library can manage on a single joystick
*/
/**
 * @doc-symbol t_bunny_axis
 * @doc-module events
 * @doc-kind type
 * @doc-order 188
 * @doc-since 5
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Enumerates joystick axes handled by LibLapin.
 * @description Axis values are bit flags so they can also describe the set of axes available on a joystick.
 * @param BA_X The X axis.
 * @param BA_Y The Y axis.
 * @param BA_Z The Z axis.
 * @param BA_R The R axis.
 * @param BA_U The U axis.
 * @param BA_V The V axis.
 * @param BA_POVX The horizontal POV axis.
 * @param BA_POVY The vertical POV axis.
 * @param LAST_BUNNY_AXIS The number of joystick axes stored by LibLapin.
 * @see t_bunny_joy_axis, bunny_get_joy_axis
 *
 * @doc-lang fr
 * @brief Énumère les axes de joystick gérés par LibLapin.
 * @description Les valeurs d'axe sont des drapeaux binaires et peuvent donc aussi décrire l'ensemble des axes disponibles sur un joystick.
 * @param BA_X L'axe X.
 * @param BA_Y L'axe Y.
 * @param BA_Z L'axe Z.
 * @param BA_R L'axe R.
 * @param BA_U L'axe U.
 * @param BA_V L'axe V.
 * @param BA_POVX L'axe POV horizontal.
 * @param BA_POVY L'axe POV vertical.
 * @param LAST_BUNNY_AXIS Le nombre d'axes de joystick mémorisés par LibLapin.
 * @see t_bunny_joy_axis, bunny_get_joy_axis
 */
typedef enum			e_bunny_axis
  {
    BA_X			= 1,
    BA_Y			= 2,
    BA_Z			= 4,
    BA_R			= 8,
    BA_U			= 16,
    BA_V			= 32,
    BA_POVX			= 64,
    BA_POVY			= 128,
    LAST_BUNNY_AXIS		= 8
  }				t_bunny_axis;

/*!
** The mouse buttons the library can manage
*/
/**
 * @doc-symbol t_bunny_mouse_button
 * @doc-module events
 * @doc-kind type
 * @doc-order 75
 * @doc-since 2
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Enumerates mouse buttons handled by LibLapin.
 * @param BMB_LEFT The left mouse button.
 * @param BMB_RIGHT The right mouse button.
 * @param BMB_MIDDLE The middle mouse button.
 * @param BMB_EXTRABUTTON0 The first extra mouse button.
 * @param BMB_EXTRABUTTON1 The second extra mouse button.
 * @param LAST_BUNNY_MOUSEBUTTON The number of mouse buttons stored by LibLapin.
 * @see t_bunny_click, bunny_get_mouse_button
 *
 * @doc-lang fr
 * @brief Énumère les boutons de souris gérés par LibLapin.
 * @param BMB_LEFT Le bouton gauche de la souris.
 * @param BMB_RIGHT Le bouton droit de la souris.
 * @param BMB_MIDDLE Le bouton central de la souris.
 * @param BMB_EXTRABUTTON0 Le premier bouton supplémentaire de la souris.
 * @param BMB_EXTRABUTTON1 Le second bouton supplémentaire de la souris.
 * @param LAST_BUNNY_MOUSEBUTTON Le nombre de boutons de souris mémorisés par LibLapin.
 * @see t_bunny_click, bunny_get_mouse_button
 */
typedef enum			e_bunny_mouse_button
  {
    BMB_LEFT,
    BMB_RIGHT,
    BMB_MIDDLE,
    BMB_EXTRABUTTON0,
    BMB_EXTRABUTTON1,
    LAST_BUNNY_MOUSEBUTTON
  }				t_bunny_mouse_button;

/*!
** The keys the library can manage on keypressed and keyreleased events.
*/
/**
 * @doc-symbol t_bunny_keysym
 * @doc-module events
 * @doc-kind type
 * @doc-order 25
 * @doc-since 2
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Enumerates keyboard keys handled by LibLapin.
 * @description These symbols are used by key press and key release callbacks. Use bunny_get_keyname to turn a symbol into a printable name.
 * @param BKS_UNKNOWN Unknown or unsupported key.
 * @param BKS_LAST_KEY The number of key symbols stored by LibLapin.
 * @see t_bunny_key, bunny_set_key_response, bunny_get_keyname, gl_bunny_keysym
 *
 * @doc-lang fr
 * @brief Énumère les touches de clavier gérées par LibLapin.
 * @description Ces symboles sont utilisés par les callbacks d'appui et de relâchement de touches. Utilisez bunny_get_keyname pour transformer un symbole en nom affichable.
 * @param BKS_UNKNOWN Touche inconnue ou non prise en charge.
 * @param BKS_LAST_KEY Le nombre de symboles de touches mémorisés par LibLapin.
 * @see t_bunny_key, bunny_set_key_response, bunny_get_keyname, gl_bunny_keysym
 */
typedef enum			e_bunny_keysym
  {
    BKS_UNKNOWN			= -1,
    BKS_A,
    BKS_B,
    BKS_C,
    BKS_D,
    BKS_E,
    BKS_F,
    BKS_G,
    BKS_H,
    BKS_I,
    BKS_J,
    BKS_K,
    BKS_L,
    BKS_M,
    BKS_N,
    BKS_O,
    BKS_P,
    BKS_Q,
    BKS_R,
    BKS_S,
    BKS_T,
    BKS_U,
    BKS_V,
    BKS_W,
    BKS_X,
    BKS_Y,
    BKS_Z,
    BKS_0,
    BKS_1,
    BKS_2,
    BKS_3,
    BKS_4,
    BKS_5,
    BKS_6,
    BKS_7,
    BKS_8,
    BKS_9,
    BKS_ESCAPE,
    BKS_LCONTROL,
    BKS_LSHIFT,
    BKS_LALT,
    BKS_LSYSTEM,
    BKS_RCONTROL,
    BKS_RSHIFT,
    BKS_RALT,
    BKS_RSYSTEM,
    BKS_MENU,
    BKS_LBRACKET,
    BKS_RBRACKET,
    BKS_SEMICOLON,
    BKS_COMMA,
    BKS_PERIOD,
    BKS_QUOTE,
    BKS_SLASH,
    BKS_BACKSLASH,
    BKS_TILDE,
    BKS_EQUAL,
    BKS_DASH,
    BKS_SPACE,
    BKS_RETURN,
    BKS_BACKSPACE,
    BKS_TAB,
    BKS_PAGEUP,
    BKS_PAGEDOWN,
    BKS_END,
    BKS_HOME,
    BKS_INSERT,
    BKS_DELETE,
    BKS_ADD,
    BKS_SUBTRACT,
    BKS_MULTIPLY,
    BKS_DIVIDE,
    BKS_LEFT,
    BKS_RIGHT,
    BKS_UP,
    BKS_DOWN,
    BKS_NUMPAD0,
    BKS_NUMPAD1,
    BKS_NUMPAD2,
    BKS_NUMPAD3,
    BKS_NUMPAD4,
    BKS_NUMPAD5,
    BKS_NUMPAD6,
    BKS_NUMPAD7,
    BKS_NUMPAD8,
    BKS_NUMPAD9,
    BKS_F1,
    BKS_F2,
    BKS_F3,
    BKS_F4,
    BKS_F5,
    BKS_F6,
    BKS_F7,
    BKS_F8,
    BKS_F9,
    BKS_F10,
    BKS_F11,
    BKS_F12,
    BKS_F13,
    BKS_F14,
    BKS_F15,
    BKS_PAUSE,
    BKS_LAST_KEY
  }				t_bunny_keysym;

/**
 * @doc-symbol gl_bunny_keysym
 * @doc-module events
 * @doc-kind global
 * @doc-order 27
 * @doc-since 2
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Array of printable key names indexed by t_bunny_keysym.
 * @description Prefer bunny_get_keyname when the symbol may be out of range, because it safely returns a fallback name.
 * @see t_bunny_keysym, bunny_get_keyname
 *
 * @doc-lang fr
 * @brief Tableau de noms de touches affichables indexé par t_bunny_keysym.
 * @description Préférez bunny_get_keyname lorsque le symbole peut être hors limites, car cette fonction renvoie un nom de secours sans danger.
 * @see t_bunny_keysym, bunny_get_keyname
 */
extern const char		*gl_bunny_keysym[BKS_LAST_KEY];

const char			*bunny_get_keyname(t_bunny_keysym	sym);

/**
 * @doc-symbol gl_maximum_joystick
 * @doc-module events
 * @doc-kind global
 * @doc-order 187
 * @doc-since 5
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Maximum number of joystick slots supported by the backend.
 * @description This value is provided by the underlying window system backend and is also exposed through the compatibility macro LAST_BUNNY_JOYSTICK.
 * @see t_bunny_joystick, bunny_get_joy_info
 *
 * @doc-lang fr
 * @brief Nombre maximal d'emplacements de joystick pris en charge par le moteur sous-jacent.
 * @description Cette valeur est fournie par le moteur de fenêtre sous-jacent et est aussi exposée par la macro de compatibilité LAST_BUNNY_JOYSTICK.
 * @see t_bunny_joystick, bunny_get_joy_info
 */
extern const size_t		gl_maximum_joystick;

#endif	/*			__LAPIN_ENUM_H__	*/
