// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

/**
 * @doc-symbol bunny_set_async_computation_response
 * @doc-module events
 * @doc-kind function
 * @doc-order 527
 * @doc-since 12
 * @doc-until latest
 * @doc-level expert
 *
 * @doc-lang en
 * @brief Registers the callback called when an asynchronous computation completes.
 * @param func The callback to call.
 * @see t_bunny_async_computation_response, bunny_async_computation
 *
 * @doc-lang fr
 * @brief Enregistre le callback appelé lorsqu'un calcul asynchrone se termine.
 * @param func Le callback à appeler.
 * @see t_bunny_async_computation_response, bunny_async_computation
 */
void			bunny_set_async_computation_response(t_bunny_async_computation_response func)
{
  gl_callback.async_computation = func;
}

