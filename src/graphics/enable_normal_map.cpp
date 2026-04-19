// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2026
//
// Bibliothèque Lapin

#include		"lapin_private.h"

extern bool		gl_normal_map;

void			bunny_enable_normal_map(bool			blend)
{
  gl_normal_map = blend;
}

