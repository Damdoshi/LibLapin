// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2022
//
// Bibliotheque Lapin

#include		"lapin_private.h"

void			bunny_delete_max7219(t_bunny_max7219		*m)
{
  bunny_free(m->pixels);
  bunny_free(m->luminosity);
  bunny_free(m);
}

