/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Bibliotheque Lapin
*/

/*!
** \file events.h
** The events module allow you to handle user actions: keyboard, joystick, mouse, etc.
** The bunny library is callback driven. You have to define functions that will
** be called if a specific category of event occurs.
*/

#ifndef				__LAPIN_EVENTS_H__
# define			__LAPIN_EVENTS_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif

/*!
** The t_bunny_response enumeration contains values that can be returned from
** a callback used by the event handling system. The value, under some specific
** conditions, can be returned by the bunny_loop function and the bunny_loop_mw
** function.
** Returning EXIT_ON_ERROR break the bunny_loop, making it returns EXIT_ON_ERROR
** Returning EXIT_ON_CROSS should not be used: it is used by the window closing mecanism
** Returning EXIT_ON_SUCCESS break the bunny_loop, making it returns EXIT_ON_SUCCESS
** Returning SWITCH_CONTEXT break the bunny_loop, making it returns SWITCH_CONTEXT
** Returning GO_ON does not break the bunny_loop, it simply goes on.
*/
typedef enum			e_bunny_response
  {
    EXIT_ON_ERROR,
    EXIT_ON_CROSS,
    EXIT_ON_SUCCESS,
    SWITCH_CONTEXT,
    GO_ON
  }				t_bunny_response;

/*!
** Most events are linked to a specific action: something was pressed or released.
** The t_bunny_event_state enumeration handle this. GO_DOWN means something was pressed.
** GO_UP means something was released. CONNECTED and DISCONNECTED are equivalent, but
** more clear when you write something like joystick connection/disconnection routine
*/
typedef enum			e_bunny_event_state
  {
    GO_DOWN,
    GO_UP,
    CONNECTED			= GO_DOWN,
    DISCONNECTED		= GO_UP
  }				t_bunny_event_state;

/*!
** The type of the function that will handle keyboard event.
** t_bunny_event_state is the action: the key was pressed or released.
** t_bunny_keysym is the key that was pressed or released. See enum.h for more informations.
** The void* pointer can be anything: it is what you sent to bunny_loop or bunny_loop_mw
** as last parameter.
** Return a t_bunny_response in order to keep the loop or break it.
*/
typedef t_bunny_response	(*t_bunny_key)(t_bunny_event_state		sta,
					       t_bunny_keysym			sym,
					       void				*dat);

/*!
** Register the sent function in order to call it when a keyboard event occurs.
** \param key The function to call
*/
void				bunny_set_key_response(t_bunny_key		key);

/*!
** Get the array of keyboard states. bunny_get_keyboard()[KEYSYM] returns if the KEYSYM
** key is up (false) or down (true). The array of keyboard states is updated ONLY
** if a callback was registered for the keyboard with the bunny_set_key_response function.
*/
const bool			*bunny_get_keyboard(void);

/*!
** The type of the function that will handle the keyboard typing event.
** There is a difference with the keyboard pressed or released event: here, we are talking
** about text, that means that keys like shift or alt are working automatically and
** that special characters may be managed.
** The uint32_t unicode is the character that was typed.
** The void* pointer can be anything: it is what you sent to bunny_loop or bunny_loop_mw
** as last parameter.
** Return a t_bunny_response in order to keep the loop or break it.
*/
typedef t_bunny_response	(*t_bunny_type)(uint32_t			unicode,
						void				*data);

/*!
** Register the sent function in order to call it when a type event occurs.
** \param type The function to call
*/
void				bunny_set_text_response(t_bunny_type		type);

/*!
** The type of the function that will handle mouse click event.
** t_bunny_event_state is the action: the button was pressed or released.
** t_bunny_mouse_button is the button that was pressed or released. See enum.h for more informations.
** The void* pointer can be anything: it is what you sent to bunny_loop or bunny_loop_mw
** as last parameter.
** Return a t_bunny_response in order to keep the loop or break it.
*/
typedef t_bunny_response	(*t_bunny_click)(t_bunny_event_state		sta,
						 t_bunny_mouse_button		but,
						 void				*dat);

/*!
** Register the sent function in order to call it when a mouse blick event occurs.
** \param cli The function to call
*/
void				bunny_set_click_response(t_bunny_click		cli);

/*!
** Get the array of mouse button states. bunny_get_mouse_button()[BUTTONID] returns if
** the button is up (false) or down (true). The array of mouse button is updated ONLY
** if a callback was registered for the mouse click with the bunny_set_click_response function.
*/
const bool			*bunny_get_mouse_button(void);

/*!
** The type of the function that will handle mouse movement event.
** t_bunny_position is the difference between the cursor now and previously.
** The void* pointer can be anything: it is what you sent to bunny_loop or bunny_loop_mw
** as last parameter.
** Return a t_bunny_response in order to keep the loop or break it.
*/
typedef t_bunny_response	(*t_bunny_move)(const t_bunny_position		*relative,
						void				*dat);

/*!
** Register the sent function in order to call it when a mouse movement event occurs.
** \param mov The function to call
*/
void				bunny_set_move_response(t_bunny_move		mov);

/*!
** Get the mouse position. The mouse position structure is updated ONLY if a callback
** was registered for the mouse movement event with the bunny_set_move_response function.
*/
const t_bunny_position		*bunny_get_mouse_position(void);

/*!
** The type of the function that will handle mouse wheel event.
** wheelid is the id of the wheel that was moved.
** delta is how much the wheel moved
** The void* pointer can be anything: it is what you sent to bunny_loop or bunny_loop_mw
** as last parameter.
** Return a t_bunny_response in order to keep the loop or break it.
*/
typedef t_bunny_response	(*t_bunny_wheel)(int				wheelid,
						 int				delta,
						 void				*data);

/*!
** Register the sent function in order to call it when a mouse wheel event occurs.
** \param wheel The function to call
*/
void				bunny_set_wheel_response(t_bunny_wheel		wheel);

/*!
** The t_bunny_joystick structure contains all informations about a joystick slot.
** The connected attribute indicates if the slot is used.
** The name attribute is the name of the joystick
** The vendor attribute is the ID of the vendor
** The product attribute is the ID of the product.
** The nb_button attribute is how many buttons there is
** The axis attribute is how many axis there is: horizontal, vertical, etc.
** See the enum.h file for more informations.
*/
typedef struct			s_bunny_joystick
{
  bool				connected;
  const char			*name;
  unsigned int			vendor;
  unsigned int			product;
  unsigned int			nb_button;
  unsigned char			axis;
}				t_bunny_joystick;

/*!
** The type of the function that will handle joystick connection and disconnection.
** t_bunny_event_state is the action: connected or disconnected
** joyid is the id of the joystick. The LibLapin supports LAST_BUNNY_JOYSTICK joysticks.
** t_bunny_joystick contains information about the connected or disconnected joystick.
** The void* pointer can be anything: it is what you sent to bunny_loop or bunny_loop_mw
** as last parameter.
** Return a t_bunny_response in order to keep the loop or break it.
*/
typedef t_bunny_response	(*t_bunny_joy_connect)(t_bunny_event_state	state,
						       int			joyid,
						       const t_bunny_joystick	*joyinfo,
						       void			*data);
/*!
** Register the sent function in order to call it when a joystick connection event occurs.
** \param joy The function to call
*/
void				bunny_set_joy_connect_response(t_bunny_joy_connect joy);

/*!
** Get informations about a specific joystick.
** \param id The id of the joystick you wanna get the info
** \return A pointer to the informations of the requested joystick. NULL if id was invalid.
*/
const t_bunny_joystick		*bunny_get_joy_info(int				id);

/*!
** The tpye of the function that will handle any changing on a joystick axis.
** joyid is the id of the joystick that got a changing axis
** t_bunny_axis is the axis that changed
** value is the new value of the axis
** The void* pointer can be anything: it is what you sent to bunny_loop or bunny_loop_mw
** as last parameter.
** Return a t_bunny_response in order to keep the loop or break it.
*/
typedef t_bunny_response	(*t_bunny_joy_axis)(int				joyid,
						    t_bunny_axis		axis,
						    float			value,
						    void			*data);

/*!
** Register the sent function in order to call it when a joystick axis event occurs.
** \param axis The function to call.
*/
void				bunny_set_joy_axis_response(t_bunny_joy_axis	axis);

/*!
** Get an array of array of axis. The first dimension is the joystick, the second
** is the axis. The axis value array is updated ONLY if a callback was registered for the
** joystick axis event with the bunny_set_joy_axis_response function.
** The maximum joystick value is LAPIN_BUNNY_JOYSTICK and the maximum value for axis is
** LAST_BUNNY_AXIS.
** Use it this way: bunny_get_joy_axis()[3][4]
*/
const float			(*bunny_get_joy_axis(void))[LAST_BUNNY_AXIS];

/*!
** The type of the function that will handle joystick button event.
** t_bunny_event_state is the action: the button was pressed or release.
** joyid is the id of the joystick that got a changing button
** button is the number of the changing button
** The void* pointer can be anything: it is what you sent to bunny_loop or bunny_loop_mw
** as last parameter
** Return a t_bunny_response in order to keep the loop or break it.
*/
typedef t_bunny_response	(*t_bunny_joy_button)(t_bunny_event_state	state,
						      int			joyid,
						      int			button,
						      void			*data);

/*!
** Register the sent function in order to call it when a joystick button event occurs.
** \param button The function to call.
*/
void				bunny_set_joy_button_response(t_bunny_joy_button button);

/*!
** Get an array of array of buttons. The first dimension is the joystick, the second
** is the button. The button value array is updated ONLY if a callback was registered
** for the joystick button event with the bunny_set_joy_button_response function.
** The maximum joystick value is LAPIN_BUNNY_JOYSTICK and the maximum value for buttons
** is LAST_BUNNY_BUTTON.
** Use it this way: bunny_get_joy_button()[3][4]
*/
const bool			(*bunny_get_joy_button(void))[LAST_BUNNY_BUTTON];

/*!
** The type of the function that will handle the get focus event.
** t_bunny_window is the address of the window that got the focus
** The void* pointer can be anything: it is what you sent to bunny_loop or bunny_loop_mw
** as last_parameter
** Return a t_bunny_response in order to keep the loop or break it.
*/
typedef t_bunny_response	(*t_bunny_get_focus)(const t_bunny_window	*win,
						     void			*data);

/*!
** Register the sent function in order to call it when a get focus event occurs.
** \param getf The function to call
*/
void				bunny_set_get_focus_response(t_bunny_get_focus	getf);

/*!
** The type of the function that will handle the lost focus event.
** t_bunny_window is the address of the window that lost the focus
** The void* pointer can be anything: it is what you sent to bunny_loop or bunny_loop_mw
** as last_parameter
** Return a t_bunny_response in order to keep the loop or break it.
*/
typedef t_bunny_response	(*t_bunny_lost_focus)(const t_bunny_window	*win,
						      void			*data);

/*!
** Register the sent function in order to call it when a lost focus event occurs.
** \param getf The function to call
*/
void				bunny_set_lost_focus_response(t_bunny_lost_focus lost);

/*!
** The type of the function that will handle the resize window event.
** t_bunny_window is the address of the window that was resize
** t_bunny_position the new size of the window
** The void* pointer can be anything: it is what you sent to bunny_loop or bunny_loop_mw
** as last_parameter
** Return a t_bunny_response in order to keep the loop or break it.
*/
typedef t_bunny_response	(*t_bunny_resize)(const t_bunny_window		*win,
						  const t_bunny_position	*siz,
						  void				*data);

/*!
** Register the sent function in order to call it when a window resize event occurs.
** \param getf The function to call
*/
void				bunny_set_resize_response(t_bunny_resize	resize);

/*!
** The type of the function that will handle the close window event.
** This function type can only be used if you use bunny_loow_mw as real-time loop.
** The sent window is the one that was requested to close.
** The void* pointer can be anything, it is what you sent to bunny_loop_mw as last
** parameter.
** Return a t_bunny_response in order to keep the loop or break it. EXIT_ON_CROSS
** may be a nice choice for this case.
*/
typedef t_bunny_response	(*t_bunny_close)(const t_bunny_window		*win,
						 void				*data);

/*!
** Register the sent function in order to call it when a window close event occurs.
** \param close The function to call
*/
void				bunny_set_close_response(t_bunny_close		close);

/*!
** Get a pointer to the window that handle the current event
** Call this function only in an event manager function, not in the loop main function
** or the display function.
** \param The window that handle the current event
*/
const t_bunny_window	       *bunny_get_window(void);

/*!
** The type of the function that will be called if at least one call to the loop main
** function was made during the last refresh cycle. The void* pointer can be anything:
** it is what you sent to bunny_loop or bunny_loop_mw as last parameter.
** Return a t_bunny_response in order to keep the loop or break it.
*/
typedef t_bunny_response	(*t_bunny_display)(const void			*data);

/*!
** Register the sent function in order to call it under certain circumstances.
** \param display The function to call.
*/
void				bunny_set_display_function(t_bunny_display	display);

/*!
** The type of the function that will be called at a specific frequency, specified thanks
** to the second parameter of bunny_loop or the third of bunny_loop_mw.
** This is useful to create a "main function".
** The void* pointer can be anything: it is what you sent to bunny_loop or bunny_loop_mw
** as last parameter.
** Return a t_bunny_response in order to keep the loop or break it.
*/
typedef t_bunny_response	(*t_bunny_loop)(void				*dat);

/*!
** Register the sent function in order to call it at the given frequency (throught the
** second parameter of bunny_loop or the third one of bunny_loop_mw).
** \param lop The function to call
*/
void				bunny_set_loop_main_function(t_bunny_loop	lop);

/*!
** The bunny_loop function is a real-time loop that also manage events previously registered
** thanks to bunny_set_*_response. The function that have been given to bunny_set_loop_main_function
** is garantee to be called freq time per seconds on average: if a treatment takes more
** time and that the frequency cannot be respected on a specific cycle, then the loop
** will catch up the missing frames on the next cycle.
** For this reason, you must when you use the bunny library take care to NEVER ask
** too much CPU or a too high frequency, making the loop always late: it would try to catch
** up its late and looping at high speed on a following treatment that would not need so
** much CPU.
** The display function is called at best one time after each call to the main function,
** but if several calls were made to the main function because of a slow down, then display
** would be called only once.
** \param win The window that is the source of events
** \param freq How many times the main function will be called per seconds
** \param dat A pointer that will be sent to ALL functions given to callbacks setters.
** \return A value returned by any callback, which cannot be GO_ON.
*/
t_bunny_response		bunny_loop(t_bunny_window			*win,
					   uint8_t				freq,
					   void					*dat);

/*!
** The bunny_loop_mw function is a real-time loop that also manage events previously registered
** thanks to bunny_set_*_response. The function that have been given to bunny_set_loop_main_function
** is garantee to be called freq time per seconds on average: if a treatment takes more
** time and that the frequency cannot be respected on a specific cycle, then the loop
** will catch up the missing frames on the next cycle.
** For this reason, you must when you use the bunny library take care to NEVER ask
** too much CPU or a too high frequency, making the loop always late: it would try to catch
** up its late and looping at high speed on a following treatment that would not need so
** much CPU.
** The display function is called at best one time after each call to the main function,
** but if several calls were made to the main function because of a slow down, then display
** would be called only once.
** This function is exactly the same as bunny_loop but can manage several window. The
** window management is only made on events: loop and display functions are still unique.
** \param win An array of pointer to window
** \param nwin The length of the array of pointer to window
** \param freq How many times the main function will be called per seconds
** \param dat A pointer that will be sent to ALL functions given to callbacks setters.
** \return A value returned by any callback, which cannot be GO_ON.
*/
t_bunny_response		bunny_loop_mw(t_bunny_window			**win,
					      size_t				nwin,
					      uint8_t				freq,
					      void				*data);

/*!
** The t_bunny_context structure is a collection of function pointer of various types.
** These types match all function pointer that can be sent with bunny_set_*_response,
** buny_set_loop_main_function or bunny_set_display_function.
** This structure is made to define a lot of callbacks in a single call, by defining
** a t_bunny_context somewhere (or an array...) and give it to bunny_set_context.
**
** A NULL pointer is a deactivated callback.
*/
typedef struct			s_bunny_context
{
  t_bunny_key			key;
  t_bunny_type			type;
  t_bunny_click			click;
  t_bunny_move			move;
  t_bunny_wheel			wheel;
  t_bunny_joy_connect		connect;
  t_bunny_joy_button		button;
  t_bunny_joy_axis		axis;
  t_bunny_get_focus		get_focus;
  t_bunny_lost_focus		lost_focus;
  t_bunny_resize		resize;
  t_bunny_loop			loop;
  t_bunny_display		display;
  t_bunny_close			close;
}				t_bunny_context;

/*!
** The t_bunny_anonymous_context serves the same purpose as t_bunny_context but
** present a tiny advantage: because all types like t_bunny_key takes a void*,
** your callbacks must all takes a void*, or you have to cast their types into
** a t_bunny_key to set it. In order to allow you to define a more precise type
** than void* for the data that is set to all callbacks, there is this structure.
**
** By using void* instead of function pointer, you can freely assign your function
** pointers to it, even if the last parameter of them is not a void* but a t_game*
** for example. This, without a cast.
**
** Of course it breaks the type safety, but at least, you are free to choose.
*/
typedef struct			s_bunny_anonymous_context
{
  void				*key;
  void				*type;
  void				*click;
  void				*move;
  void				*wheel;
  void				*connect;
  void				*button;
  void				*axis;
  void				*get_focus;
  void				*lost_focus;
  void				*resize;
  void				*loop;
  void				*display;
  void				*close;
}				t_bunny_anonymous_context;

/*!
** Set the event context.
** \param context The event context.
*/
void				bunny_set_context(const t_bunny_context		*context);

/*!
** Get the event context.
** \param context The event context.
*/
void				bunny_get_context(t_bunny_context		*context);

#endif	/*			__LAPIN_EVENTS_H__	*/

