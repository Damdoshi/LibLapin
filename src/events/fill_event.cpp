// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include		"lapin_private.h"

static t_bunny_axis	__bunny_convert_axis(const sf::Joystick::Axis	&axis)
{
  t_bunny_axis		bunny_axis;

  if (axis == sf::Joystick::Axis::X)
    bunny_axis = BA_X;
  else if (axis == sf::Joystick::Axis::Y)
    bunny_axis = BA_Y;
  else if (axis == sf::Joystick::Axis::Z)
    bunny_axis = BA_Z;
  else if (axis == sf::Joystick::Axis::R)
    bunny_axis = BA_R;
  else if (axis == sf::Joystick::Axis::U)
    bunny_axis = BA_U;
  else if (axis == sf::Joystick::Axis::V)
    bunny_axis = BA_V;
  else if (axis == sf::Joystick::Axis::PovX)
    bunny_axis = BA_POVX;
  else if (axis == sf::Joystick::Axis::PovY)
    bunny_axis = BA_POVY;
  else
    bunny_axis = LAST_BUNNY_AXIS;
  return (bunny_axis);
}

bool			__bunny_fill_event(sf::RenderWindow		&window,
					   t_bunny_event	        &b)
{
  auto			a = window.pollEvent();

  if (!a)
    return (false);
  if (a->is<sf::Event::MouseMoved>())
    {
      const auto	*sub_struct = a->getIf<sf::Event::MouseMoved>();

      b.type = BET_MOUSE_MOVED;
      b.mouse_moved.x = sub_struct->position.x;
      b.mouse_moved.y = sub_struct->position.y;
    }
  else if (a->is<sf::Event::MouseMovedRaw>())
    {
      const auto	*sub_struct = a->getIf<sf::Event::MouseMovedRaw>();

      b.type = BET_MOUSE_MOVED_RAW;
      b.mouse_moved.x = sub_struct->delta.x;
      b.mouse_moved.y = sub_struct->delta.y;
    }
  else if (a->is<sf::Event::TextEntered>())
    {
      const auto	*sub_struct = a->getIf<sf::Event::TextEntered>();

      b.type = BET_TEXT_ENTERED;
      b.text.unicode = sub_struct->unicode;
    }
  else if (a->is<sf::Event::KeyPressed>())
    {
      const auto	*sub_struct = a->getIf<sf::Event::KeyPressed>();

      b.type = BET_KEY_PRESSED;
      b.key.sym = (t_bunny_keysym)sub_struct->code;
      b.key.alt = sub_struct->alt;
      b.key.control = sub_struct->control;
      b.key.shift = sub_struct->shift;
      b.key.system = sub_struct->system;
    }
  else if (a->is<sf::Event::KeyReleased>())
    {
      const auto	*sub_struct = a->getIf<sf::Event::KeyReleased>();

      b.type = BET_KEY_RELEASED;
      b.key.sym = (t_bunny_keysym)sub_struct->code;
      b.key.alt = sub_struct->alt;
      b.key.control = sub_struct->control;
      b.key.shift = sub_struct->shift;
      b.key.system = sub_struct->system;
    }
  else if (a->is<sf::Event::Resized>())
    {
      const auto* sub_struct = a->getIf<sf::Event::Resized>();
      b.type = BET_RESIZE_WINDOW;
      b.size.width = sub_struct->size.x;
      b.size.height = sub_struct->size.y;
    }
  else if (a->is<sf::Event::MouseWheelScrolled>())
    {
      const auto	*sub_struct = a->getIf<sf::Event::MouseWheelScrolled>();

      b.type = BET_MOUSE_WHEEL;
      b.wheel.wheel = (int)sub_struct->wheel;
      b.wheel.delta = sub_struct->delta;
      b.wheel.x = sub_struct->position.x;
      b.wheel.y = sub_struct->position.y;
    }
  else if (a->is<sf::Event::MouseButtonPressed>())
    {
      const auto	*sub_struct = a->getIf<sf::Event::MouseButtonPressed>();

      b.type = BET_MOUSE_BUTTON_PRESSED;
      b.mouse_button.button = (t_bunny_mouse_button)sub_struct->button;
      b.mouse_button.x = sub_struct->position.x;
      b.mouse_button.y = sub_struct->position.y;
    }
  else if (a->is<sf::Event::MouseButtonReleased>())
    {
      const auto	*sub_struct = a->getIf<sf::Event::MouseButtonReleased>();

      b.type = BET_MOUSE_BUTTON_RELEASED;
      b.mouse_button.button = (t_bunny_mouse_button)sub_struct->button;
      b.mouse_button.x = sub_struct->position.x;
      b.mouse_button.y = sub_struct->position.y;
    }
  else if (a->is<sf::Event::MouseEntered>())
    b.type = BET_MOUSE_ENTERED;
  else if (a->is<sf::Event::MouseLeft>())
    b.type = BET_MOUSE_LEFT;
  else if (a->is<sf::Event::JoystickButtonPressed>())
    {
      const auto	*sub_struct = a->getIf<sf::Event::JoystickButtonPressed>();

      b.type = BET_JOYSTICK_BUTTON_PRESSED;
      b.joy_button.joystick_id = sub_struct->joystickId;
      b.joy_button.button = sub_struct->button;
    }
  else if (a->is<sf::Event::JoystickButtonReleased>())
    {
      const auto	*sub_struct = a->getIf<sf::Event::JoystickButtonReleased>();

      b.type = BET_JOYSTICK_BUTTON_RELEASED;
      b.joy_button.joystick_id = sub_struct->joystickId;
      b.joy_button.button = sub_struct->button;
    }
  else if (a->is<sf::Event::JoystickMoved>())
    {
      const auto	*sub_struct = a->getIf<sf::Event::JoystickMoved>();

      b.type = BET_JOYSTICK_MOVED;
      b.joy_move.joystick_id = sub_struct->joystickId;
      b.joy_move.axis = __bunny_convert_axis(sub_struct->axis);
      b.joy_move.position = sub_struct->position;
    }
  else if (a->is<sf::Event::JoystickConnected>())
    {
      const auto	*sub_struct = a->getIf<sf::Event::JoystickConnected>();

      b.type = BET_JOYSTICK_CONNECTED;
      b.joy_connect.joystick_id = sub_struct->joystickId;
    }
  else if (a->is<sf::Event::JoystickDisconnected>())
    {
      const auto	*sub_struct = a->getIf<sf::Event::JoystickDisconnected>();

      b.type = BET_JOYSTICK_DISCONNECTED;
      b.joy_connect.joystick_id = sub_struct->joystickId;
    }
  else if (a->is<sf::Event::FocusLost>())
    b.type = BET_LOST_FOCUS;
  else if (a->is<sf::Event::FocusGained>())
    b.type = BET_GAIN_FOCUS;
  else if (a->is<sf::Event::Closed>())
    b.type = BET_CLOSE_WINDOW;
  else if (a->is<sf::Event::TouchBegan>())
    b.type = BET_TOUCH_BEGAN;
  else if (a->is<sf::Event::TouchMoved>())
    b.type = BET_TOUCH_MOVED;
  else if (a->is<sf::Event::TouchEnded>())
    b.type = BET_TOUCH_ENDED;
  else if (a->is<sf::Event::SensorChanged>())
    b.type = BET_SENSOR;
  else
    b.type = BET_UNKNOWN;
  return (true);
}

