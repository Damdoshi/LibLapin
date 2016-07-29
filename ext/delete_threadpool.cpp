// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include		"Threads.hpp"
#include		"lapin.h"

void			bunny_delete_threadpool(t_bunny_threadpool		*pol)
{
  delete (hbs::Workers*)pol->_private;
  bunny_free(pol);
}

