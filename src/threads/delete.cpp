// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include		"Threads.hpp"
#include		"lapin_private.h"

void			bunny_delete_threadpool(t_bunny_threadpool		*pol)
{
#ifndef         __WIN32
  delete (hbs::Workers*)pol->_private;
#endif
  bunny_free(pol);
  scream_log_if("%p", pol);
}

