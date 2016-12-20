// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2017
//
// LibLapin: C++ Loop stone
// Wrapper for bunny_loop response function:
// - Allow you to use virtual member-functions instead of plain function pointer.
// - You cannot mix both!
// - There is a small overhead (+1 function call for every type of events,
//   and all events are listened against only listened events are the one
//   you need)
//
// To use it, your class must inherit from it and template it by the type
// of itself. 
// Exemple:
// class Credit;
// class Credit : public hbs::LoopStone<Credit> {};

#ifndef					__HBS_LOOP_STONE_HPP__
# define				__HBS_LOOP_STONE_HPP__
# include				<lapin.h>

namespace				hbs
{
  class					LoopStone
  {
  protected:
    LoopStone(void) {}
    virtual ~LoopStone(void) {}
  };

  template<typename T>
  class					LoopStone : public LoopStone
  {
  private:
    LoopStone				&operator=(const LoopStone		&stone);
    LoopStone(void);

    T					&data;

    virtual t_bunny_response		Key(t_bunny_event_state			state,
					    t_bunny_keysym			sym,
					    T					&data)
    {
      (void)state;
      (void)sym;
      (void)data;
      return (GO_ON);
    }
    virtual t_bunny_response		Text(t_bunny_type			type,
					     T					&data)
    {
      (void)type;
      (void)data;
      return (GO_ON);
    }
    virtual t_bunny_response		Click(t_bunny_event_state		state,
					      t_bunny_mouse_button		button,
					      T					&data)
    {
      (void)state;
      (void)button;
      (void)data;
      return (GO_ON);
    }
    virtual t_bunny_response		Move(const t_bunny_position		&relative,
					     T					&data)
    {
      (void)relative;
      (void)data;
      return (GO_ON);
    }
    virtual t_bunny_response		Wheel(int				wheelid,
					      int				delta,
					      T					&data)
    {
      (void)wheelid;
      (void)delta;
      (void)data;
      return (GO_ON);
    }
    virtual t_bunny_response		StickIn(t_bunny_event_state		state,
						int				joyid,
						const t_bunny_joystick		&info,
						T				&data)
    {
      (void)state;
      (void)joyid;
      (void)info;
      (void)data;
      return (GO_ON);
    }
    virtual t_bunny_response		StickAxis(int				id,
						  t_bunny_axis			axis,
						  float				value,
						  T				&data)
    {
      (void)id;
      (void)axis;
      (void)value;
      (void)data;
      return (GO_ON);
    }
    virtual t_bunny_response		StickButton(t_bunny_event_state		state,
						    int				joyid,
						    int				button,
						    T				&data)
    {
      (void)state;
      (void)joyid;
      (void)button;
      (void)data;
      return (GO_ON);
    }
    virtual t_bunny_response		Focus(t_bunny_event_state		state,
					      const t_bunny_window		&win,
					      T					&data)
    {
      (void)state;
      (void)win;
      (void)data;
      return (GO_ON);
    }
    virtual t_bunny_response		Resize(const t_bunny_window		&win,
					       const t_bunny_position		&siz,
					       T				&data)
    {
      (void)win;
      (void)siz;
      (void)data;
      return (GO_ON);
    }
    virtual t_bunny_response		Close(const t_bunny_window		&win,
					      T					&data)
    {
      (void)win;
      (void)data;
      return (GO_ON);
    }
    virtual t_bunny_response		Loop(T					&data)
    {
      return (GO_ON);
    }
    virtual t_bunny_response		Display(const T				&data)
    {
      return (GO_ON);
    }

    static t_bunny_response		key(t_bunny_event_state			state,
					    t_bunny_keysym			sym,
					    LoopStone				&ptr)
    {
      return (ptr.Key(state, sym, ptr.data));
    }
    static t_bunny_response		text(t_bunny_type			type,
					     LoopStone				&ptr)
    {
      return (ptr.Text(type, ptr.data));
    }
    static t_bunny_response		click(t_bunny_event_state		state,
					      t_bunny_mouse_button		button,
					      LoopStone				&ptr)
    {
      return (ptr.Click(state, button, ptr.data));
    }
    static t_bunny_response		move(const t_bunny_position		*relative,
					     LoopStone				&ptr)
    {
      return (ptr.Move(*relative, ptr.data));
    }
    static t_bunny_response		wheel(int				wheelid,
					      int				delta,
					      LoopStone				&ptr)
    {
      return (ptr.Wheel(wheelid, delta, ptr.data));
    }
    static t_bunny_response		stickin(t_bunny_event_state		state,
						int				joyid,
						const t_bunny_joystick		*info,
						LoopStone			&ptr)
    {
      return (ptr.StickIn(state, joyid, *info, ptr.data));
    }
    static t_bunny_response		stickaxis(int				id,
						  t_bunny_axis			axis,
						  float				value,
						  LoopStone			&ptr)
    {
      return (ptr.StickAxis(id, axis, value, ptr.data));
    }
    static t_bunny_response		stickbutton(t_bunny_event_state		state,
						    int				joyid,
						    int				button,
						    LoopStone			&ptr)
    {
      return (ptr.StickButton(state, joyid, button, ptr.data));
    }
    static t_bunny_response		getfocus(const t_bunny_window		*win,
						 LoopStone			&ptr)
    {
      return (ptr.Focus(GO_UP, *win, ptr.data));
    }
    static t_bunny_response		lostfocus(const t_bunny_window		*win,
						  LoopStone			&ptr)
    {
      return (ptr.Focus(GO_DOWN, *win, ptr.data));
    }
    static t_bunny_response		resize(const t_bunny_window		*win,
					       const t_bunny_position		*siz,
					       LoopStone			&ptr)
    {
      return (ptr.Resize(*win, *siz, ptr.data));
    }
    static t_bunny_response		close(const t_bunny_window		*win,
					      LoopStone				&ptr)
    {
      return (ptr.Close(*win, ptr.data));
    }
    static t_bunny_response		loop(LoopStone				&ptr)
    {
      return (ptr.Loop(ptr.data));
    }
    static t_bunny_response		display(LoopStone			&ptr)
    {
      return (ptr.Display(ptr.data));
    }

    static const t_bunny_context	Context;

  protected:
    bool				GetKeyState(t_bunny_keysym		key) const
    {
      return (bunny_get_keyboard()[key]);
    }
    bool				GetButtonState(t_bunny_mouse_button	button) const
    {
      return (bunny_get_mouse_button()[button]);
    }
    const t_bunny_position		&GetMousePosition(void) const
    {
      return (*bunny_get_mouse_position());
    }
    const t_bunny_joystick		&GetStickInfo(int			id) const
    {
      return (*bunny_get_joy_info(id % LAST_BUNNY_JOYSTICK));
    }
    float				GetStickAxis(int			id,
						     t_bunny_axis		axis) const
    {
      return (bunny_get_joy_axis()[id % LAST_BUNNY_JOYSTICK][axis]);
    }
    bool				GetStickButton(int			id,
						       int			button) const
    {
      return (bunny_get_joy_button()[id % LAST_BUNNY_JOYSTICK][axis]);
    }
    const t_bunny_window		&GetWindow(void) const
    {
      return (*bunny_get_window());
    }

    LoopStone(T				&_data) : data(_data)  {}
    virtual ~LoopStone(void) {}
  };

  t_bunny_response			bunny_loop(t_bunny_window		&win,
						   uint8_t			freq,
						   LoopStone			&ls)
  {
    ::bunny_set_context(&Context);
    return (::bunny_loop(&win, freq, (void*)&ls));
  }
  t_bunny_response			bunny_loop_mw(std::vector<t_bunny_window*> &win,
						      size_t			nwin,
						      uint8_t			freq,
						      LoopStone			&ls)
  {
    t_bunny_window			**ptr = alloca(win.size() * sizeof(*ptr));
    size_t				i;

    for (i = 0; i < win.size(); ++i)
      ptr[i] = &win[i];
    return (::bunny_loop_mw(ptr, nwin, freq, (void*)&ls));
  }
}

const t_bunny_context			hbs::LoopStone::Context =
  {
    (t_bunny_key)hbs::LoopStone::key,
    (t_bunny_type)hbs::LoopStone::text,
    (t_bunny_click)hbs::LoopStone::clic,
    (t_bunny_move)hbs::LoopStone::move,
    (t_bunny_wheel)hbs::LoopStone::wheel,
    (t_bunny_joy_connect)hbs::LoopStone::stickin,
    (t_bunny_joy_button)hbs::LoopStone::stickbutton,
    (t_bunny_joy_axis)hbs::LoopStone::stickaxis,
    (t_bunny_get_focus)hbs::LoopStone::getfocus,
    (t_bunny_lost_focus)hbs::LoopStone::lostfocus,
    (t_bunny_resize)hbs::LoopStone::resize,
    (t_bunny_loop)hbs::LoopStone::loop,
    (t_bunny_display)hbs::LoopStone::display,
    (t_bunny_close)hbs::LoopStone::close    
  };

#endif	//				__HBS_LOOP_STONE_HPP__

