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
# define			LAST_BUNNY_BUTTON		32

/*!
** The axis a library can manage on a single joystick
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

extern const char		*gl_bunny_keysym[BKS_LAST_KEY];

const char			*bunny_get_keyname(t_bunny_keysym	sym);

extern const size_t		gl_maximum_joystick;

#endif	/*			__LAPIN_ENUM_H__	*/
