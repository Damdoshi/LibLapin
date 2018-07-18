// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include		"lapin_private.h"

const t_bunny_event	*__bunny_event_convert(const sf::Event	&a)
{
  static t_bunny_event	b;

  switch (b.type = (t_bunny_event_type)a.type)
    {
    case BET_RESIZE_WINDOW:
      memcpy(&b.size, &a.size, sizeof(b.size));
      break ;
    case BET_TEXT_ENTERED:
      memcpy(&b.text, &a.text, sizeof(b.text));
      break ;
    case BET_KEY_PRESSED:
    case BET_KEY_RELEASED:
      memcpy(&b.key, &a.key, sizeof(b.key));
      break ;
    case __BET_UNUSED0:
      b.wheel.wheel = 0;
      b.wheel.delta = a.mouseWheel.delta;
      b.wheel.x = a.mouseWheel.x;
      b.wheel.y = a.mouseWheel.y;
      break ;
    case BET_MOUSE_WHEEL:
      memcpy(&b.wheel, &a.mouseWheelScroll, sizeof(b.wheel));
      break ;
    case BET_MOUSE_BUTTON_PRESSED:
    case BET_MOUSE_BUTTON_RELEASED:
      memcpy(&b.mouse_button, &a.mouseButton, sizeof(b.mouse_button));
      break ;
    case BET_MOUSE_MOVED:
      memcpy(&b.mouse_moved, &a.mouseMove, sizeof(b.mouse_moved));
      break ;
    case BET_JOYSTICK_BUTTON_PRESSED:
    case BET_JOYSTICK_BUTTON_RELEASED:
      memcpy(&b.joy_button, &a.joystickButton, sizeof(b.joy_button));
      break ;
    case BET_JOYSTICK_MOVED:
      memcpy(&b.joy_move, &a.joystickMove, sizeof(b.joy_move));
      break ;
    case BET_JOYSTICK_CONNECTED:
    case BET_JOYSTICK_DISCONNECTED:
      memcpy(&b.joy_connect, &a.joystickConnect, sizeof(b.joy_connect));
    default:
      break ;
    }
  return (&b);
}
