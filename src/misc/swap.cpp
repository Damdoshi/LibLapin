// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

void			bunny_swap(void			**a,
				   void			**b)
{
  void			*c = *a;

  *a = *b;
  *b = c;
  scream_log_if("%p first_elem, %p second_elem", "misc", a, b);
}

