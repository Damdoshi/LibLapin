// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// HBSL - Threads - Workers

#ifndef			__WIN32
# include		"Threads.hpp"

bool			hbs::Workers::IsWorking(void) const
{
  return (GetHowManyTasks() != 0);
}

#endif
