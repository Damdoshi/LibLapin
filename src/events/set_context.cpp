// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin Library

#include		<string.h>
#include		"lapin_private.h"

/**
 * @doc-symbol bunny_set_context
 * @doc-module events
 * @doc-kind function
 * @doc-order 550
 * @doc-since 5
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Replaces the current event callback context.
 * @param context The context to copy into the event callback table.
 * @see t_bunny_context, bunny_get_context
 *
 * @doc-lang fr
 * @brief Remplace le contexte courant de callbacks d'événements.
 * @param context Le contexte à copier dans la table de callbacks d'événements.
 * @see t_bunny_context, bunny_get_context
 */
void			bunny_set_context(const t_bunny_context		*context)
{
  memcpy(&gl_callback, context, sizeof(gl_callback));
}

