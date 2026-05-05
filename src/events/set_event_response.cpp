// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

/**
 * @doc-symbol bunny_set_event_response
 * @doc-module events
 * @doc-kind function
 * @doc-order 457
 * @doc-since 12
 * @doc-until latest
 * @doc-level expert
 *
 * @doc-lang en
 * @brief Registers the generic raw event callback.
 * @param resp The callback to call.
 * @see t_bunny_event_response, t_bunny_event
 *
 * @doc-lang fr
 * @brief Enregistre le callback générique d'événement brut.
 * @param resp Le callback à appeler.
 * @see t_bunny_event_response, t_bunny_event
 */
void			bunny_set_event_response(t_bunny_event_response	evt)
{
  gl_callback.event = evt;
}

