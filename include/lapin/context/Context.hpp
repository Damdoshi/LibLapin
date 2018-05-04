/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2018
**
**
** Bibliotheque Lapin
*/

#ifndef				__LAPIN_CONTEXT_HPP__
# define			__LAPIN_CONTEXT_HPP__

namespace			Bunny
{
  template<typename		SubContext>
  class				Context
  {
  public:
    t_bunny_response		Key(t_bunny_event_state		state,
				    t_bunny_keysym		sym)
    {
      (void)state;
      (void)sym;
      return (GO_ON);
    }
    static t_bunny_response	KeyHook(t_bunny_event_state	state,
					t_bunny_keysym		sym,
					SubContext		*data)
    {
      return (data->Key(state, sym));
    }

    //////////////////////////////////////////////////////////////////////

    t_bunny_response		Text(t_bunny_type		type)
    {
      (void)type;
      return (GO_ON);
    }
    static t_bunny_response	TextHook(t_bunny_type		type,
					 SubContext		*data)
    {
      return (data->Text(type));
    }

    //////////////////////////////////////////////////////////////////////

    t_bunny_response		Click(t_bunny_event_state	state,
				      t_bunny_mouse_button	button)
    {
      (void)state;
      (void)button;
      return (GO_ON);
    }
    static t_bunny_response	ClickHook(t_bunny_event_state	state,
					  t_bunny_mouse_button	button,
					  SubContext		*data)
    {
      return (data->Click(state, button));
    }

    //////////////////////////////////////////////////////////////////////

    t_bunny_response		Move(const t_bunny_position	*relative)
    {
      (void)relative;
      return (GO_ON);
    }
    static t_bunny_response	MoveHook(const t_bunny_position	*relative,
					 SubContext		*data)
    {
      return (data->Move(relative));
    }

    //////////////////////////////////////////////////////////////////////

    t_bunny_response		Wheel(int			wheelid,
				      int			delta)
    {
      (void)wheelid;
      (void)delta;
      return (GO_ON);
    }
    static t_bunny_response	WheelHook(int			wheelid,
					  int			delta,
					  SubContext		*data)
    {
      return (data->Wheel(wheelid, delta));
    }

    //////////////////////////////////////////////////////////////////////

    t_bunny_response		JoyConnect(t_bunny_event_state	state,
					   int			joyid,
					   const t_bunny_joystick *info)
    {
      (void)state;
      (void)joyid;
      (void)info;
      return (GO_ON);
    }
    static t_bunny_response	JoyConnectHook(t_bunny_event_state state,
					       int		joyid,
					       const t_bunny_joystick *info,
					       SubContext	*data)
    {
      return (data->JoyConnect(state, joyid, info));
    }

    //////////////////////////////////////////////////////////////////////

    t_bunny_response		JoyAxis(int			id,
					t_bunny_axis		axis,
					float			value)
    {
      (void)id;
      (void)axis;
      (void)value;
      return (GO_ON);
    }
    static t_bunny_response	JoyAxisHook(int			id,
					    t_bunny_axis	axis,
					    float		value,
					    SubContext		*data)
    {
      return (data->JoyAxis(id, axis, value));
    }

    //////////////////////////////////////////////////////////////////////

    t_bunny_response		JoyButton(t_bunny_event_state	state,
					  int			joyid,
					  int			button)
    {
      (void)state;
      (void)joyid;
      (void)button;
      return (GO_ON);
    }
    static t_bunny_response	JoyButtonHook(t_bunny_event_state state,
					      int		joyid,
					      int		button,
					      SubContext	*data)
    {
      return (data->JoyButton(state, joyid, button));
    }

    //////////////////////////////////////////////////////////////////////

    t_bunny_response		GetFocus(const t_bunny_window	*win)
    {
      (void)win;
      return (GO_ON);
    }
    static t_bunny_response	GetFocusHook(const t_bunny_window *win,
					     SubContext		*data)
    {
      return (data->GetFocus(win));
    }

    //////////////////////////////////////////////////////////////////////

    t_bunny_response		LostFocus(const t_bunny_window	*win)
    {
      (void)win;
      return (GO_ON);
    }
    static t_bunny_response	LostFocusHook(const t_bunny_window *win,
					      SubContext	*data)
    {
      return (data->LostFocus(win));
    }

    //////////////////////////////////////////////////////////////////////

    t_bunny_response		Resize(const t_bunny_window	*win,
				       const t_bunny_position	*size)
    {
      (void)win;
      (void)size;
      return (GO_ON);
    }
    static t_bunny_response	ResizeHook(const t_bunny_window	*win,
					   const t_bunny_position *size,
					   SubContext		*data)
    {
      return (data->Resize(win, size));
    }

    //////////////////////////////////////////////////////////////////////

    t_bunny_response		Close(const t_bunny_window	*win)
    {
      (void)win;
      return (GO_ON);
    }
    static t_bunny_response	CloseHook(const t_bunny_window	*win,
					  SubContext		*data)
    {
      return (data->Close(win));
    }

    //////////////////////////////////////////////////////////////////////

    t_bunny_response		Loop(void)
    {
      return (GO_ON);
    }
    static t_bunny_response	LoopHook(SubContext		*data)
    {
      return (data->Loop());
    }

    //////////////////////////////////////////////////////////////////////

    t_bunny_response		Display(void)
    {
      return (GO_ON);
    }
    static t_bunny_response	DisplayHook(SubContext		*data)
    {
      return (data->Display());
    }

    //////////////////////////////////////////////////////////////////////

    virtual t_bunny_network	*Netcom(void)
    {
      return (NULL);
    }

    //////////////////////////////////////////////////////////////////////

    t_bunny_response		NetMessage(int			fd,
					   const void		*buffer,
					   size_t		bufsize)
    {
      (void)fd;
      (void)buffer;
      (void)bufsize;
      return (GO_ON);
    }
    static t_bunny_response	NetMessageHook(int		fd,
					       const void	*buffer,
					       size_t		bufsize,
					       SubContext	*data)
    {
      return (data->NetMessage(fd, buffer, bufsize));
    }

    //////////////////////////////////////////////////////////////////////

    t_bunny_response		NetConnect(int			fd,
					   t_bunny_event_state	state)
    {
      (void)fd;
      (void)state;
      return (GO_ON);
    }
    static t_bunny_response	NetConnectHook(int		fd,
					       t_bunny_event_state state,
					       SubContext	*data)
    {
      return (data->NetConnect(fd, state));
    }

    //////////////////////////////////////////////////////////////////////

    t_bunny_response		Entering(void)
    {
      return (GO_ON);
    }
    static t_bunny_response	EnteringHook(SubContext		*data)
    {
      return (data->Entering());
    }

    //////////////////////////////////////////////////////////////////////

    void			Leaving(t_bunny_response	return_value)
    {
      (void)return_value;
    }
    static void			LeavingHook(t_bunny_response	return_value,
					    SubContext		*data)
    {
      return (data->Leaving(return_value));
    }

    //////////////////////////////////////////////////////////////////////

    t_bunny_response		AsyncComputation(void		*computed_val)
    {
      (void)computed_val;
      return (GO_ON);
    }
    static t_bunny_response	AsyncComputationHook(void	*computed_val,
						     SubContext	*data)
    {
      return (data->AsyncComputation(computed_val));
    }

    //////////////////////////////////////////////////////////////////////

    Context(void) {}
    virtual ~Context(void) {}
  };

  template <typename T> // Ultimate cast
  void				*UC(const T		&v)
  {
    union {
      const T	*t;
      void *v;
    } x;

    x.t = &v;
    return (x.v);
  }

# define			_TAS(d, o)		\
  if (&T::o != &Bunny::Context<T>::o) {			\
    out.d = UC(T::o ## Hook);				\
  } else {						\
    out.d = NULL;					\
  }

  template <typename T>
  void				SetContext(const T	&inctx)
  {
    t_bunny_anonymous_context	out;

    (void)inctx;
    _TAS(key, Key);
    _TAS(type, Text);
    _TAS(click, Click);
    _TAS(move, Move);
    _TAS(wheel, Wheel);
    _TAS(connect, JoyConnect);
    _TAS(button, JoyButton);
    _TAS(axis, JoyAxis);
    _TAS(get_focus, GetFocus);
    _TAS(lost_focus, LostFocus);
    _TAS(resize, Resize);
    _TAS(loop, Loop);
    _TAS(display, Display);
    _TAS(close, Close);
    out.netcom = (void*)const_cast<T&>(inctx).Netcom();
    _TAS(netmessage, NetMessage);
    _TAS(netconnect, NetConnect);
    _TAS(entering_context, Entering);
    _TAS(leaving_context, Leaving);
    _TAS(async_computation_response, AsyncComputation);
    bunny_set_context((t_bunny_context*)&out);
  }

# undef				_TAS
}

#endif	/*			__LAPIN_CONTEXT_HPP__		*/
