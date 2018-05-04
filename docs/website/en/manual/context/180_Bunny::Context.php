<div class="prototype">
  $Kclass $CBunny@::$SContext@;<$TT@>
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A A class from which you can inherit. Overload the function you want
  to set inside the context and call $CBunny@::$SSetContext@. The function
  will be called automatically.
</div>
<hr />

<div class="parameters">
  <h3>Member functions that can be overloaded</h3>
  <ul>
    <li>
      t_bunny_response		Key(t_bunny_event_state		state, t_bunny_keysym		sym);
    </li>
    <li>
      t_bunny_response		Text(t_bunny_type		type);
    </li>
    <li>
      t_bunny_response		Click(t_bunny_event_state	state,
			t_bunny_mouse_button	button);
    </li>
    <li>
      t_bunny_response		Move(const t_bunny_position	*relative);
    </li>
    <li>
      t_bunny_response		Wheel(int			wheelid,
			int			delta);
    </li>
    <li>
      t_bunny_response		JoyConnect(t_bunny_event_state	state,
			int			joyid,
			const t_bunny_joystick *info);
    </li>
    <li>
      t_bunny_response		JoyAxis(int			id,
			t_bunny_axis		axis,
			float			value);
    </li>
    <li>
      t_bunny_response		JoyButton(t_bunny_event_state	state,
			int			joyid,
			int			button);
    </li>
    <li>
      t_bunny_response		GetFocus(const t_bunny_window	*win);
    </li>
    <li>
      t_bunny_response		LostFocus(const t_bunny_window	*win);
    </li>
    <li>
      t_bunny_response		Resize(const t_bunny_window	*win,
			const t_bunny_position	*size);
    </li>
    <li>
      t_bunny_response		Close(const t_bunny_window	*win);
    </li>
    <li>
      t_bunny_response		Loop(void);
    </li>
    <li>
      t_bunny_response		Display(void);
    </li>
    <li>
      virtual t_bunny_network	*Netcom(void);
    </li>
    <li>
      t_bunny_response		NetMessage(int			fd,
			const void		*buffer,
			size_t		bufsize);
    </li>
    <li>
      t_bunny_response		NetConnect(int			fd,
			t_bunny_event_state	state);
    </li>
    <li>
      t_bunny_response		Entering(void);
    </li>
    <li>
      void			Leaving(t_bunny_response	return_value);
    </li>
    <li>
      t_bunny_response		AsyncComputation(void		*computed_val);
    </li>
  </ul>
</div>

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>Bunny::Context</li>
  </ul>
</div>

