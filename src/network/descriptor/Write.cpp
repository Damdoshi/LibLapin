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
  // Simple vérification de cohérence
  if (outqueue.empty())
    return (true);
  if (outqueue.front().datas.size() == wcursor)
    {
      outqueue.pop_front();
      wcursor = 0;
    }
  if (outqueue.empty())
    return (true);

  // L'écriture
  Communication		&next = outqueue.front();
  ssize_t		len;

  if ((len = sendto
       (fd,
	&next.datas[wcursor],
	next.datas.size() - wcursor,
	0,
	(const struct sockaddr*)&next.info.sockaddr,
	next.info.socklen
	)) == -1)
    return (false);

  // Si tout est écrit.
  wcursor += len;
  if (outqueue.front().datas.size() == wcursor)
    {
      outqueue.pop_front();
      wcursor = 0;
    }
  if (outqueue.empty())
    pollfd->events &= ~POLLOUT;
  return (true);
}

