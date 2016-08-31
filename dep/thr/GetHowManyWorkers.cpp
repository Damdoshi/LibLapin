// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// HBSL - Threads - Workers

#ifndef			__WIN32
# include		"Threads.hpp"

size_t			hbs::Workers::GetHowManyWorkers(void) const
{
  return (nbr_worker);
}

#endif

