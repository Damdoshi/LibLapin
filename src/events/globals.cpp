// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include		<SFML/Window.hpp>
#include		"lapin.h"

// 8 with standard SFML. 12 with custom SFML.
const size_t		gl_maximum_joystick = sf::Joystick::Count;

const char		*gl_bunny_keysym[BKS_LAST_KEY] =
  {
    "A",
    "B",
    "C",
    "D",
    "E",
    "F",
    "G",
    "H",
    "I",
    "J",
    "K",
    "L",
    "M",
    "N",
    "O",
    "P",
    "Q",
    "R",
    "S",
    "T",
    "U",
    "V",
    "W",
    "X",
    "Y",
    "Z",
    "0",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "Esc",
    "LeftCtrl",
    "LeftShift",
    "LeftAlt",
    "LeftSystem",
    "RightCtrl",
    "RightShift",
    "RightAlt",
    "RightSystem",
    "Menu",
    "[",
    "]",
    ";",
    ",",
    ".",
    "'",
    "/",
    "\\",
    "~",
    "=",
    "-",
    "Space",
    "Return",
    "Backspace",
    "Tab",
    "PageUp",
    "PageDown",
    "End",
    "Home",
    "Insert",
    "Delete",
    "+",
    "-",
    "*",
    "/",
    "Left",
    "Right",
    "Up",
    "Down",
    "Numpad0",
    "Numpad1",
    "Numpad2",
    "Numpad3",
    "Numpad4",
    "Numpad5",
    "Numpad6",
    "Numpad7",
    "Numpad8",
    "Numpad9",
    "F1",
    "F2",
    "F3",
    "F4",
    "F5",
    "F6",
    "F7",
    "F8",
    "F9",
    "F10",
    "F11",
    "F12",
    "F13",
    "F14",
    "F15",
    "Pause"
  };

const char			*bunny_get_keyname(t_bunny_keysym	sym)
{
  static const char		*unknown = "Unknown";

  if (sym == BKS_UNKNOWN)
    return (unknown);
  if (sym < BKS_LAST_KEY)
    return (gl_bunny_keysym[sym]);
  return (gl_bunny_keysym[0]);
}
