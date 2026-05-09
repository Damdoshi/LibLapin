// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_context_key
 * @doc-kind function
 * @doc-module context
 * @doc-order 120
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Forwards keyboard key events to the subcontext.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Returns the subcontext response, or $CGO_ON@ when there is no callback.
 * @see t_bunny_context_runtime_info
 *
 * @doc-lang fr
 * @brief Transmet les événements clavier au sous-contexte.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Renvoie la réponse du sous-contexte, ou $CGO_ON@ quand aucun callback n’est présent.
 * @see t_bunny_context_runtime_info
 */
t_bunny_response	bunny_context_key(t_bunny_event_state	state,
					  t_bunny_keysym	sym,
					  void			*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.key)
    return (x->subcontext.key(state, sym, data));
  return (GO_ON);
}

/**
 * @doc
 * @doc-symbol bunny_context_type
 * @doc-kind function
 * @doc-module context
 * @doc-order 121
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Forwards typed Unicode input to the subcontext.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Returns the subcontext response, or $CGO_ON@ when there is no callback.
 * @see t_bunny_context_runtime_info
 *
 * @doc-lang fr
 * @brief Transmet la saisie Unicode au sous-contexte.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Renvoie la réponse du sous-contexte, ou $CGO_ON@ quand aucun callback n’est présent.
 * @see t_bunny_context_runtime_info
 */
t_bunny_response	bunny_context_type(uint32_t		unicode,
					   void			*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.type)
    return (x->subcontext.type(unicode, data));
  return (GO_ON);
}

/**
 * @doc
 * @doc-symbol bunny_context_click
 * @doc-kind function
 * @doc-module context
 * @doc-order 122
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Forwards mouse button events to the subcontext.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Returns the subcontext response, or $CGO_ON@ when there is no callback.
 * @see t_bunny_context_runtime_info
 *
 * @doc-lang fr
 * @brief Transmet les événements bouton souris au sous-contexte.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Renvoie la réponse du sous-contexte, ou $CGO_ON@ quand aucun callback n’est présent.
 * @see t_bunny_context_runtime_info
 */
t_bunny_response	bunny_context_click(t_bunny_event_state	state,
					    t_bunny_mouse_button sym,
					    void		*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.button)
    return (x->subcontext.click(state, sym, data));
  return (GO_ON);
}

/**
 * @doc
 * @doc-symbol bunny_context_move
 * @doc-kind function
 * @doc-module context
 * @doc-order 123
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Forwards mouse movement events to the subcontext.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Returns the subcontext response, or $CGO_ON@ when there is no callback.
 * @see t_bunny_context_runtime_info
 *
 * @doc-lang fr
 * @brief Transmet les déplacements souris au sous-contexte.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Renvoie la réponse du sous-contexte, ou $CGO_ON@ quand aucun callback n’est présent.
 * @see t_bunny_context_runtime_info
 */
t_bunny_response	bunny_context_move(const t_bunny_position *rel,
					   void			*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.move)
    return (x->subcontext.move(rel, data));
  return (GO_ON);
}

/**
 * @doc
 * @doc-symbol bunny_context_wheel
 * @doc-kind function
 * @doc-module context
 * @doc-order 124
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Forwards mouse wheel events to the subcontext.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Returns the subcontext response, or $CGO_ON@ when there is no callback.
 * @see t_bunny_context_runtime_info
 *
 * @doc-lang fr
 * @brief Transmet les événements molette au sous-contexte.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Renvoie la réponse du sous-contexte, ou $CGO_ON@ quand aucun callback n’est présent.
 * @see t_bunny_context_runtime_info
 */
t_bunny_response	bunny_context_wheel(int			wheelid,
					    int			delta,
					    void		*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.wheel)
    return (x->subcontext.wheel(wheelid, delta, data));
  return (GO_ON);
}

/**
 * @doc
 * @doc-symbol bunny_context_joy_connect
 * @doc-kind function
 * @doc-module context
 * @doc-order 125
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Forwards joystick connection events to the subcontext.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Returns the subcontext response, or $CGO_ON@ when there is no callback.
 * @see t_bunny_context_runtime_info
 *
 * @doc-lang fr
 * @brief Transmet les événements de connexion joystick au sous-contexte.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Renvoie la réponse du sous-contexte, ou $CGO_ON@ quand aucun callback n’est présent.
 * @see t_bunny_context_runtime_info
 */
t_bunny_response	bunny_context_joy_connect(t_bunny_event_state	state,
						  int		joyid,
						  const t_bunny_joystick *joyinfo,
						  void		*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.connect)
    return (x->subcontext.connect(state, joyid, joyinfo, data));
  return (GO_ON);
}

/**
 * @doc
 * @doc-symbol bunny_context_joy_axis
 * @doc-kind function
 * @doc-module context
 * @doc-order 126
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Forwards joystick axis events to the subcontext.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Returns the subcontext response, or $CGO_ON@ when there is no callback.
 * @see t_bunny_context_runtime_info
 *
 * @doc-lang fr
 * @brief Transmet les axes joystick au sous-contexte.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Renvoie la réponse du sous-contexte, ou $CGO_ON@ quand aucun callback n’est présent.
 * @see t_bunny_context_runtime_info
 */
t_bunny_response	bunny_context_joy_axis(int		joyid,
					       t_bunny_axis	axis,
					       float		value,
					       void		*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.axis)
    return (x->subcontext.axis(joyid, axis, value, data));
  return (GO_ON);
}

/**
 * @doc
 * @doc-symbol bunny_context_joy_button
 * @doc-kind function
 * @doc-module context
 * @doc-order 127
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Forwards joystick button events to the subcontext.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Returns the subcontext response, or $CGO_ON@ when there is no callback.
 * @see t_bunny_context_runtime_info
 *
 * @doc-lang fr
 * @brief Transmet les boutons joystick au sous-contexte.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Renvoie la réponse du sous-contexte, ou $CGO_ON@ quand aucun callback n’est présent.
 * @see t_bunny_context_runtime_info
 */
t_bunny_response	bunny_context_joy_button(t_bunny_event_state state,
						 int		joyid,
						 int		button,
						 void		*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.button)
    return (x->subcontext.button(state, joyid, button, data));
  return (GO_ON);
}

/**
 * @doc
 * @doc-symbol bunny_context_get_focus
 * @doc-kind function
 * @doc-module context
 * @doc-order 128
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Forwards window focus-gain events to the subcontext.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Returns the subcontext response, or $CGO_ON@ when there is no callback.
 * @see t_bunny_context_runtime_info
 *
 * @doc-lang fr
 * @brief Transmet les gains de focus fenêtre au sous-contexte.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Renvoie la réponse du sous-contexte, ou $CGO_ON@ quand aucun callback n’est présent.
 * @see t_bunny_context_runtime_info
 */
t_bunny_response	bunny_context_get_focus(const t_bunny_window *win,
						void		*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.get_focus)
    return (x->subcontext.get_focus(win, data));
  return (GO_ON);
}

/**
 * @doc
 * @doc-symbol bunny_context_lost_focus
 * @doc-kind function
 * @doc-module context
 * @doc-order 129
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Forwards window focus-loss events to the subcontext.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Returns the subcontext response, or $CGO_ON@ when there is no callback.
 * @see t_bunny_context_runtime_info
 *
 * @doc-lang fr
 * @brief Transmet les pertes de focus fenêtre au sous-contexte.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Renvoie la réponse du sous-contexte, ou $CGO_ON@ quand aucun callback n’est présent.
 * @see t_bunny_context_runtime_info
 */
t_bunny_response	bunny_context_lost_focus(const t_bunny_window *win,
						 void		*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.lost_focus)
    return (x->subcontext.lost_focus(win, data));
  return (GO_ON);
}

/**
 * @doc
 * @doc-symbol bunny_context_resize
 * @doc-kind function
 * @doc-module context
 * @doc-order 130
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Forwards window resize events to the subcontext.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Returns the subcontext response, or $CGO_ON@ when there is no callback.
 * @see t_bunny_context_runtime_info
 *
 * @doc-lang fr
 * @brief Transmet les redimensionnements fenêtre au sous-contexte.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Renvoie la réponse du sous-contexte, ou $CGO_ON@ quand aucun callback n’est présent.
 * @see t_bunny_context_runtime_info
 */
t_bunny_response	bunny_context_resize(const t_bunny_window *win,
					     const t_bunny_position *siz,
					     void		*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.resize)
    return (x->subcontext.resize(win, siz, data));
  return (GO_ON);
}

/**
 * @doc
 * @doc-symbol bunny_context_close
 * @doc-kind function
 * @doc-module context
 * @doc-order 131
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Forwards window close events to the subcontext.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Returns the subcontext response, or $CGO_ON@ when there is no callback.
 * @see t_bunny_context_runtime_info
 *
 * @doc-lang fr
 * @brief Transmet les demandes de fermeture fenêtre au sous-contexte.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Renvoie la réponse du sous-contexte, ou $CGO_ON@ quand aucun callback n’est présent.
 * @see t_bunny_context_runtime_info
 */
t_bunny_response	bunny_context_close(const t_bunny_window *win,
					    void		*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.close)
    return (x->subcontext.close(win, data));
  return (GO_ON);
}

/**
 * @doc
 * @doc-symbol bunny_context_loop
 * @doc-kind function
 * @doc-module context
 * @doc-order 132
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Forwards loop ticks to the subcontext.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Returns the subcontext response, or $CGO_ON@ when there is no callback.
 * @see t_bunny_context_runtime_info
 *
 * @doc-lang fr
 * @brief Transmet les tours de boucle au sous-contexte.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Renvoie la réponse du sous-contexte, ou $CGO_ON@ quand aucun callback n’est présent.
 * @see t_bunny_context_runtime_info
 */
t_bunny_response	bunny_context_loop(void			*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.loop)
    return (x->subcontext.loop(data));
  return (GO_ON);
}

/**
 * @doc
 * @doc-symbol bunny_context_display
 * @doc-kind function
 * @doc-module context
 * @doc-order 133
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Forwards display calls to the subcontext.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Returns the subcontext response, or $CGO_ON@ when there is no callback.
 * @see t_bunny_context_runtime_info
 *
 * @doc-lang fr
 * @brief Transmet les appels d’affichage au sous-contexte.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Renvoie la réponse du sous-contexte, ou $CGO_ON@ quand aucun callback n’est présent.
 * @see t_bunny_context_runtime_info
 */
t_bunny_response	bunny_context_display(void		*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.display)
    return (x->subcontext.display(data));
  return (GO_ON);
}

/**
 * @doc
 * @doc-symbol bunny_context_message
 * @doc-kind function
 * @doc-module context
 * @doc-order 134
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Forwards network message events to the subcontext.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Returns the subcontext response, or $CGO_ON@ when there is no callback.
 * @see t_bunny_context_runtime_info
 *
 * @doc-lang fr
 * @brief Transmet les messages réseau au sous-contexte.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Renvoie la réponse du sous-contexte, ou $CGO_ON@ quand aucun callback n’est présent.
 * @see t_bunny_context_runtime_info
 */
t_bunny_response	bunny_context_message(t_bunny_network_info info,
					      void		*buffer,
					      size_t		siz,
					      void		*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.net_message)
    return (x->subcontext.net_message(info, (void*)buffer, siz, data));
  return (GO_ON);
}

/**
 * @doc
 * @doc-symbol bunny_context_connect
 * @doc-kind function
 * @doc-module context
 * @doc-order 135
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Forwards network connection events to the subcontext.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Returns the subcontext response, or $CGO_ON@ when there is no callback.
 * @see t_bunny_context_runtime_info
 *
 * @doc-lang fr
 * @brief Transmet les événements de connexion réseau au sous-contexte.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Renvoie la réponse du sous-contexte, ou $CGO_ON@ quand aucun callback n’est présent.
 * @see t_bunny_context_runtime_info
 */
t_bunny_response	bunny_context_connect(t_bunny_network_info info,
					      t_bunny_event_state state,
					      void		*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.net_connect)
    return (x->subcontext.net_connect(info, state, data));
  return (GO_ON);
}

/**
 * @doc
 * @doc-symbol bunny_context_entering
 * @doc-kind function
 * @doc-module context
 * @doc-order 136
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Forwards entering-context notifications to the subcontext.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Returns the subcontext response, or $CGO_ON@ when there is no callback.
 * @see t_bunny_context_runtime_info
 *
 * @doc-lang fr
 * @brief Transmet les notifications d’entrée de contexte au sous-contexte.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Renvoie la réponse du sous-contexte, ou $CGO_ON@ quand aucun callback n’est présent.
 * @see t_bunny_context_runtime_info
 */
t_bunny_response	bunny_context_entering(void		*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.entering_context)
    return (x->subcontext.entering_context(data));
  return (GO_ON);
}

/**
 * @doc
 * @doc-symbol bunny_context_leaving
 * @doc-kind function
 * @doc-module context
 * @doc-order 137
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Forwards leaving-context notifications to the subcontext.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Calls the subcontext leaving callback when present.
 * @see t_bunny_context_runtime_info
 *
 * @doc-lang fr
 * @brief Transmet les notifications de sortie de contexte au sous-contexte.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Appelle le callback de sortie du sous-contexte quand il est présent.
 * @see t_bunny_context_runtime_info
 */
void			bunny_context_leaving(t_bunny_response	res,
					      void		*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.leaving_context)
    x->subcontext.leaving_context(res, data);
}

/**
 * @doc
 * @doc-symbol bunny_context_async_computation
 * @doc-kind function
 * @doc-module context
 * @doc-order 138
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Forwards asynchronous computation responses to the subcontext.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Returns the subcontext response, or $CGO_ON@ when there is no callback.
 * @see t_bunny_context_runtime_info
 *
 * @doc-lang fr
 * @brief Transmet les réponses de calcul asynchrone au sous-contexte.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Renvoie la réponse du sous-contexte, ou $CGO_ON@ quand aucun callback n’est présent.
 * @see t_bunny_context_runtime_info
 */
t_bunny_response	bunny_context_async_computation(void	*cmt,
							void	*data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.async_computation)
    return (x->subcontext.async_computation(cmt, data));
  return (GO_ON);
}

/**
 * @doc
 * @doc-symbol bunny_context_event_response
 * @doc-kind function
 * @doc-module context
 * @doc-order 139
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Forwards raw events to the subcontext.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Returns the subcontext response, or $CGO_ON@ when there is no callback.
 * @see t_bunny_context_runtime_info
 *
 * @doc-lang fr
 * @brief Transmet les événements bruts au sous-contexte.
 * @param data Pointer to a $Tt_bunny_context_runtime_info@.
 * @return-success Renvoie la réponse du sous-contexte, ou $CGO_ON@ quand aucun callback n’est présent.
 * @see t_bunny_context_runtime_info
 */
t_bunny_response	bunny_context_event_response(const t_bunny_event *event,
						     void *data)
{
  t_bunny_context_runtime_info *x = (t_bunny_context_runtime_info*)data;

  if (x->subcontext.event)
    return (x->subcontext.event(event, data));
  return (GO_ON);
}

