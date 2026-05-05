/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2020
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
/**
 * @doc-symbol t_bunny_response
 * @doc-module events
 * @doc-kind type
 * @doc-order 10
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Enumerates the actions a callback can request from the event loop.
 * @description Every event callback returns a t_bunny_response. GO_ON keeps the loop running; most other values stop the current loop and are returned to the caller.
 * @param EXIT_ON_ERROR Stop the loop because an error happened.
 * @param EXIT_ON_CROSS Stop the loop because the window close button was used.
 * @param EXIT_ON_SUCCESS Stop the loop successfully.
 * @param SWITCH_CONTEXT Stop the loop so the caller can select another context.
 * @param SWITCH_WINDOW Stop the loop so the caller can select another window set.
 * @param GO_ON Continue the current loop.
 * @param LEAVE_EVENT Leave the current event handling chain without stopping the loop.
 * @param NOTHING_HAPPENED Report that no callback did useful work.
 * @see bunny_loop, bunny_loop_mw, t_bunny_context
 *
 * @doc-lang fr
 * @brief Énumère les actions qu'un callback peut demander à la boucle d'événements.
 * @description Chaque callback d'événement renvoie un t_bunny_response. GO_ON laisse la boucle continuer ; la plupart des autres valeurs arrêtent la boucle courante et sont renvoyées à l'appelant.
 * @param EXIT_ON_ERROR Arrête la boucle parce qu'une erreur est survenue.
 * @param EXIT_ON_CROSS Arrête la boucle parce que le bouton de fermeture de la fenêtre a été utilisé.
 * @param EXIT_ON_SUCCESS Arrête la boucle avec succès.
 * @param SWITCH_CONTEXT Arrête la boucle pour que l'appelant puisse choisir un autre contexte.
 * @param SWITCH_WINDOW Arrête la boucle pour que l'appelant puisse choisir un autre ensemble de fenêtres.
 * @param GO_ON Continue la boucle courante.
 * @param LEAVE_EVENT Quitte la chaîne de traitement de l'événement courant sans arrêter la boucle.
 * @param NOTHING_HAPPENED Indique qu'aucun callback n'a effectué de travail utile.
 * @see bunny_loop, bunny_loop_mw, t_bunny_context
 */
typedef enum			e_bunny_response
  {
    EXIT_ON_ERROR,
    EXIT_ON_CROSS,
    EXIT_ON_SUCCESS,
    SWITCH_CONTEXT,
    SWITCH_WINDOW,
    GO_ON,
    LEAVE_EVENT,
    NOTHING_HAPPENED
  }				t_bunny_response;

/*!
** Most events are linked to a specific action: something was pressed or released.
** The t_bunny_event_state enumeration handle this. GO_DOWN means something was pressed.
** GO_UP means something was released. CONNECTED and DISCONNECTED are equivalent, but
** more clear when you write something like joystick connection/disconnection routine
*/
/**
 * @doc-symbol t_bunny_event_state
 * @doc-module events
 * @doc-kind type
 * @doc-order 20
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Describes whether an event starts or ends.
 * @description GO_DOWN and GO_UP are the generic names. The other symbols are aliases used to make focus, joystick connection and context transitions easier to read.
 * @param GO_DOWN A key or button was pressed.
 * @param GO_UP A key or button was released.
 * @param LOST_FOCUS Alias of GO_DOWN for a focus-lost event.
 * @param GOT_FOCUS Alias of GO_UP for a focus-gained event.
 * @param CONNECTED Alias of GO_DOWN for a connection event.
 * @param DISCONNECTED Alias of GO_UP for a disconnection event.
 * @param ENTERING Alias of GO_DOWN for entering a context.
 * @param LEAVING Alias of GO_UP for leaving a context.
 * @see t_bunny_key, t_bunny_click, t_bunny_joy_connect
 *
 * @doc-lang fr
 * @brief Décrit si un événement commence ou se termine.
 * @description GO_DOWN et GO_UP sont les noms génériques. Les autres symboles sont des alias utilisés pour rendre plus lisibles les événements de focus, de connexion de joystick et de transition de contexte.
 * @param GO_DOWN Une touche ou un bouton a été enfoncé.
 * @param GO_UP Une touche ou un bouton a été relâché.
 * @param LOST_FOCUS Alias de GO_DOWN pour une perte de focus.
 * @param GOT_FOCUS Alias de GO_UP pour un gain de focus.
 * @param CONNECTED Alias de GO_DOWN pour une connexion.
 * @param DISCONNECTED Alias de GO_UP pour une déconnexion.
 * @param ENTERING Alias de GO_DOWN pour l'entrée dans un contexte.
 * @param LEAVING Alias de GO_UP pour la sortie d'un contexte.
 * @see t_bunny_key, t_bunny_click, t_bunny_joy_connect
 */
typedef enum			e_bunny_event_state
  {
    GO_DOWN,
    GO_UP,
    LOST_FOCUS			= GO_DOWN,
    GOT_FOCUS			= GO_UP,
    CONNECTED			= GO_DOWN,
    DISCONNECTED		= GO_UP,
    ENTERING			= GO_DOWN,
    LEAVING			= GO_UP
  }				t_bunny_event_state;

/*!
** The type of the function that will handle keyboard event.
** t_bunny_event_state is the action: the key was pressed or released.
** t_bunny_keysym is the key that was pressed or released. See enum.h for more informations.
** The void* pointer can be anything: it is what you sent to bunny_loop or bunny_loop_mw
** as last parameter.
** Return a t_bunny_response in order to keep the loop or break it.
*/
/**
 * @doc-symbol t_bunny_key
 * @doc-module events
 * @doc-kind type
 * @doc-order 30
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Callback type for keyboard press and release events.
 * @param sta Tells whether the key was pressed or released.
 * @param sym The key symbol concerned by the event.
 * @param dat The data pointer sent to bunny_loop or bunny_loop_mw.
 * @return-success GO_ON to keep the loop running, or another t_bunny_response to stop or change it.
 * @see bunny_set_key_response, bunny_get_keyboard, t_bunny_type
 *
 * @doc-lang fr
 * @brief Type de callback pour les appuis et relâchements de touches.
 * @param sta Indique si la touche a été enfoncée ou relâchée.
 * @param sym Le symbole de touche concerné par l'événement.
 * @param dat Le pointeur de données transmis à bunny_loop ou bunny_loop_mw.
 * @return-success GO_ON pour laisser la boucle continuer, ou une autre valeur t_bunny_response pour l'arrêter ou la changer.
 * @see bunny_set_key_response, bunny_get_keyboard, t_bunny_type
 */
typedef t_bunny_response	(*t_bunny_key)(t_bunny_event_state		sta,
					       t_bunny_keysym			sym,
					       void				*dat);

typedef t_bunny_response	t_bunny_key_function(t_bunny_event_state	sta,
						     t_bunny_keysym		sym,
						     void			*dat);

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
/**
 * @doc-symbol t_bunny_type
 * @doc-module events
 * @doc-kind type
 * @doc-order 60
 * @doc-since 5
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Callback type for text input events.
 * @param unicode The typed Unicode code point.
 * @param data The data pointer sent to bunny_loop or bunny_loop_mw.
 * @return-success GO_ON to keep the loop running, or another t_bunny_response to stop or change it.
 * @see bunny_set_text_response, t_bunny_key
 *
 * @doc-lang fr
 * @brief Type de callback pour la saisie de texte.
 * @param unicode Le point de code Unicode saisi.
 * @param data Le pointeur de données transmis à bunny_loop ou bunny_loop_mw.
 * @return-success GO_ON pour laisser la boucle continuer, ou une autre valeur t_bunny_response pour l'arrêter ou la changer.
 * @see bunny_set_text_response, t_bunny_key
 */
typedef t_bunny_response	(*t_bunny_type)(uint32_t			unicode,
						void				*data);

typedef t_bunny_response	t_bunny_type_function(uint32_t			unicode,
						      void			*data);

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
/**
 * @doc-symbol t_bunny_click
 * @doc-module events
 * @doc-kind type
 * @doc-order 80
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Callback type for mouse button press and release events.
 * @param sta Tells whether the button was pressed or released.
 * @param but The mouse button concerned by the event.
 * @param dat The data pointer sent to bunny_loop or bunny_loop_mw.
 * @return-success GO_ON to keep the loop running, or another t_bunny_response to stop or change it.
 * @see bunny_set_click_response, bunny_get_mouse_button, t_bunny_mouse_button
 *
 * @doc-lang fr
 * @brief Type de callback pour les appuis et relâchements de boutons de souris.
 * @param sta Indique si le bouton a été enfoncé ou relâché.
 * @param but Le bouton de souris concerné par l'événement.
 * @param dat Le pointeur de données transmis à bunny_loop ou bunny_loop_mw.
 * @return-success GO_ON pour laisser la boucle continuer, ou une autre valeur t_bunny_response pour l'arrêter ou la changer.
 * @see bunny_set_click_response, bunny_get_mouse_button, t_bunny_mouse_button
 */
typedef t_bunny_response	(*t_bunny_click)(t_bunny_event_state		sta,
						 t_bunny_mouse_button		but,
						 void				*dat);

typedef t_bunny_response	t_bunny_click_function(t_bunny_event_state	sta,
						       t_bunny_mouse_button	but,
						       void			*dat);

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
/**
 * @doc-symbol t_bunny_move
 * @doc-module events
 * @doc-kind type
 * @doc-order 110
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Callback type for mouse movement events.
 * @param relative The movement of the mouse since the previous mouse move event.
 * @param dat The data pointer sent to bunny_loop or bunny_loop_mw.
 * @return-success GO_ON to keep the loop running, or another t_bunny_response to stop or change it.
 * @see bunny_set_move_response, bunny_get_mouse_position
 *
 * @doc-lang fr
 * @brief Type de callback pour les déplacements de souris.
 * @param relative Le déplacement de la souris depuis le précédent événement de mouvement.
 * @param dat Le pointeur de données transmis à bunny_loop ou bunny_loop_mw.
 * @return-success GO_ON pour laisser la boucle continuer, ou une autre valeur t_bunny_response pour l'arrêter ou la changer.
 * @see bunny_set_move_response, bunny_get_mouse_position
 */
typedef t_bunny_response	(*t_bunny_move)(const t_bunny_position		*relative,
						void				*dat);

typedef t_bunny_response	t_bunny_move_function(const t_bunny_position	*relative,
						      void			*dat);

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
/**
 * @doc-symbol t_bunny_wheel
 * @doc-module events
 * @doc-kind type
 * @doc-order 140
 * @doc-since 5
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Callback type for mouse wheel events.
 * @param wheelid The wheel identifier.
 * @param delta The movement amount reported by the wheel.
 * @param data The data pointer sent to bunny_loop or bunny_loop_mw.
 * @return-success GO_ON to keep the loop running, or another t_bunny_response to stop or change it.
 * @see bunny_set_wheel_response
 *
 * @doc-lang fr
 * @brief Type de callback pour les événements de molette de souris.
 * @param wheelid L'identifiant de la molette.
 * @param delta L'amplitude du mouvement signalé par la molette.
 * @param data Le pointeur de données transmis à bunny_loop ou bunny_loop_mw.
 * @return-success GO_ON pour laisser la boucle continuer, ou une autre valeur t_bunny_response pour l'arrêter ou la changer.
 * @see bunny_set_wheel_response
 */
typedef t_bunny_response	(*t_bunny_wheel)(int				wheelid,
						 int				delta,
						 void				*data);

typedef t_bunny_response	t_bunny_wheel_function(int			wheelid,
						       int			delta,
						       void			*data);

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
/**
 * @doc-symbol t_bunny_joystick
 * @doc-module events
 * @doc-kind type
 * @doc-order 160
 * @doc-since 5
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Describes one joystick slot.
 * @description The array of joystick slots is refreshed by bunny_update_joysticks and when windows are created.
 * @param connected True if a joystick is currently connected to this slot.
 * @param name The joystick name, or NULL when no joystick is connected.
 * @param vendor The vendor identifier reported by the backend.
 * @param product The product identifier reported by the backend.
 * @param nb_button The number of buttons reported by the backend.
 * @param axis Bit field describing available t_bunny_axis values.
 * @param vibration_gain The current vibration gain requested through bunny_set_joystick_vibration.
 * @param vibrating True when a vibration request is active.
 * @see bunny_get_joy_info, bunny_update_joysticks, t_bunny_joy_connect
 *
 * @doc-lang fr
 * @brief Décrit un emplacement de joystick.
 * @description Le tableau d'emplacements de joysticks est rafraîchi par bunny_update_joysticks et lors de la création des fenêtres.
 * @param connected Vaut true si un joystick est actuellement connecté à cet emplacement.
 * @param name Le nom du joystick, ou NULL si aucun joystick n'est connecté.
 * @param vendor L'identifiant de constructeur fourni par le moteur sous-jacent.
 * @param product L'identifiant de produit fourni par le moteur sous-jacent.
 * @param nb_button Le nombre de boutons fourni par le moteur sous-jacent.
 * @param axis Champ de bits décrivant les valeurs t_bunny_axis disponibles.
 * @param vibration_gain Le gain de vibration courant demandé via bunny_set_joystick_vibration.
 * @param vibrating Vaut true lorsqu'une demande de vibration est active.
 * @see bunny_get_joy_info, bunny_update_joysticks, t_bunny_joy_connect
 */
typedef struct			s_bunny_joystick
{
  bool				connected;
  const char			*name;
  unsigned int			vendor;
  unsigned int			product;
  unsigned int			nb_button;
  unsigned char			axis;
  double			vibration_gain;
  bool				vibrating;
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
/**
 * @doc-symbol t_bunny_joy_connect
 * @doc-module events
 * @doc-kind type
 * @doc-order 170
 * @doc-since 5
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Callback type for joystick connection and disconnection events.
 * @param state CONNECTED when a joystick appears, DISCONNECTED when it disappears.
 * @param joyid The joystick slot identifier.
 * @param joyinfo The information known about the joystick slot.
 * @param data The data pointer sent to bunny_loop or bunny_loop_mw.
 * @return-success GO_ON to keep the loop running, or another t_bunny_response to stop or change it.
 * @see bunny_set_joy_connect_response, bunny_get_joy_info
 *
 * @doc-lang fr
 * @brief Type de callback pour les connexions et déconnexions de joysticks.
 * @param state CONNECTED lorsqu'un joystick apparaît, DISCONNECTED lorsqu'il disparaît.
 * @param joyid L'identifiant de l'emplacement de joystick.
 * @param joyinfo Les informations connues sur l'emplacement de joystick.
 * @param data Le pointeur de données transmis à bunny_loop ou bunny_loop_mw.
 * @return-success GO_ON pour laisser la boucle continuer, ou une autre valeur t_bunny_response pour l'arrêter ou la changer.
 * @see bunny_set_joy_connect_response, bunny_get_joy_info
 */
typedef t_bunny_response	(*t_bunny_joy_connect)(t_bunny_event_state	state,
						       int			joyid,
						       const t_bunny_joystick	*joyinfo,
						       void			*data);

typedef t_bunny_response	t_bunny_joy_connect_function(t_bunny_event_state state,
							     int		joyid,
							     const t_bunny_joystick *joyinfo,
							     void		*data);
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
void				bunny_update_joysticks(void);

/*!
** The tpye of the function that will handle any changing on a joystick axis.
** joyid is the id of the joystick that got a changing axis
** t_bunny_axis is the axis that changed
** value is the new value of the axis [-100; +100]
** The void* pointer can be anything: it is what you sent to bunny_loop or bunny_loop_mw
** as last parameter.
** Return a t_bunny_response in order to keep the loop or break it.
*/
/**
 * @doc-symbol t_bunny_joy_axis
 * @doc-module events
 * @doc-kind type
 * @doc-order 190
 * @doc-since 5
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Callback type for joystick axis movement events.
 * @param joyid The joystick slot identifier.
 * @param axis The axis that changed.
 * @param value The new axis value, usually between -100 and 100.
 * @param data The data pointer sent to bunny_loop or bunny_loop_mw.
 * @return-success GO_ON to keep the loop running, or another t_bunny_response to stop or change it.
 * @see bunny_set_joy_axis_response, bunny_set_joy_axis_minimum_offset, bunny_get_joy_axis
 *
 * @doc-lang fr
 * @brief Type de callback pour les déplacements d'axes de joystick.
 * @param joyid L'identifiant de l'emplacement de joystick.
 * @param axis L'axe qui a changé.
 * @param value La nouvelle valeur de l'axe, généralement comprise entre -100 et 100.
 * @param data Le pointeur de données transmis à bunny_loop ou bunny_loop_mw.
 * @return-success GO_ON pour laisser la boucle continuer, ou une autre valeur t_bunny_response pour l'arrêter ou la changer.
 * @see bunny_set_joy_axis_response, bunny_set_joy_axis_minimum_offset, bunny_get_joy_axis
 */
typedef t_bunny_response	(*t_bunny_joy_axis)(int				joyid,
						    t_bunny_axis		axis,
						    float			value,
						    void			*data);

typedef t_bunny_response	t_bunny_joy_axis_function(int			joyid,
							  t_bunny_axis		axis,
							  float			value,
							  void			*data);

/*!
** Register the sent function in order to call it when a joystick axis event occurs.
** \param axis The function to call.
*/
void				bunny_set_joy_axis_response(t_bunny_joy_axis	axis);

/*!
** Set a minimum offset between the previous value and the new one to trigger
** the joystick axis response.
** \param offset The offset [0; +100]
*/
void				bunny_set_joystick_threshold(t_bunny_window	*win,
							     float		offset);

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
/**
 * @doc-symbol t_bunny_joy_button
 * @doc-module events
 * @doc-kind type
 * @doc-order 230
 * @doc-since 5
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Callback type for joystick button press and release events.
 * @param state Tells whether the button was pressed or released.
 * @param joyid The joystick slot identifier.
 * @param button The joystick button identifier.
 * @param data The data pointer sent to bunny_loop or bunny_loop_mw.
 * @return-success GO_ON to keep the loop running, or another t_bunny_response to stop or change it.
 * @see bunny_set_joy_button_response, bunny_get_joy_button
 *
 * @doc-lang fr
 * @brief Type de callback pour les appuis et relâchements de boutons de joystick.
 * @param state Indique si le bouton a été enfoncé ou relâché.
 * @param joyid L'identifiant de l'emplacement de joystick.
 * @param button L'identifiant du bouton de joystick.
 * @param data Le pointeur de données transmis à bunny_loop ou bunny_loop_mw.
 * @return-success GO_ON pour laisser la boucle continuer, ou une autre valeur t_bunny_response pour l'arrêter ou la changer.
 * @see bunny_set_joy_button_response, bunny_get_joy_button
 */
typedef t_bunny_response	(*t_bunny_joy_button)(t_bunny_event_state	state,
						      int			joyid,
						      int			button,
						      void			*data);

typedef t_bunny_response	t_bunny_joy_button_function(t_bunny_event_state	state,
							    int			joyid,
							    int			button,
							    void		*data);

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

bool				bunny_set_joystick_vibration(int		joy_id,
							     double		strength);

/*!
** The type of the function that will handle the get focus event.
** t_bunny_window is the address of the window that got the focus
** The void* pointer can be anything: it is what you sent to bunny_loop or bunny_loop_mw
** as last_parameter
** Return a t_bunny_response in order to keep the loop or break it.
*/
/**
 * @doc-symbol t_bunny_get_focus
 * @doc-module events
 * @doc-kind type
 * @doc-order 260
 * @doc-since 7
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Callback type for window focus gain events.
 * @param win The window that gained focus.
 * @param data The data pointer sent to bunny_loop or bunny_loop_mw.
 * @return-success GO_ON to keep the loop running, or another t_bunny_response to stop or change it.
 * @see bunny_set_get_focus_response, t_bunny_lost_focus
 *
 * @doc-lang fr
 * @brief Type de callback pour les gains de focus de fenêtre.
 * @param win La fenêtre qui a obtenu le focus.
 * @param data Le pointeur de données transmis à bunny_loop ou bunny_loop_mw.
 * @return-success GO_ON pour laisser la boucle continuer, ou une autre valeur t_bunny_response pour l'arrêter ou la changer.
 * @see bunny_set_get_focus_response, t_bunny_lost_focus
 */
typedef t_bunny_response	(*t_bunny_get_focus)(const t_bunny_window	*win,
						     void			*data);

typedef t_bunny_response	t_bunny_get_focus_function(const t_bunny_window	*win,
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
/**
 * @doc-symbol t_bunny_lost_focus
 * @doc-module events
 * @doc-kind type
 * @doc-order 280
 * @doc-since 7
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Callback type for window focus loss events.
 * @param win The window that lost focus.
 * @param data The data pointer sent to bunny_loop or bunny_loop_mw.
 * @return-success GO_ON to keep the loop running, or another t_bunny_response to stop or change it.
 * @see bunny_set_lost_focus_response, t_bunny_get_focus
 *
 * @doc-lang fr
 * @brief Type de callback pour les pertes de focus de fenêtre.
 * @param win La fenêtre qui a perdu le focus.
 * @param data Le pointeur de données transmis à bunny_loop ou bunny_loop_mw.
 * @return-success GO_ON pour laisser la boucle continuer, ou une autre valeur t_bunny_response pour l'arrêter ou la changer.
 * @see bunny_set_lost_focus_response, t_bunny_get_focus
 */
typedef t_bunny_response	(*t_bunny_lost_focus)(const t_bunny_window	*win,
						      void			*data);

typedef t_bunny_response	t_bunny_lost_focus_function(const t_bunny_window *win,
							    void		*data);

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
/**
 * @doc-symbol t_bunny_resize
 * @doc-module events
 * @doc-kind type
 * @doc-order 300
 * @doc-since 7
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Callback type for window resize events.
 * @param win The resized window.
 * @param siz The new window size.
 * @param data The data pointer sent to bunny_loop or bunny_loop_mw.
 * @return-success GO_ON to keep the loop running, or another t_bunny_response to stop or change it.
 * @see bunny_set_resize_response
 *
 * @doc-lang fr
 * @brief Type de callback pour les redimensionnements de fenêtre.
 * @param win La fenêtre redimensionnée.
 * @param siz La nouvelle taille de la fenêtre.
 * @param data Le pointeur de données transmis à bunny_loop ou bunny_loop_mw.
 * @return-success GO_ON pour laisser la boucle continuer, ou une autre valeur t_bunny_response pour l'arrêter ou la changer.
 * @see bunny_set_resize_response
 */
typedef t_bunny_response	(*t_bunny_resize)(const t_bunny_window		*win,
						  const t_bunny_position	*siz,
						  void				*data);

typedef t_bunny_response	t_bunny_resize_function(const t_bunny_window	*win,
							const t_bunny_position	*siz,
							void			*data);

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
/**
 * @doc-symbol t_bunny_close
 * @doc-module events
 * @doc-kind type
 * @doc-order 320
 * @doc-since 7
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Callback type for window close request events.
 * @param win The window that received the close request.
 * @param data The data pointer sent to bunny_loop_mw.
 * @return-success GO_ON to keep the loop running, or another t_bunny_response to stop or change it.
 * @see bunny_set_close_response, bunny_loop_mw
 *
 * @doc-lang fr
 * @brief Type de callback pour les demandes de fermeture de fenêtre.
 * @param win La fenêtre qui a reçu la demande de fermeture.
 * @param data Le pointeur de données transmis à bunny_loop_mw.
 * @return-success GO_ON pour laisser la boucle continuer, ou une autre valeur t_bunny_response pour l'arrêter ou la changer.
 * @see bunny_set_close_response, bunny_loop_mw
 */
typedef t_bunny_response	(*t_bunny_close)(const t_bunny_window		*win,
						 void				*data);

typedef t_bunny_response	t_bunny_close_function(const t_bunny_window	*win,
						       void			*data);

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
/**
 * @doc-symbol t_bunny_display
 * @doc-module events
 * @doc-kind type
 * @doc-order 340
 * @doc-since 7
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Callback type for display refresh events.
 * @param data The data pointer sent to bunny_loop or bunny_loop_mw.
 * @return-success GO_ON to keep the loop running, or another t_bunny_response to stop or change it.
 * @see bunny_set_display_function, bunny_loop
 *
 * @doc-lang fr
 * @brief Type de callback pour les rafraîchissements d'affichage.
 * @param data Le pointeur de données transmis à bunny_loop ou bunny_loop_mw.
 * @return-success GO_ON pour laisser la boucle continuer, ou une autre valeur t_bunny_response pour l'arrêter ou la changer.
 * @see bunny_set_display_function, bunny_loop
 */
typedef t_bunny_response	(*t_bunny_display)(void				*data);

typedef t_bunny_response	t_bunny_display_function(void			*data);

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
/**
 * @doc-symbol t_bunny_loop
 * @doc-module events
 * @doc-kind type
 * @doc-order 360
 * @doc-since 0
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Callback type for fixed-frequency main loop events.
 * @param dat The data pointer sent to bunny_loop or bunny_loop_mw.
 * @return-success GO_ON to keep the loop running, or another t_bunny_response to stop or change it.
 * @see bunny_set_loop_main_function, bunny_loop, bunny_loop_mw
 *
 * @doc-lang fr
 * @brief Type de callback pour la boucle principale à fréquence fixe.
 * @param dat Le pointeur de données transmis à bunny_loop ou bunny_loop_mw.
 * @return-success GO_ON pour laisser la boucle continuer, ou une autre valeur t_bunny_response pour l'arrêter ou la changer.
 * @see bunny_set_loop_main_function, bunny_loop, bunny_loop_mw
 */
typedef t_bunny_response	(*t_bunny_loop)(void				*dat);

typedef t_bunny_response	t_bunny_loop_function(void			*dat);

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
					   unsigned int				freq,
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
					      unsigned int			freq,
					      void				*data);

/*!
** Get the frequency of the current bunny_loop
** \return The number of call to the loop callback per seconds, under good
** condition of performences.
*/
int				bunny_get_frequency(void);
double				bunny_get_delay(void);

/*
** Network event
*/

/**
 * @doc-symbol t_bunny_message_response
 * @doc-module events
 * @doc-kind type
 * @doc-order 460
 * @doc-since 11
 * @doc-until latest
 * @doc-level expert
 *
 * @doc-lang en
 * @brief Callback type for incoming network message events.
 * @param clt The network peer that sent the message.
 * @param buffer The received message buffer.
 * @param size The size of the received message in bytes.
 * @param data The data pointer sent to bunny_loop or bunny_loop_mw.
 * @return-success GO_ON to keep the loop running, or another t_bunny_response to stop or change it.
 * @see bunny_set_message_response, t_bunny_connect_response
 *
 * @doc-lang fr
 * @brief Type de callback pour les messages réseau entrants.
 * @param clt Le pair réseau qui a envoyé le message.
 * @param buffer Le tampon du message reçu.
 * @param size La taille du message reçu en octets.
 * @param data Le pointeur de données transmis à bunny_loop ou bunny_loop_mw.
 * @return-success GO_ON pour laisser la boucle continuer, ou une autre valeur t_bunny_response pour l'arrêter ou la changer.
 * @see bunny_set_message_response, t_bunny_connect_response
 */
typedef t_bunny_response	(*t_bunny_message_response)(t_bunny_network_info clt,
							    void		*buffer,
							    size_t		size,
							    void		*data);

typedef t_bunny_response	t_bunny_message_response_function(t_bunny_network_info clt,
								  void		*buffer,
								  size_t	size,
								  void		*data);

/*!
** Set the function that will be called whe you receive a message.
** \param func The function that will be called.
*/
void				bunny_set_message_response(t_bunny_message_response func);

/*!
** The type of the function that will be called when a t_bunny_client or a t_bunny_server
** or an opened connection by a t_bunny_server is opened or closed.
** \param fd The file descriptor that receive the message.
** \param state Is the file descriptor opened or closed.
** \param data The data parameter of bunny_loop
** \return A t_bunny_response in order to keep the loop or break it.
*/
/**
 * @doc-symbol t_bunny_connect_response
 * @doc-module events
 * @doc-kind type
 * @doc-order 480
 * @doc-since 11
 * @doc-until latest
 * @doc-level expert
 *
 * @doc-lang en
 * @brief Callback type for network connection and disconnection events.
 * @param clt The network peer whose state changed.
 * @param state CONNECTED when the peer opens, DISCONNECTED when it closes.
 * @param data The data pointer sent to bunny_loop or bunny_loop_mw.
 * @return-success GO_ON to keep the loop running, or another t_bunny_response to stop or change it.
 * @see bunny_set_connect_response, t_bunny_message_response
 *
 * @doc-lang fr
 * @brief Type de callback pour les connexions et déconnexions réseau.
 * @param clt Le pair réseau dont l'état a changé.
 * @param state CONNECTED lorsque le pair s'ouvre, DISCONNECTED lorsqu'il se ferme.
 * @param data Le pointeur de données transmis à bunny_loop ou bunny_loop_mw.
 * @return-success GO_ON pour laisser la boucle continuer, ou une autre valeur t_bunny_response pour l'arrêter ou la changer.
 * @see bunny_set_connect_response, t_bunny_message_response
 */
typedef t_bunny_response	(*t_bunny_connect_response)(t_bunny_network_info clt,
							    t_bunny_event_state	state,
							    void		*data);

typedef t_bunny_response	t_bunny_connect_response_function(t_bunny_network_info cnt,
								  t_bunny_event_state state,
								  void		*data);

/*!
** Set the function that will be called when a connection is opened or closed.
** \param func The function to call
*/
void				bunny_set_connect_response(t_bunny_connect_response func);

/*!
** Set the function that will be called when you enter in the bunny loop.
** \param func The function to call
*/
void				bunny_set_entering_context_response(t_bunny_loop func);

typedef t_bunny_response	t_bunny_entering_context_function(void		*dat);

/*!
** The type of the function that will be called when the bunny_loop is exited.
** It receives what will be the return value.
** \param returned The value that will be sent to the bunny_loop caller
** \param data The data parameter of bunny loop
*/
/**
 * @doc-symbol t_bunny_leaving_context
 * @doc-module events
 * @doc-kind type
 * @doc-order 510
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Callback type called when the event loop leaves its current context.
 * @param returned The value that will be returned by bunny_loop or bunny_loop_mw.
 * @param data The data pointer sent to bunny_loop or bunny_loop_mw.
 * @see bunny_set_leaving_context_response, bunny_set_entering_context_response
 *
 * @doc-lang fr
 * @brief Type de callback appelé lorsque la boucle d'événements quitte son contexte courant.
 * @param returned La valeur qui sera renvoyée par bunny_loop ou bunny_loop_mw.
 * @param data Le pointeur de données transmis à bunny_loop ou bunny_loop_mw.
 * @see bunny_set_leaving_context_response, bunny_set_entering_context_response
 */
typedef void			(*t_bunny_leaving_context)(t_bunny_response	returned,
							   void			*data);

typedef void			t_bunny_leaving_context_function(t_bunny_response returned,
								 void		*data);

/*!
** Set the function that will be called when you leave the bunny loop.
** \param func The function to call
*/
void				bunny_set_leaving_context_response(t_bunny_leaving_context func);

/*!
** The type of the callback function to call when asynchronous computation set with
** bunny_async_computation is done.
** \param cmt The computed value
** \param data The data parameter of bunny loop
*/
/**
 * @doc-symbol t_bunny_async_computation_response
 * @doc-module events
 * @doc-kind type
 * @doc-order 522
 * @doc-since 12
 * @doc-until latest
 * @doc-level expert
 *
 * @doc-lang en
 * @brief Callback type for asynchronous computation completion events.
 * @param cmt The computed value returned by the asynchronous computation.
 * @param data The data pointer sent to bunny_loop or bunny_loop_mw.
 * @return-success GO_ON to keep the loop running, or another t_bunny_response to stop or change it.
 * @see bunny_async_computation, bunny_set_async_computation_response
 *
 * @doc-lang fr
 * @brief Type de callback pour les fins de calcul asynchrone.
 * @param cmt La valeur calculée renvoyée par le traitement asynchrone.
 * @param data Le pointeur de données transmis à bunny_loop ou bunny_loop_mw.
 * @return-success GO_ON pour laisser la boucle continuer, ou une autre valeur t_bunny_response pour l'arrêter ou la changer.
 * @see bunny_async_computation, bunny_set_async_computation_response
 */
typedef t_bunny_response	(*t_bunny_async_computation_response)(void	*cmt,
								      void	*data);

typedef t_bunny_response	t_bunny_async_computation_response_function(void *cmt,
									    void *data);

/*!
** Set a callback function to be called when asynchronous computation set with
** bunny_async_computation is done.
** \param func The function to call.
*/
void				bunny_set_async_computation_response(t_bunny_async_computation_response func);

/*
** It miss touch event and sensor event (as the main loop) that are also
** available throught SFML. It should be added later.
** It also miss mouse entered and mouse left
*/
/**
 * @doc-symbol t_bunny_event_type
 * @doc-module events
 * @doc-kind type
 * @doc-order 440
 * @doc-since 12
 * @doc-until latest
 * @doc-level expert
 *
 * @doc-lang en
 * @brief Enumerates raw backend event categories stored in t_bunny_event.
 * @description These values are used by the generic event callback registered with bunny_set_event_response.
 * @see t_bunny_event, t_bunny_event_response, bunny_set_event_response
 *
 * @doc-lang fr
 * @brief Énumère les catégories d'événements bruts stockées dans t_bunny_event.
 * @description Ces valeurs sont utilisées par le callback générique enregistré avec bunny_set_event_response.
 * @see t_bunny_event, t_bunny_event_response, bunny_set_event_response
 */
typedef enum			e_bunny_event_type
  {
    BET_CLOSE_WINDOW,
    BET_RESIZE_WINDOW,
    BET_LOST_FOCUS,
    BET_GAIN_FOCUS,
    BET_TEXT_ENTERED,
    BET_KEY_PRESSED,
    BET_KEY_RELEASED,
    BET_MOUSE_WHEEL,
    BET_MOUSE_BUTTON_PRESSED,
    BET_MOUSE_BUTTON_RELEASED,
    BET_MOUSE_MOVED,
    BET_MOUSE_MOVED_RAW,
    BET_MOUSE_ENTERED,
    BET_MOUSE_LEFT,
    BET_JOYSTICK_BUTTON_PRESSED,
    BET_JOYSTICK_BUTTON_RELEASED,
    BET_JOYSTICK_MOVED,
    BET_JOYSTICK_CONNECTED,
    BET_JOYSTICK_DISCONNECTED,
    BET_TOUCH_BEGAN,
    BET_TOUCH_MOVED,
    BET_TOUCH_ENDED,
    BET_SENSOR
  }				t_bunny_event_type;

/**
 * @doc-symbol t_bunny_size_event
 * @doc-module events
 * @doc-kind type
 * @doc-order 441
 * @doc-since 12
 * @doc-until latest
 * @doc-level expert
 *
 * @doc-lang en
 * @brief Payload of a raw window resize event.
 * @param width The new window width.
 * @param height The new window height.
 * @see t_bunny_event
 *
 * @doc-lang fr
 * @brief Charge utile d'un événement brut de redimensionnement de fenêtre.
 * @param width La nouvelle largeur de la fenêtre.
 * @param height La nouvelle hauteur de la fenêtre.
 * @see t_bunny_event
 */
typedef struct			s_bunny_size_event
{
  unsigned int			width;
  unsigned int			height;
}				t_bunny_size_event;

/**
 * @doc-symbol t_bunny_key_event
 * @doc-module events
 * @doc-kind type
 * @doc-order 442
 * @doc-since 12
 * @doc-until latest
 * @doc-level expert
 *
 * @doc-lang en
 * @brief Payload of a raw keyboard event.
 * @param sym The key symbol.
 * @param alt True when Alt was held.
 * @param control True when Control was held.
 * @param shift True when Shift was held.
 * @param system True when the system modifier was held.
 * @see t_bunny_event
 *
 * @doc-lang fr
 * @brief Charge utile d'un événement brut de clavier.
 * @param sym Le symbole de touche.
 * @param alt Vaut true si Alt était maintenu.
 * @param control Vaut true si Contrôle était maintenu.
 * @param shift Vaut true si Shift était maintenu.
 * @param system Vaut true si le modificateur système était maintenu.
 * @see t_bunny_event
 */
typedef struct			s_bunny_key_event
{
  t_bunny_keysym		sym;
  bool				alt;
  bool				control;
  bool				shift;
  bool				system;
}				t_bunny_key_event;

/**
 * @doc-symbol t_bunny_text_event
 * @doc-module events
 * @doc-kind type
 * @doc-order 443
 * @doc-since 12
 * @doc-until latest
 * @doc-level expert
 *
 * @doc-lang en
 * @brief Payload of a raw text input event.
 * @param unicode The typed Unicode code point.
 * @see t_bunny_event
 *
 * @doc-lang fr
 * @brief Charge utile d'un événement brut de saisie de texte.
 * @param unicode Le point de code Unicode saisi.
 * @see t_bunny_event
 */
typedef struct			s_bunny_text_event
{
  uint32_t			unicode;
}				t_bunny_text_event;

/**
 * @doc-symbol t_bunny_mouse_move_event
 * @doc-module events
 * @doc-kind type
 * @doc-order 444
 * @doc-since 12
 * @doc-until latest
 * @doc-level expert
 *
 * @doc-lang en
 * @brief Payload of a raw mouse movement event.
 * @param x The horizontal position or delta, depending on the raw event type.
 * @param y The vertical position or delta, depending on the raw event type.
 * @see t_bunny_event
 *
 * @doc-lang fr
 * @brief Charge utile d'un événement brut de déplacement de souris.
 * @param x La position ou différence horizontale, selon le type d'événement brut.
 * @param y La position ou différence verticale, selon le type d'événement brut.
 * @see t_bunny_event
 */
typedef struct			s_bunny_mouse_move_event
{
  int				x;
  int				y;
}				t_bunny_mouse_move_event;

/**
 * @doc-symbol t_bunny_mouse_button_event
 * @doc-module events
 * @doc-kind type
 * @doc-order 445
 * @doc-since 12
 * @doc-until latest
 * @doc-level expert
 *
 * @doc-lang en
 * @brief Payload of a raw mouse button event.
 * @param button The mouse button concerned by the event.
 * @param x The mouse X position when the event occurred.
 * @param y The mouse Y position when the event occurred.
 * @see t_bunny_event
 *
 * @doc-lang fr
 * @brief Charge utile d'un événement brut de bouton de souris.
 * @param button Le bouton de souris concerné par l'événement.
 * @param x La position X de la souris au moment de l'événement.
 * @param y La position Y de la souris au moment de l'événement.
 * @see t_bunny_event
 */
typedef struct			s_bunny_mouse_button_event
{
  t_bunny_mouse_button		button;
  int				x;
  int				y;
}				t_bunny_mouse_button_event;

/**
 * @doc-symbol t_bunny_mouse_wheel_event
 * @doc-module events
 * @doc-kind type
 * @doc-order 446
 * @doc-since 12
 * @doc-until latest
 * @doc-level expert
 *
 * @doc-lang en
 * @brief Payload of a raw mouse wheel event.
 * @param wheel The wheel identifier.
 * @param delta The wheel movement amount.
 * @param x The mouse X position when the event occurred.
 * @param y The mouse Y position when the event occurred.
 * @see t_bunny_event
 *
 * @doc-lang fr
 * @brief Charge utile d'un événement brut de molette de souris.
 * @param wheel L'identifiant de la molette.
 * @param delta L'amplitude du mouvement de molette.
 * @param x La position X de la souris au moment de l'événement.
 * @param y La position Y de la souris au moment de l'événement.
 * @see t_bunny_event
 */
typedef struct			s_bunny_mouse_wheel_event
{
  int				wheel;
  int				delta;
  int				x;
  int				y;
}				t_bunny_mouse_wheel_event;

/**
 * @doc-symbol t_bunny_joystick_connect_event
 * @doc-module events
 * @doc-kind type
 * @doc-order 447
 * @doc-since 12
 * @doc-until latest
 * @doc-level expert
 *
 * @doc-lang en
 * @brief Payload of a raw joystick connection event.
 * @param joystick_id The joystick slot identifier.
 * @see t_bunny_event
 *
 * @doc-lang fr
 * @brief Charge utile d'un événement brut de connexion de joystick.
 * @param joystick_id L'identifiant de l'emplacement de joystick.
 * @see t_bunny_event
 */
typedef struct			s_bunny_joystick_connect_event
{
  unsigned int			joystick_id;
}				t_bunny_joystick_connect_event;

/**
 * @doc-symbol t_bunny_joystick_move_event
 * @doc-module events
 * @doc-kind type
 * @doc-order 448
 * @doc-since 12
 * @doc-until latest
 * @doc-level expert
 *
 * @doc-lang en
 * @brief Payload of a raw joystick axis event.
 * @param joystick_id The joystick slot identifier.
 * @param axis The axis that moved.
 * @param position The new axis value.
 * @see t_bunny_event
 *
 * @doc-lang fr
 * @brief Charge utile d'un événement brut d'axe de joystick.
 * @param joystick_id L'identifiant de l'emplacement de joystick.
 * @param axis L'axe qui a bougé.
 * @param position La nouvelle valeur de l'axe.
 * @see t_bunny_event
 */
typedef struct			s_bunny_joystick_move_event
{
  unsigned int			joystick_id;
  t_bunny_axis			axis;
  float				position;
}				t_bunny_joystick_move_event;

/**
 * @doc-symbol t_bunny_joystick_button_event
 * @doc-module events
 * @doc-kind type
 * @doc-order 449
 * @doc-since 12
 * @doc-until latest
 * @doc-level expert
 *
 * @doc-lang en
 * @brief Payload of a raw joystick button event.
 * @param joystick_id The joystick slot identifier.
 * @param button The joystick button identifier.
 * @see t_bunny_event
 *
 * @doc-lang fr
 * @brief Charge utile d'un événement brut de bouton de joystick.
 * @param joystick_id L'identifiant de l'emplacement de joystick.
 * @param button L'identifiant du bouton de joystick.
 * @see t_bunny_event
 */
typedef struct			s_bunny_joystick_button_event
{
  unsigned int			joystick_id;
  unsigned int			button;
}				t_bunny_joystick_button_event;

typedef struct			u_bunny_event
{
  t_bunny_event_type		type;
  union
  {
    t_bunny_size_event		size;
    t_bunny_key_event		key;
    t_bunny_text_event		text;
    t_bunny_mouse_move_event	mouse_moved;
    t_bunny_mouse_button_event	mouse_button;
    t_bunny_mouse_wheel_event	wheel;
    t_bunny_joystick_connect_event joy_connect;
    t_bunny_joystick_move_event	joy_move;
    t_bunny_joystick_button_event joy_button;
  };
}				t_bunny_event;

/**
 * @doc-symbol t_bunny_event_response
 * @doc-module events
 * @doc-kind type
 * @doc-order 455
 * @doc-since 12
 * @doc-until latest
 * @doc-level expert
 *
 * @doc-lang en
 * @brief Callback type for generic raw events.
 * @description This callback is called before the specialized event callback associated with the event category.
 * @param event The raw event.
 * @param data The data pointer sent to bunny_loop or bunny_loop_mw.
 * @return-success GO_ON to keep the loop running and allow specialized callbacks, or another t_bunny_response to stop the loop.
 * @see bunny_set_event_response, t_bunny_event
 *
 * @doc-lang fr
 * @brief Type de callback pour les événements bruts génériques.
 * @description Ce callback est appelé avant le callback spécialisé associé à la catégorie de l'événement.
 * @param event L'événement brut.
 * @param data Le pointeur de données transmis à bunny_loop ou bunny_loop_mw.
 * @return-success GO_ON pour laisser la boucle continuer et permettre les callbacks spécialisés, ou une autre valeur t_bunny_response pour arrêter la boucle.
 * @see bunny_set_event_response, t_bunny_event
 */
typedef t_bunny_response	(*t_bunny_event_response)(const t_bunny_event	*event,
							  void			*data);

typedef t_bunny_response	t_bunny_event_response_function(const t_bunny_event *event,
								void		*data);

void				bunny_set_event_response(t_bunny_event_response	resp);

/*!
** The t_bunny_context structure is a collection of function pointer of various types.
** These types match all function pointer that can be sent with bunny_set_*_response,
** buny_set_loop_main_function or bunny_set_display_function.
** This structure is made to define a lot of callbacks in a single call, by defining
** a t_bunny_context somewhere (or an array...) and give it to bunny_set_context.
**
** A NULL pointer is a deactivated callback.
*/
/**
 * @doc-symbol t_bunny_context
 * @doc-module events
 * @doc-kind type
 * @doc-order 530
 * @doc-since 5
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Groups all event callbacks into a single context structure.
 * @description Each NULL function pointer disables the corresponding callback. This structure can be installed with bunny_set_context and copied back with bunny_get_context.
 * @param key Keyboard key callback.
 * @param type Text input callback.
 * @param click Mouse button callback.
 * @param move Mouse movement callback.
 * @param wheel Mouse wheel callback.
 * @param joy_connect Joystick connection callback.
 * @param joy_button Joystick button callback.
 * @param joy_axis Joystick axis callback.
 * @param get_focus Window focus gain callback.
 * @param lost_focus Window focus loss callback.
 * @param resize Window resize callback.
 * @param loop Fixed-frequency main callback.
 * @param display Display callback.
 * @param close Window close callback.
 * @param net_message Network message callback.
 * @param net_connect Network connection callback.
 * @param entering_context Callback called when entering the loop.
 * @param leaving_context Callback called when leaving the loop.
 * @param async_computation Callback called when an asynchronous computation completes.
 * @param event Generic raw event callback.
 * @see bunny_set_context, bunny_get_context, bunny_declare_context
 *
 * @doc-lang fr
 * @brief Regroupe tous les callbacks d'événements dans une même structure de contexte.
 * @description Chaque pointeur de fonction NULL désactive le callback correspondant. Cette structure peut être installée avec bunny_set_context et recopiée avec bunny_get_context.
 * @param key Callback des touches clavier.
 * @param type Callback de saisie de texte.
 * @param click Callback des boutons de souris.
 * @param move Callback des mouvements de souris.
 * @param wheel Callback de molette de souris.
 * @param joy_connect Callback de connexion de joystick.
 * @param joy_button Callback de bouton de joystick.
 * @param joy_axis Callback d'axe de joystick.
 * @param get_focus Callback de gain de focus de fenêtre.
 * @param lost_focus Callback de perte de focus de fenêtre.
 * @param resize Callback de redimensionnement de fenêtre.
 * @param loop Callback principal à fréquence fixe.
 * @param display Callback d'affichage.
 * @param close Callback de fermeture de fenêtre.
 * @param net_message Callback de message réseau.
 * @param net_connect Callback de connexion réseau.
 * @param entering_context Callback appelé à l'entrée dans la boucle.
 * @param leaving_context Callback appelé à la sortie de la boucle.
 * @param async_computation Callback appelé lorsqu'un calcul asynchrone se termine.
 * @param event Callback générique d'événement brut.
 * @see bunny_set_context, bunny_get_context, bunny_declare_context
 */
typedef struct			s_bunny_context
{
  t_bunny_key			key;
  t_bunny_type			type;
  t_bunny_click			click;
  t_bunny_move			move;
  t_bunny_wheel			wheel;
  union {
    t_bunny_joy_connect		connect;
    t_bunny_joy_connect		joy_connect;
  };
  union {
    t_bunny_joy_button		button;
    t_bunny_joy_button		joy_button;
  };
  union {
    t_bunny_joy_axis		axis;
    t_bunny_joy_axis		joy_axis;
  };
  t_bunny_get_focus		get_focus;
  t_bunny_lost_focus		lost_focus;
  t_bunny_resize		resize;
  t_bunny_loop			loop;
  t_bunny_display		display;
  t_bunny_close			close;
  union {
    t_bunny_message_response	net_message;
    t_bunny_message_response	netmessage _BDEPREC();
  };
  union {
    t_bunny_connect_response	net_connect;
    t_bunny_connect_response	netconnect _BDEPREC();
  };
  t_bunny_loop			entering_context;
  t_bunny_leaving_context	leaving_context;
  union {
    t_bunny_async_computation_response async_computation;
    t_bunny_async_computation_response async_computation_response _BDEPREC();
  };
  t_bunny_event_response	event;
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
**
**
** Deprecation notice: using bunny_declare_context locally allow you to trick the
** compiler into thinking your functions are taking a void* instead of the real
** type I'm sure it takes. Use bunny_declare_context and t_bunny_context instead.
*/
/**
 * @doc-symbol t_bunny_anonymous_context
 * @doc-module events
 * @doc-kind type
 * @doc-order 540
 * @doc-since 5
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Deprecated untyped variant of t_bunny_context.
 * @description It stores callbacks as void pointers so user callbacks can use a specific data type without casts, but this breaks type safety. Prefer bunny_declare_context with t_bunny_context.
 * @see t_bunny_context, bunny_declare_context
 *
 * @doc-lang fr
 * @brief Variante non typée obsolète de t_bunny_context.
 * @description Elle stocke les callbacks comme des pointeurs void afin que les callbacks utilisateur puissent employer un type de données spécifique sans casts, mais cela casse la sûreté de typage. Préférez bunny_declare_context avec t_bunny_context.
 * @see t_bunny_context, bunny_declare_context
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
  void				*netmessage;
  void				*netconnect;
  void				*entering_context;
  void				*leaving_context;
  void				*async_computation_response;
  void				*event;
}				t_bunny_anonymous_context _BDEPREC();

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

