// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

void			bunny_swap(void			**a,
				   void			**b)
{
  void			*c = *a;

  *a = *b;
  *b = c;
}

