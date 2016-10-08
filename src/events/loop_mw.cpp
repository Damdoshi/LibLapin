// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include		<unistd.h>
#include		<string.h>
#include		"lapin_private.h"

t_bunny_response	bunny_loop_mw(t_bunny_window	**window,
				      size_t		nwin,
				      unsigned char	freq,
				      void		*data)
{
  sf::Event		event;
  sf::Clock		clock;
  unsigned int		delay;
  t_bunny_response	rep;
  unsigned int		prev;
  unsigned int		now;
  bool			once;
  size_t		i;

  /// How many microseconds
  delay = 1000000.0 / freq;

  rep = GO_ON;
  prev = clock.getElapsedTime().asMicroseconds();
  while (rep == GO_ON)
    {
      once = false;
      now = clock.getElapsedTime().asMicroseconds();
      while (now - prev > delay)
	{
	  once = true;
	  for (i = 0; i < nwin; ++i)
	    {
	      struct bunny_window	*win = (struct bunny_window*)window[i];

	      gl_window = window[i];
	      if (win)
		while (win->window->pollEvent(event))
		  {
		    if (event.type == sf::Event::Closed)
		      {
			if (gl_callback.close)
			  {
			    if ((rep = gl_callback.close(gl_window, data)) != GO_ON)
			      return (rep);
			  }
			else
			  return (EXIT_ON_CROSS);
		      }
		    //////
		    /////		WINDOW
		    ////
		    /// GAIN FOCUS
		    //
		    if (event.type == sf::Event::GainedFocus && gl_callback.get_focus)
		      if ((rep = gl_callback.get_focus(gl_window, data)) != GO_ON)
			return (rep);
		    ////
		    /// LOST FOCUS
		    //
		    if (event.type == sf::Event::LostFocus && gl_callback.lost_focus)
		      if ((rep = gl_callback.lost_focus(gl_window, data)) != GO_ON)
			return (rep);
		    ////
		    /// RESIZE
		    //
		    if (event.type == sf::Event::Resized && gl_callback.resize)
		      {
			t_bunny_position	siz;
			
			siz.x = event.size.width;
			siz.y = event.size.height;
			if ((rep = gl_callback.resize(gl_window, &siz, data)) != GO_ON)
			  return (rep);
		      }
		    
		    ///////
		    //////		KEYBOARD
		    /////
		    ////
		    /// KEYBOARD
		    //
		    if (gl_callback.key != NULL)
		      {
			if (event.type == sf::Event::KeyPressed)
			  {
			    if (event.key.code != sf::Keyboard::Unknown)
			      gl_keyboard[event.key.code] = true;
			    if ((rep = gl_callback.key
				 (GO_DOWN, (t_bunny_keysym)event.key.code, data)) != GO_ON)
			      return (rep);
			  }
			else if (event.type == sf::Event::KeyReleased)
			  {
			    if (event.key.code != sf::Keyboard::Unknown)
			      gl_keyboard[event.key.code] = false;
			    if ((rep = gl_callback.key
				 (GO_UP, (t_bunny_keysym)event.key.code, data)) != GO_ON)
			      return (rep);
			  }
		      }
		    ////
		    /// TEXT INPUT
		    //
		    if (gl_callback.type != NULL && event.type == sf::Event::TextEntered)
		      {
			if ((rep = gl_callback.type(event.text.unicode, data)) != GO_ON)
			  return (rep);
		      }
		    
		    ///////
		    //////		JOYSTICK
		    /////
		    if (gl_callback.connect != NULL)
		      {
			bool				connect;
			
			////
			/// JOYSTICK CONNECT
			//
			if ((connect = (event.type == sf::Event::JoystickConnected)) ||
			    event.type == sf::Event::JoystickDisconnected)
			  {
			    sf::Joystick::Identification	id;
			    int				joyid;
			    int				i;
			    
			    joyid = event.joystickConnect.joystickId;
			    if (connect)
			      {
				id = sf::Joystick::getIdentification(joyid);
				gl_joystick[joyid].connected = true;
				gl_joystick[joyid].name = strdup(id.name.toAnsiString().c_str());
				gl_joystick[joyid].vendor = id.vendorId;
				gl_joystick[joyid].product = id.productId;
				gl_joystick[joyid].nb_button = sf::Joystick::getButtonCount(joyid);
				gl_joystick[joyid].axis = 0;
				for (i = 0; i < sf::Joystick::AxisCount; ++i)
				  gl_joystick[joyid].axis |= (sf::Joystick::hasAxis(joyid, (sf::Joystick::Axis)i) ? 1 : 0) << i;
			      }
			    else
			      {
				gl_joystick[joyid].connected = false;
				free((char*)gl_joystick[joyid].name);
			      }
			    if ((rep = gl_callback.connect
				 (connect ? CONNECTED : DISCONNECTED,
				  joyid, &gl_joystick[joyid], data)) != GO_ON)
			      return (rep);      
			  }
			
			////
			/// JOYSTICK BUTTON
			//
			if (gl_callback.button != NULL)
			  {
			    if (event.type == sf::Event::JoystickButtonPressed)
			      {
				gl_joy_button
				  [event.joystickButton.joystickId][event.joystickButton.button] = true;
				if ((rep = gl_callback.button
				     (GO_DOWN,
				      event.joystickButton.joystickId,
				      event.joystickButton.button,
				      data)) != GO_ON)
				  return (rep);
			      }
			    else if (event.type == sf::Event::JoystickButtonReleased)
			      {
				gl_joy_button
				  [event.joystickButton.joystickId][event.joystickButton.button] = false;
				if ((rep = gl_callback.button
				     (GO_UP,
				      event.joystickButton.joystickId,
				      event.joystickButton.button,
				      data)) != GO_ON)
				  return (rep);
			      }
			  }
			
			////
			/// JOYSTICK AXIS
			//
			if (gl_callback.axis != NULL)
			  {
			    if (event.type == sf::Event::JoystickMoved)
			      {
				gl_joy_axis
				  [event.joystickMove.joystickId][event.joystickMove.axis] =
				  event.joystickMove.position;
				if ((rep = gl_callback.axis
				     (event.joystickMove.joystickId,
				      (t_bunny_axis)event.joystickMove.axis,
				      event.joystickMove.position,
				      data)) != GO_ON)
				  return (rep);
			      }
			  }
		      }
		    
		    ///////
		    //////		MOUSE
		    /////
		    ////
		    /// MOUSE BUTTON
		    //
		    if (gl_callback.click != NULL)
		      {
			if (event.type == sf::Event::MouseButtonPressed)
			  {
			    gl_mouse.x = event.mouseButton.x;
			    gl_mouse.y = event.mouseButton.y;
			    gl_button[event.mouseButton.button] = true;
			    if ((rep = gl_callback.click
				 (GO_DOWN, (t_bunny_mousebutton)event.mouseButton.button, data)) != GO_ON)
			      return (rep);
			  }
			else if (event.type == sf::Event::MouseButtonReleased)
			  {
			    gl_mouse.x = event.mouseButton.x;
			    gl_mouse.y = event.mouseButton.y;		    
			    gl_button[event.mouseButton.button] = false;
			    if ((rep = gl_callback.click
				 (GO_UP, (t_bunny_mousebutton)event.mouseButton.button, data)) != GO_ON)
			      return (rep);
			  }
		      }
		    ////
		    /// MOUSE WHEEL
		    //
		    if (event.type == sf::Event::MouseWheelScrolled)
		      {
			gl_mouse.x = event.mouseWheelScroll.x;
			gl_mouse.y = event.mouseWheelScroll.y;
			if (gl_callback.wheel != NULL)
			  {
			    if ((rep = gl_callback.wheel
				 ((int)event.mouseWheelScroll.wheel,
				  event.mouseWheelScroll.delta,
				  data)) != GO_ON)
			      return (rep);
			  }
		      }
		    ////
		    /// MOUSE MOVE
		    //
		    if (event.type == sf::Event::MouseMoved)
		      {
			t_bunny_position	pos;
			
			pos.x = event.mouseMove.x - gl_mouse.x;
			pos.y = event.mouseMove.y - gl_mouse.y;
			gl_mouse.x = event.mouseMove.x;
			gl_mouse.y = event.mouseMove.y;
			if (gl_callback.move != NULL)
			  {
			    if ((rep = gl_callback.move(&pos, data)) != GO_ON)
			      return (rep);
			  }
		      }
		  }
	    }
	  if (gl_callback.loop != NULL)
	    if ((rep = gl_callback.loop(data)) != GO_ON)
	      return (rep);
	  prev += delay;
	}
      if (once && gl_callback.display != NULL)
	if ((rep = gl_callback.display(data)) != GO_ON)
	  return (rep);
      /// Let the CPU rest a little...
      usleep(delay - (now - prev));
      // usleep(now - prev);
    }
  return (rep);
}

