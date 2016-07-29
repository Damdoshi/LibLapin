// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// HBSL - Threads - Workers

#include		"Threads.hpp"

bool			hbs::Workers::IsWorking(void) const
{
  return (GetHowManyTasks() != 0);
}

