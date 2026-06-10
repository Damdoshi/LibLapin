// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin Library

#include		<string.h>
#include		"lapin_private.h"

/**
 * @doc-symbol bunny_get_context
 * @doc-module events
 * @doc-kind function
 * @doc-order 560
 * @doc-since 5
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Copies the current event callback context into context.
 * @param context The structure that receives the currently registered callbacks.
 * @see bunny_set_context, t_bunny_context
 *
 * @doc-lang fr
 * @brief Copie le contexte courant de callbacks d'événements dans context.
 * @param context La structure qui reçoit les callbacks actuellement enregistrés.
 * @see bunny_set_context, t_bunny_context
 */
void			bunny_get_context(t_bunny_context		*context)
{
  memcpy(context, &gl_callback, sizeof(*context));
}

