// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_subcontext_key
 * @doc-kind function
 * @doc-module context
 * @doc-order 220
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Forwards keyboard key events to the subcontext with $Smain_structure@ as user data.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Returns the subcontext response, or $CGO_ON@ when there is no callback.
 * @see t_bunny_context_runtime_info
 * @see bunny_context_key
 *
 * @doc-lang fr
 * @brief Transmet les événements clavier au sous-contexte avec $Smain_structure@ comme donnée utilisateur.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Renvoie la réponse du sous-contexte, ou $CGO_ON@ quand aucun callback n’est présent.
 * @see t_bunny_context_runtime_info
 * @see bunny_context_key
 */
t_bunny_response	bunny_subcontext_key(t_bunny_event_state	state,
					     t_bunny_keysym		sym,
					     void			*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.key)
    return (x->subcontext.key(state, sym, x->main_structure));
  return (GO_ON);
}

/**
 * @doc
 * @doc-symbol bunny_subcontext_type
 * @doc-kind function
 * @doc-module context
 * @doc-order 221
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Forwards typed Unicode input to the subcontext with $Smain_structure@ as user data.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Returns the subcontext response, or $CGO_ON@ when there is no callback.
 * @see t_bunny_context_runtime_info
 * @see bunny_context_key
 *
 * @doc-lang fr
 * @brief Transmet la saisie Unicode au sous-contexte avec $Smain_structure@ comme donnée utilisateur.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Renvoie la réponse du sous-contexte, ou $CGO_ON@ quand aucun callback n’est présent.
 * @see t_bunny_context_runtime_info
 * @see bunny_context_key
 */
t_bunny_response	bunny_subcontext_type(uint32_t			unicode,
					   void				*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.type)
    return (x->subcontext.type(unicode, x->main_structure));
  return (GO_ON);
}

/**
 * @doc
 * @doc-symbol bunny_subcontext_click
 * @doc-kind function
 * @doc-module context
 * @doc-order 222
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Forwards mouse button events to the subcontext with $Smain_structure@ as user data.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Returns the subcontext response, or $CGO_ON@ when there is no callback.
 * @see t_bunny_context_runtime_info
 * @see bunny_context_key
 *
 * @doc-lang fr
 * @brief Transmet les événements bouton souris au sous-contexte avec $Smain_structure@ comme donnée utilisateur.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Renvoie la réponse du sous-contexte, ou $CGO_ON@ quand aucun callback n’est présent.
 * @see t_bunny_context_runtime_info
 * @see bunny_context_key
 */
t_bunny_response	bunny_subcontext_click(t_bunny_event_state	state,
					       t_bunny_mouse_button	sym,
					       void			*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.button)
    return (x->subcontext.click(state, sym, x->main_structure));
  return (GO_ON);
}

/**
 * @doc
 * @doc-symbol bunny_subcontext_move
 * @doc-kind function
 * @doc-module context
 * @doc-order 223
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Forwards mouse movement events to the subcontext with $Smain_structure@ as user data.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Returns the subcontext response, or $CGO_ON@ when there is no callback.
 * @see t_bunny_context_runtime_info
 * @see bunny_context_key
 *
 * @doc-lang fr
 * @brief Transmet les déplacements souris au sous-contexte avec $Smain_structure@ comme donnée utilisateur.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Renvoie la réponse du sous-contexte, ou $CGO_ON@ quand aucun callback n’est présent.
 * @see t_bunny_context_runtime_info
 * @see bunny_context_key
 */
t_bunny_response	bunny_subcontext_move(const t_bunny_position	*rel,
					      void			*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.move)
    return (x->subcontext.move(rel, x->main_structure));
  return (GO_ON);
}

/**
 * @doc
 * @doc-symbol bunny_subcontext_wheel
 * @doc-kind function
 * @doc-module context
 * @doc-order 224
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Forwards mouse wheel events to the subcontext with $Smain_structure@ as user data.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Returns the subcontext response, or $CGO_ON@ when there is no callback.
 * @see t_bunny_context_runtime_info
 * @see bunny_context_key
 *
 * @doc-lang fr
 * @brief Transmet les événements molette au sous-contexte avec $Smain_structure@ comme donnée utilisateur.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Renvoie la réponse du sous-contexte, ou $CGO_ON@ quand aucun callback n’est présent.
 * @see t_bunny_context_runtime_info
 * @see bunny_context_key
 */
t_bunny_response	bunny_subcontext_wheel(int			wheelid,
					       int			delta,
					       void			*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.wheel)
    return (x->subcontext.wheel(wheelid, delta, x->main_structure));
  return (GO_ON);
}

/**
 * @doc
 * @doc-symbol bunny_subcontext_joy_connect
 * @doc-kind function
 * @doc-module context
 * @doc-order 225
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Forwards joystick connection events to the subcontext with $Smain_structure@ as user data.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Returns the subcontext response, or $CGO_ON@ when there is no callback.
 * @see t_bunny_context_runtime_info
 * @see bunny_context_key
 *
 * @doc-lang fr
 * @brief Transmet les événements de connexion joystick au sous-contexte avec $Smain_structure@ comme donnée utilisateur.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Renvoie la réponse du sous-contexte, ou $CGO_ON@ quand aucun callback n’est présent.
 * @see t_bunny_context_runtime_info
 * @see bunny_context_key
 */
t_bunny_response	bunny_subcontext_joy_connect(t_bunny_event_state state,
						     int		joyid,
						     const t_bunny_joystick *joyinfo,
						     void		*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.connect)
    return (x->subcontext.connect(state, joyid, joyinfo, x->main_structure));
  return (GO_ON);
}

/**
 * @doc
 * @doc-symbol bunny_subcontext_joy_axis
 * @doc-kind function
 * @doc-module context
 * @doc-order 226
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Forwards joystick axis events to the subcontext with $Smain_structure@ as user data.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Returns the subcontext response, or $CGO_ON@ when there is no callback.
 * @see t_bunny_context_runtime_info
 * @see bunny_context_key
 *
 * @doc-lang fr
 * @brief Transmet les axes joystick au sous-contexte avec $Smain_structure@ comme donnée utilisateur.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Renvoie la réponse du sous-contexte, ou $CGO_ON@ quand aucun callback n’est présent.
 * @see t_bunny_context_runtime_info
 * @see bunny_context_key
 */
t_bunny_response	bunny_subcontext_joy_axis(int			joyid,
						  t_bunny_axis		axis,
						  float			value,
						  void			*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.axis)
    return (x->subcontext.axis(joyid, axis, value, x->main_structure));
  return (GO_ON);
}

/**
 * @doc
 * @doc-symbol bunny_subcontext_joy_button
 * @doc-kind function
 * @doc-module context
 * @doc-order 227
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Forwards joystick button events to the subcontext with $Smain_structure@ as user data.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Returns the subcontext response, or $CGO_ON@ when there is no callback.
 * @see t_bunny_context_runtime_info
 * @see bunny_context_key
 *
 * @doc-lang fr
 * @brief Transmet les boutons joystick au sous-contexte avec $Smain_structure@ comme donnée utilisateur.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Renvoie la réponse du sous-contexte, ou $CGO_ON@ quand aucun callback n’est présent.
 * @see t_bunny_context_runtime_info
 * @see bunny_context_key
 */
t_bunny_response	bunny_subcontext_joy_button(t_bunny_event_state state,
						    int			joyid,
						    int			button,
						    void		*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.button)
    return (x->subcontext.button(state, joyid, button, x->main_structure));
  return (GO_ON);
}

/**
 * @doc
 * @doc-symbol bunny_subcontext_get_focus
 * @doc-kind function
 * @doc-module context
 * @doc-order 228
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Forwards window focus-gain events to the subcontext with $Smain_structure@ as user data.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Returns the subcontext response, or $CGO_ON@ when there is no callback.
 * @see t_bunny_context_runtime_info
 * @see bunny_context_key
 *
 * @doc-lang fr
 * @brief Transmet les gains de focus fenêtre au sous-contexte avec $Smain_structure@ comme donnée utilisateur.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Renvoie la réponse du sous-contexte, ou $CGO_ON@ quand aucun callback n’est présent.
 * @see t_bunny_context_runtime_info
 * @see bunny_context_key
 */
t_bunny_response	bunny_subcontext_get_focus(const t_bunny_window *win,
						   void			*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.get_focus)
    return (x->subcontext.get_focus(win, x->main_structure));
  return (GO_ON);
}

/**
 * @doc
 * @doc-symbol bunny_subcontext_lost_focus
 * @doc-kind function
 * @doc-module context
 * @doc-order 229
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Forwards window focus-loss events to the subcontext with $Smain_structure@ as user data.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Returns the subcontext response, or $CGO_ON@ when there is no callback.
 * @see t_bunny_context_runtime_info
 * @see bunny_context_key
 *
 * @doc-lang fr
 * @brief Transmet les pertes de focus fenêtre au sous-contexte avec $Smain_structure@ comme donnée utilisateur.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Renvoie la réponse du sous-contexte, ou $CGO_ON@ quand aucun callback n’est présent.
 * @see t_bunny_context_runtime_info
 * @see bunny_context_key
 */
t_bunny_response	bunny_subcontext_lost_focus(const t_bunny_window *win,
						    void		*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.lost_focus)
    return (x->subcontext.lost_focus(win, x->main_structure));
  return (GO_ON);
}

/**
 * @doc
 * @doc-symbol bunny_subcontext_resize
 * @doc-kind function
 * @doc-module context
 * @doc-order 230
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Forwards window resize events to the subcontext with $Smain_structure@ as user data.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Returns the subcontext response, or $CGO_ON@ when there is no callback.
 * @see t_bunny_context_runtime_info
 * @see bunny_context_key
 *
 * @doc-lang fr
 * @brief Transmet les redimensionnements fenêtre au sous-contexte avec $Smain_structure@ comme donnée utilisateur.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Renvoie la réponse du sous-contexte, ou $CGO_ON@ quand aucun callback n’est présent.
 * @see t_bunny_context_runtime_info
 * @see bunny_context_key
 */
t_bunny_response	bunny_subcontext_resize(const t_bunny_window	*win,
						const t_bunny_position	*siz,
						void			*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.resize)
    return (x->subcontext.resize(win, siz, x->main_structure));
  return (GO_ON);
}

/**
 * @doc
 * @doc-symbol bunny_subcontext_close
 * @doc-kind function
 * @doc-module context
 * @doc-order 231
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Forwards window close events to the subcontext with $Smain_structure@ as user data.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Returns the subcontext response, or $CGO_ON@ when there is no callback.
 * @see t_bunny_context_runtime_info
 * @see bunny_context_key
 *
 * @doc-lang fr
 * @brief Transmet les demandes de fermeture fenêtre au sous-contexte avec $Smain_structure@ comme donnée utilisateur.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Renvoie la réponse du sous-contexte, ou $CGO_ON@ quand aucun callback n’est présent.
 * @see t_bunny_context_runtime_info
 * @see bunny_context_key
 */
t_bunny_response	bunny_subcontext_close(const t_bunny_window	*win,
					       void			*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.close)
    return (x->subcontext.close(win, x->main_structure));
  return (GO_ON);
}

/**
 * @doc
 * @doc-symbol bunny_subcontext_loop
 * @doc-kind function
 * @doc-module context
 * @doc-order 232
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Forwards loop ticks to the subcontext with $Smain_structure@ as user data.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Returns the subcontext response, or $CGO_ON@ when there is no callback.
 * @see t_bunny_context_runtime_info
 * @see bunny_context_key
 *
 * @doc-lang fr
 * @brief Transmet les tours de boucle au sous-contexte avec $Smain_structure@ comme donnée utilisateur.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Renvoie la réponse du sous-contexte, ou $CGO_ON@ quand aucun callback n’est présent.
 * @see t_bunny_context_runtime_info
 * @see bunny_context_key
 */
t_bunny_response	bunny_subcontext_loop(void			*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.loop)
    return (x->subcontext.loop(x->main_structure));
  return (GO_ON);
}

/**
 * @doc
 * @doc-symbol bunny_subcontext_display
 * @doc-kind function
 * @doc-module context
 * @doc-order 233
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Forwards display calls to the subcontext with $Smain_structure@ as user data.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Returns the subcontext response, or $CGO_ON@ when there is no callback.
 * @see t_bunny_context_runtime_info
 * @see bunny_context_key
 *
 * @doc-lang fr
 * @brief Transmet les appels d’affichage au sous-contexte avec $Smain_structure@ comme donnée utilisateur.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Renvoie la réponse du sous-contexte, ou $CGO_ON@ quand aucun callback n’est présent.
 * @see t_bunny_context_runtime_info
 * @see bunny_context_key
 */
t_bunny_response	bunny_subcontext_display(void			*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.display)
    return (x->subcontext.display(x->main_structure));
  return (GO_ON);
}

/**
 * @doc
 * @doc-symbol bunny_subcontext_message
 * @doc-kind function
 * @doc-module context
 * @doc-order 234
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Forwards network message events to the subcontext with $Smain_structure@ as user data.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Returns the subcontext response, or $CGO_ON@ when there is no callback.
 * @see t_bunny_context_runtime_info
 * @see bunny_context_key
 *
 * @doc-lang fr
 * @brief Transmet les messages réseau au sous-contexte avec $Smain_structure@ comme donnée utilisateur.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Renvoie la réponse du sous-contexte, ou $CGO_ON@ quand aucun callback n’est présent.
 * @see t_bunny_context_runtime_info
 * @see bunny_context_key
 */
t_bunny_response	bunny_subcontext_message(t_bunny_network_info	info,
						 void			*buffer,
						 size_t			siz,
						 void			*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.net_message)
    return (x->subcontext.net_message(info, (void*)buffer, siz, x->main_structure));
  return (GO_ON);
}

/**
 * @doc
 * @doc-symbol bunny_subcontext_connect
 * @doc-kind function
 * @doc-module context
 * @doc-order 235
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Forwards network connection events to the subcontext with $Smain_structure@ as user data.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Returns the subcontext response, or $CGO_ON@ when there is no callback.
 * @see t_bunny_context_runtime_info
 * @see bunny_context_key
 *
 * @doc-lang fr
 * @brief Transmet les événements de connexion réseau au sous-contexte avec $Smain_structure@ comme donnée utilisateur.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Renvoie la réponse du sous-contexte, ou $CGO_ON@ quand aucun callback n’est présent.
 * @see t_bunny_context_runtime_info
 * @see bunny_context_key
 */
t_bunny_response	bunny_subcontext_connect(t_bunny_network_info	info,
						 t_bunny_event_state	state,
						 void			*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.net_connect)
    return (x->subcontext.net_connect(info, state, x->main_structure));
  return (GO_ON);
}

/**
 * @doc
 * @doc-symbol bunny_subcontext_entering
 * @doc-kind function
 * @doc-module context
 * @doc-order 236
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Forwards entering-context notifications to the subcontext with $Smain_structure@ as user data.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Returns the subcontext response, or $CGO_ON@ when there is no callback.
 * @see t_bunny_context_runtime_info
 * @see bunny_context_key
 *
 * @doc-lang fr
 * @brief Transmet les notifications d’entrée de contexte au sous-contexte avec $Smain_structure@ comme donnée utilisateur.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Renvoie la réponse du sous-contexte, ou $CGO_ON@ quand aucun callback n’est présent.
 * @see t_bunny_context_runtime_info
 * @see bunny_context_key
 */
t_bunny_response	bunny_subcontext_entering(void			*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.entering_context)
    return (x->subcontext.entering_context(x->main_structure));
  return (GO_ON);
}

/**
 * @doc
 * @doc-symbol bunny_subcontext_leaving
 * @doc-kind function
 * @doc-module context
 * @doc-order 237
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Forwards leaving-context notifications to the subcontext with $Smain_structure@ as user data.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Calls the subcontext leaving callback when present.
 * @see t_bunny_context_runtime_info
 * @see bunny_context_key
 *
 * @doc-lang fr
 * @brief Transmet les notifications de sortie de contexte au sous-contexte avec $Smain_structure@ comme donnée utilisateur.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Appelle le callback de sortie du sous-contexte quand il est présent.
 * @see t_bunny_context_runtime_info
 * @see bunny_context_key
 */
void			bunny_subcontext_leaving(t_bunny_response	res,
						 void			*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.leaving_context)
    x->subcontext.leaving_context(res, x->main_structure);
}

/**
 * @doc
 * @doc-symbol bunny_subcontext_async_computation
 * @doc-kind function
 * @doc-module context
 * @doc-order 238
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Forwards asynchronous computation responses to the subcontext with $Smain_structure@ as user data.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Returns the subcontext response, or $CGO_ON@ when there is no callback.
 * @see t_bunny_context_runtime_info
 * @see bunny_context_key
 *
 * @doc-lang fr
 * @brief Transmet les réponses de calcul asynchrone au sous-contexte avec $Smain_structure@ comme donnée utilisateur.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Renvoie la réponse du sous-contexte, ou $CGO_ON@ quand aucun callback n’est présent.
 * @see t_bunny_context_runtime_info
 * @see bunny_context_key
 */
t_bunny_response	bunny_subcontext_async_computation(void		*cmt,
							   void		*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.async_computation)
    return (x->subcontext.async_computation(cmt, x->main_structure));
  return (GO_ON);
}

/**
 * @doc
 * @doc-symbol bunny_subcontext_event_response
 * @doc-kind function
 * @doc-module context
 * @doc-order 239
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Forwards raw events to the subcontext with $Smain_structure@ as user data.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Returns the subcontext response, or $CGO_ON@ when there is no callback.
 * @see t_bunny_context_runtime_info
 * @see bunny_context_key
 *
 * @doc-lang fr
 * @brief Transmet les événements bruts au sous-contexte avec $Smain_structure@ comme donnée utilisateur.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Renvoie la réponse du sous-contexte, ou $CGO_ON@ quand aucun callback n’est présent.
 * @see t_bunny_context_runtime_info
 * @see bunny_context_key
 */
t_bunny_response	bunny_subcontext_event_response(const t_bunny_event *event,
							void *data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.event)
    return (x->subcontext.event(event, x->main_structure));
  return (GO_ON);
}

