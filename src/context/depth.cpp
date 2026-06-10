// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include			"lapin_private.h"

/**
 * @doc
 * @doc-symbol gl_bunny_depth_context
 * @doc-kind variable
 * @doc-module context
 * @doc-order 710
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Built-in experimental depth-engine context.
 *
 * @doc-lang fr
 * @brief Contexte expérimental intégré de depth engine.
 */
const t_bunny_context		gl_bunny_depth_context =
  {
    bunny_context_key,
    NULL,
    bunny_context_click,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL, //(t_bunny_loop)depth_loop,
    NULL, //(t_bunny_display)depth_display,
    NULL,
    NULL,
    NULL,
    NULL, //(t_bunny_loop)depth_entering,
    NULL, //(t_bunny_leaving_context)depth_leaving,
    NULL,
    NULL
  };
