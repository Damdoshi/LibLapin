// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliotheque Lapin

#include		<unistd.h>
#include		<string.h>
#include		"lapin_private.h"

#define			PATTERN		"%p window, %zu nbr_window, %u frequency, %p parameter ("

const t_bunny_event	*__bunny_event_convert(const sf::Event	&);

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
  int			display_cnt;

  gl_loop_data = data;

  scream_log_if(PATTERN "Entering)", "event", window, nwin, freq, data);

  /// How many microseconds
  delay = 1000000.0 / freq;
  gl_bunny_frequency = freq;
  if (gl_callback.entering_context != NULL)
    {
      scream_log_if(PATTERN "enter_context)", "event", window, nwin, freq, data);
      if ((rep = gl_callback.entering_context(data)) < GO_ON)
	goto end;
    }
  else
    rep = GO_ON;

  display_cnt = 0;
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
		    // Generic event handler
		    if (gl_callback.event)
		      {
			scream_log_if(PATTERN "event %p)", "event", window, nwin, freq, data, gl_window);
			if ((rep = gl_callback.event
			     (__bunny_event_convert(event), data)) < GO_ON)
			  goto end;
		      }

		    if (event.type == sf::Event::Closed)
		      {
			if (gl_callback.close)
			  {
			    scream_log_if(PATTERN "close window %p)", "event", window, nwin, freq, data, gl_window);
			    if ((rep = gl_callback.close(gl_window, data)) < GO_ON)
			      goto end;
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
		      {
			scream_log_if(PATTERN "gain_focus %p)", "event", window, nwin, freq, data, gl_window);
			if ((rep = gl_callback.get_focus(gl_window, data)) < GO_ON)
			  goto end;
		      }
		    ////
		    /// LOST FOCUS
		    //
		    if (event.type == sf::Event::LostFocus && gl_callback.lost_focus)
		      {
			scream_log_if(PATTERN "lost_focus %p)", "event", window, nwin, freq, data, gl_window);
			if ((rep = gl_callback.lost_focus(gl_window, data)) < GO_ON)
			  goto end;
		      }
		    ////
		    /// RESIZE
		    //
		    if (event.type == sf::Event::Resized && gl_callback.resize)
		      {
			t_bunny_position	siz;

			siz.x = event.size.width;
			siz.y = event.size.height;
			scream_log_if(PATTERN "reisze %p)", "event", window, nwin, freq, data, gl_window);
			if ((rep = gl_callback.resize(gl_window, &siz, data)) < GO_ON)
			  goto end;
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
			    scream_log_if(PATTERN "keydown)", "event", window, nwin, freq, data);
			    if ((rep = gl_callback.key
				 (GO_DOWN, (t_bunny_keysym)event.key.code, data)) < GO_ON)
			      goto end;
			  }
			else if (event.type == sf::Event::KeyReleased)
			  {
			    if (event.key.code != sf::Keyboard::Unknown)
			      gl_keyboard[event.key.code] = false;
			    scream_log_if(PATTERN "keyup)", "event", window, nwin, freq, data);
			    if ((rep = gl_callback.key
				 (GO_UP, (t_bunny_keysym)event.key.code, data)) < GO_ON)
			      goto end;
			  }
		      }
		    ////
		    /// TEXT INPUT
		    //
		    if (gl_callback.type != NULL && event.type == sf::Event::TextEntered)
		      {
			scream_log_if(PATTERN "text)", "event", window, nwin, freq, data);
			if ((rep = gl_callback.type(event.text.unicode, data)) < GO_ON)
			  goto end;
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
				gl_joystick[joyid].name = bunny_strdup(id.name.toAnsiString().c_str());
				gl_joystick[joyid].vendor = id.vendorId;
				gl_joystick[joyid].product = id.productId;
				gl_joystick[joyid].nb_button = sf::Joystick::getButtonCount(joyid);
				gl_joystick[joyid].axis = 0;
				for (i = 0; i < sf::Joystick::AxisCount; ++i)
				  gl_joystick[joyid].axis |= (sf::Joystick::hasAxis(joyid, (sf::Joystick::Axis)i) ? 1 : 0) << i;
				scream_log_if(PATTERN "joyconnect)", "event", window, nwin, freq, data);
			      }
			    else
			      {
				gl_joystick[joyid].connected = false;
				if (gl_joystick[joyid].name)
				  {
				    bunny_free((char*)gl_joystick[joyid].name);
				    gl_joystick[joyid].name = NULL;
				  }
				scream_log_if(PATTERN "joydisconnect)", "event", window, nwin, freq, data);
			      }
			    if ((rep = gl_callback.connect
				 (connect ? CONNECTED : DISCONNECTED,
				  joyid, &gl_joystick[joyid], data)) < GO_ON)
			      goto end;
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
				scream_log_if(PATTERN "joydown)", "event", window, nwin, freq, data);
				if ((rep = gl_callback.button
				     (GO_DOWN,
				      event.joystickButton.joystickId,
				      event.joystickButton.button,
				      data)) < GO_ON)
				  goto end;
			      }
			    else if (event.type == sf::Event::JoystickButtonReleased)
			      {
				gl_joy_button
				  [event.joystickButton.joystickId][event.joystickButton.button] = false;
				scream_log_if(PATTERN "joyup)", "event", window, nwin, freq, data);
				if ((rep = gl_callback.button
				     (GO_UP,
				      event.joystickButton.joystickId,
				      event.joystickButton.button,
				      data)) < GO_ON)
				  goto end;
			      }
			  }

			////
			/// JOYSTICK AXIS
			//
			if (gl_callback.axis != NULL)
			  {
			    if (event.type == sf::Event::JoystickMoved)
			      {
				if (fabs(gl_joy_axis
					 [event.joystickMove.joystickId]
					 [event.joystickMove.axis]
					 - event.joystickMove.position)
				    > gl_axis_offset[event.joystickMove.axis])
				  {
				    gl_joy_axis
				      [event.joystickMove.joystickId][event.joystickMove.axis] =
				      event.joystickMove.position;
				    scream_log_if(PATTERN "joymove)", "event", window, nwin, freq, data);
				    if ((rep = gl_callback.axis
					 (event.joystickMove.joystickId,
					  (t_bunny_axis)event.joystickMove.axis,
					  event.joystickMove.position,
					  data)) < GO_ON)
				      goto end;
				  }
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
			    scream_log_if(PATTERN "mousedown)", "event", window, nwin, freq, data);
			    if ((rep = gl_callback.click
				 (GO_DOWN, (t_bunny_mousebutton)event.mouseButton.button, data)) < GO_ON)
			      goto end;
			  }
			else if (event.type == sf::Event::MouseButtonReleased)
			  {
			    gl_mouse.x = event.mouseButton.x;
			    gl_mouse.y = event.mouseButton.y;
			    gl_button[event.mouseButton.button] = false;
			    scream_log_if(PATTERN "mouseup)", "event", window, nwin, freq, data);
			    if ((rep = gl_callback.click
				 (GO_UP, (t_bunny_mousebutton)event.mouseButton.button, data)) < GO_ON)
			      goto end;
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
			    scream_log_if(PATTERN "mousewheel)", "event", window, nwin, freq, data);
			    if ((rep = gl_callback.wheel
				 ((int)event.mouseWheelScroll.wheel,
				  event.mouseWheelScroll.delta,
				  data)) < GO_ON)
			      goto end;
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
			    scream_log_if(PATTERN "mousemove)", "event", window, nwin, freq, data);
			    if ((rep = gl_callback.move(&pos, data)) < GO_ON)
			      goto end;
			  }
		      }
		  }
	    }

	  /// ASYNCHRONOUS COMPUTATION
	  if (gl_callback.async_computation_response)
	    {
	      while (gl_completed_tasks.empty() == false)
		if ((gl_callback.async_computation_response(gl_completed_tasks.front(), data)) < GO_ON)
		  {
		    gl_completed_tasks.pop();
		    goto end;
		  }
		else
		  gl_completed_tasks.pop();
	    }

	  bunny_asynclock(delay, BCO_BEFORE_LOOP_MAIN_FUNCTION);
	  if (gl_callback.loop != NULL)
	    {
	      scream_log_if(PATTERN "loop)", "event", window, nwin, freq, data);
	      if ((rep = gl_callback.loop(data)) < GO_ON)
		goto end;
	    }
	  bunny_asynclock(delay, BCO_AFTER_LOOP_MAIN_FUNCTION);
	  prev += delay;
	}
      if (once && gl_callback.display != NULL)
	{
	  if (delay - (now - prev) > 0.05 * delay || display_cnt > 20)
	    {
	      display_cnt = 0;
	      scream_log_if(PATTERN "display)", "event", window, nwin, freq, data);
	      if ((rep = gl_callback.display(data)) < GO_ON)
		goto end;
	    }
	  else
	    display_cnt += 1;
	}

      /// Let the CPU rest a little...
      if (gl_callback.netcom == NULL)
	{
	  if (delay > now - prev)
	    bunny_usleep(delay - (now - prev));
	}
      else
	network_event((delay - (now - prev)) / 1000.0, data);
    }
 end:
  if (gl_callback.leaving_context != NULL)
    {
      scream_log_if(PATTERN "leave_context)", "event", window, nwin, freq, data);
      gl_callback.leaving_context(rep, data);
    }
  for (i = 0; rep != SWITCH_WINDOW && i < nwin; ++i)
    {
      struct bunny_window	*win = (struct bunny_window*)window[i];

      if (win)
	while (win->window->pollEvent(event));
    }

  while (gl_completed_tasks.empty() == false)
    gl_completed_tasks.pop();

  scream_log_if("%p window, %zu nbr_window, %u frequency, %p parameter -> %d (Exiting)", "event", window, nwin, freq, data, rep);
  return (rep);
}
