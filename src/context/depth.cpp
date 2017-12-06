// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include			"lapin_private.h"

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
    (t_bunny_loop)depth_loop,
    (t_bunny_display)depth_display,
    NULL,
    NULL,
    NULL,
    NULL,
    (t_bunny_loop)depth_entering,
    (t_bunny_leaving_context)depth_leaving
  };
