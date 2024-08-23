// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Bibliothèque Lapin

#include		<poll.h>
#include		"private/network.hpp"

bool			network::Descriptor::Write(void)
{
  if (outqueue.empty())
    return (true);
  Communication		&next = outqueue.front();
  ssize_t		wt;

  ///

  if (outqueue.empty())
    pollfd->events &= ~POLLOUT;
  return (true);
}
