// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include		"Threads.hpp"
#include		"lapin.h"

void			bunny_delete_threadpool(t_bunny_threadpool		*pol)
{
#ifndef         __WIN32
  delete (hbs::Workers*)pol->_private;
#endif // __WIN32
  bunny_free(pol);
}

