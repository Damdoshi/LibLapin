// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
//
// Lapin library

#include	"lapin_private.h"

void		bunny_end(t_bunny_window		**w)
{
  for (size_t i = 0; w[i]; ++i)
    bunny_stop(w[i]);
  bunny_free(w);
}

