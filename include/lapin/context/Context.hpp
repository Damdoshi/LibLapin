// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
// EFRITS SAS 2022-2025
// Pentacle Technologie 2008-2025
//
// Not Alone

#ifndef				__CONTEXT_HPP__
# define			__CONTEXT_HPP__
# include			<lapin.h>
# include			<span>

namespace			hbs
{
  class				Context : public t_bunny_context
  {
  protected:
    Context(void)
    {
      memset(static_cast<t_bunny_context*>(this), 0, sizeof(t_bunny_context));
    }

  public:
    virtual t_bunny_response	Key(t_bunny_event_state		state,
				    t_bunny_keysym		sym) = 0;
    virtual t_bunny_response	Type(uint32_t			unicode) = 0;
    virtual t_bunny_response	Click(t_bunny_event_state	state,
				      t_bunny_mouse_button	but) = 0;
    virtual t_bunny_response	Move(const t_bunny_position	&rel) = 0;
    virtual t_bunny_response	Wheel(int			wid,
				      int			delta) = 0;
    virtual t_bunny_response	Connect(t_bunny_event_state	state,
					int			jid,
					const t_bunny_joystick	&jinfo) = 0;
    virtual t_bunny_response	Button(t_bunny_event_state	state,
				       int			jid,
				       int			button) = 0;
    virtual t_bunny_response	Axis(int			jid,
				     t_bunny_axis		axis,
				     float			value) = 0;
    virtual t_bunny_response	GetFocus(const t_bunny_window	&win) = 0;
    virtual t_bunny_response	LostFocus(const t_bunny_window	&win) = 0;
    virtual t_bunny_response	Resize(const t_bunny_window	&win,
				       const t_bunny_position	&siz) = 0;
    virtual t_bunny_response	Loop(void) = 0;
    virtual t_bunny_response	Display(void) = 0;
    virtual t_bunny_response	Close(const t_bunny_window	&win) = 0;
    virtual t_bunny_response	NetMessage(t_bunny_network_info	clt,
					   std::span<std::byte>	tmp) = 0;
    virtual t_bunny_response	NetConnect(t_bunny_network_info	clt,
					   t_bunny_event_state	state) = 0;
    virtual t_bunny_response	EnteringContext(void) = 0;
    virtual void		LeavingContext(t_bunny_response	ret) = 0;
    virtual t_bunny_response	AsyncComputation(void		*cmd) = 0;
    virtual t_bunny_response	Event(const t_bunny_event	&event) = 0;
    virtual ~Context(void) {}
  };

  template <typename		T>
  class				ContextBridge : public Context
  {
  private:
    static t_bunny_response	KeyF(t_bunny_event_state	state,
				     t_bunny_keysym		sym,
				     T				*data)
    {
      return (data->Key(state, sym));
    }
  public:
    virtual t_bunny_response	Key(t_bunny_event_state		state,
				    t_bunny_keysym		sym) override
    {
      (void)state; (void)sym;
      this->key = NULL;
      bunny_set_context(this);
      return (GO_ON);
    }

  private:
    static t_bunny_response	TypeF(uint32_t			unicode,
				      T				*data)
    {
      return (data->Type(unicode));
    }
  public:
    virtual t_bunny_response	Type(uint32_t			unicode) override
    {
      (void)unicode;
      this->type = NULL;
      bunny_set_context(this);
      return (GO_ON);
    }

  private:
    static t_bunny_response	ClickF(t_bunny_event_state	state,
				       t_bunny_mouse_button	but,
				       T			*data)
    {
      return (data->Click(state, but));
    }
  public:
    virtual t_bunny_response	Click(t_bunny_event_state	state,
				      t_bunny_mouse_button	but) override
    {
      (void)state; (void)but;
      this->click = NULL;
      bunny_set_context(this);
      return (GO_ON);
    }

  private:
    static t_bunny_response	MoveF(const t_bunny_position	*rel,
				      T				*data)
    {
      return (data->Move(*rel));
    }
  public:
    virtual t_bunny_response	Move(const t_bunny_position	&rel) override
    {
      (void)rel;
      this->move = NULL;
      bunny_set_context(this);
      return (GO_ON);
    }

  private:
    static t_bunny_response	WheelF(int			wid,
				       int			delta,
				       T			*data)
    {
      return (data->Wheel(wid, delta));
    }
  public:
    virtual t_bunny_response	Wheel(int			wid,
				      int			delta) override
    {
      (void)wid; (void)delta;
      this->wheel = NULL;
      bunny_set_context(this);
      return (GO_ON);
    }

  private:
    static t_bunny_response	ConnectF(t_bunny_event_state	state,
					 int			joyid,
					 const t_bunny_joystick	*jinfo,
					 T			*data)
    {
      return (data->Connect(state, joyid, *jinfo));
    }
  public:
    virtual t_bunny_response	Connect(t_bunny_event_state	state,
					int			jid,
					const t_bunny_joystick	&jinfo) override
    {
      (void)state; (void)jid; (void)jinfo;
      this->joy_connect = NULL;
      bunny_set_context(this);
      return (GO_ON);
    }

  private:
    static t_bunny_response	ButtonF(t_bunny_event_state	state,
					int			jid,
					int			button,
					T			*data)
    {
      return (data->Button(state, jid, button));
    }
  public:
    virtual t_bunny_response	Button(t_bunny_event_state	state,
				       int			jid,
				       int			button) override
    {
      (void)state; (void)jid; (void)button;
      this->joy_button = NULL;
      bunny_set_context(this);
      return (GO_ON);
    }

  private:
    static t_bunny_response	AxisF(int			jid,
				      t_bunny_axis		axis,
				      float			value,
				      T				*data)
    {
      return (data->Axis(jid, axis, value));
    }
  public:
    virtual t_bunny_response	Axis(int			jid,
				     t_bunny_axis		axis,
				     float			value) override
    {
      (void)jid; (void)axis; (void)value;
      this->joy_axis = NULL;
      bunny_set_context(this);
      return (GO_ON);
    }

  private:
    static t_bunny_response	GetFocusF(const t_bunny_window	*win,
					  T			*data)
    {
      return (data->GetFocus(*win));
    }
  public:
    virtual t_bunny_response	GetFocus(const t_bunny_window	&win) override
    {
      (void)win;
      this->get_focus = NULL;
      bunny_set_context(this);
      return (GO_ON);
    }

  private:
    static t_bunny_response	LostFocusF(const t_bunny_window	*win,
					   T			*data)
    {
      return (data->LostFocus(*win));
    }
  public:
    virtual t_bunny_response	LostFocus(const t_bunny_window	&win) override
    {
      (void)win;
      this->lost_focus = NULL;
      bunny_set_context(this);
      return (GO_ON);
    }

  private:
    static t_bunny_response	ResizeF(const t_bunny_window	*win,
					const t_bunny_position	*siz,
					T			*data)
    {
      return (data->Resize(*win, *siz));
    }
  public:
    virtual t_bunny_response	Resize(const t_bunny_window	&win,
				       const t_bunny_position	&siz) override
    {
      (void)win; (void)siz;
      this->resize = NULL;
      bunny_set_context(this);
      return (GO_ON);
    }

  private:
    static t_bunny_response	LoopF(T				*data)
    {
      return (data->Loop());
    }
  public:
    virtual t_bunny_response	Loop(void) override
    {
      this->loop = NULL;
      bunny_set_context(this);
      return (GO_ON);
    }

  private:
    static t_bunny_response	DisplayF(T			*data)
    {
      return (data->Display());
    }
  public:
    virtual t_bunny_response	Display(void) override
    {
      this->display = NULL;
      bunny_set_context(this);
      return (GO_ON);
    }

  private:
    static t_bunny_response	CloseF(const t_bunny_window	*win,
				       T			*data)
    {
      return (data->Close(*win));
    }
  public:
    virtual t_bunny_response	Close(const t_bunny_window	&win) override
    {
      (void)win;
      this->close = NULL;
      bunny_set_context(this);
      return (GO_ON);
    }

  private:
    static t_bunny_response	NetMessageF(t_bunny_network_info clt,
					    void		*buffer,
					    size_t		size,
					    T			*data)
    {
      return (data->NetMessage(clt, std::span<std::byte>{(std::byte*)buffer, size}));
    }
  public:
    virtual t_bunny_response	NetMessage(t_bunny_network_info	clt,
					   std::span<std::byte>	tmp) override
    {
      (void)clt; (void)tmp;
      this->net_message = NULL;
      bunny_set_context(this);
      return (GO_ON);
    }

  private:
    static t_bunny_response	NetConnectF(t_bunny_network_info clt,
					    t_bunny_event_state	state,
					    T			*data)
    {
      return (data->NetConnect(clt, state));
    }
  public:
    virtual t_bunny_response	NetConnect(t_bunny_network_info	clt,
					   t_bunny_event_state	state) override
    {
      (void)clt; (void)state;
      this->net_connect = NULL;
      bunny_set_context(this);
      return (GO_ON);
    }

  private:
    static t_bunny_response	EnteringContextF(T		*data)
    {
      return (data->EnteringContext());
    }
  public:
    virtual t_bunny_response	EnteringContext(void) override
    {
      this->entering_context = NULL;
      bunny_set_context(this);
      return (GO_ON);
    }

  private:
    static void			LeavingContextF(t_bunny_response ret,
						T		*data)
    {
      return (data->LeavingContext(ret));
    }
  public:
    virtual void		LeavingContext(t_bunny_response	ret) override
    {
      (void)ret;
      this->leaving_context = NULL;
      bunny_set_context(this);
    }

  private:
    static t_bunny_response	AsyncComputationF(void		*cmd,
						  T		*data)
    {
      return (data->AsyncComputation(cmd));
    }
  public:
    virtual t_bunny_response	AsyncComputation(void		*cmd) override
    {
      (void)cmd;
      this->async_computation = NULL;
      bunny_set_context(this);
      return (GO_ON);
    }

  private:
    static t_bunny_response	EventF(const t_bunny_event	*event,
				       T			*data)
    {
      return (data->Event(*event));
    }
  public:
    virtual t_bunny_response	Event(const t_bunny_event	&event) override
    {
      (void)event;
      this->event = NULL;
      return (GO_ON);
    }	
    
  public:
    ContextBridge(void)
    {
      key = (t_bunny_key)KeyF;
      type = (t_bunny_type)TypeF;
      click = (t_bunny_click)ClickF;
      move = (t_bunny_move)MoveF;
      wheel = (t_bunny_wheel)WheelF;
      joy_connect = (t_bunny_joy_connect)ConnectF;
      joy_button = (t_bunny_joy_button)ButtonF;
      joy_axis = (t_bunny_joy_axis)AxisF;
      get_focus = (t_bunny_get_focus)GetFocusF;
      lost_focus = (t_bunny_lost_focus)LostFocusF;
      resize = (t_bunny_resize)ResizeF;
      loop = (t_bunny_loop)LoopF;
      display = (t_bunny_display)DisplayF;
      close = (t_bunny_close)CloseF;
      net_message = (t_bunny_message_response)NetMessageF;
      net_connect = (t_bunny_connect_response)NetConnectF;
      entering_context = (t_bunny_loop)EnteringContextF;
      leaving_context = (t_bunny_leaving_context)LeavingContextF;
      async_computation = (t_bunny_async_computation_response)AsyncComputationF;
      event = (t_bunny_event_response)EventF;
    }
    ContextBridge(t_bunny_context const &ctx)
    {
      *static_cast<t_bunny_context*>(this) = ctx;
    }
    virtual ~ContextBridge(void) {}
  };
}

#endif	//			__CONTEXT_HPP__
