// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Bibliothèque Lapin

#include		<errno.h>
#include		<poll.h>
#include		<sys/socket.h>
#include		"lapin.h"
#include		"private/network/network.hpp"

///////IL FAUDRAIT POP LA WRITE REQUEST DE PEER SEULEMENT UNE FOIS QUE DESCRIPTOR A BIEN*
////// TOUT ECRIT

static bool		queue_write_error(std::list<network::Communication> &inqueue,
					  const network::Info		     &info,
					  int				     err)
{
  try
    {
      inqueue.emplace_back(BCT_SENDTO_ERROR, err);
      inqueue.back().info = info;
    }
  catch (...)
    {
      return (false);
    }
  return (true);
}

bool			network::Descriptor::Write(void)
{
  // Simple vérification de cohérence
  if (outqueue.empty())
    return (true);

  // L'écriture
  Communication		&next = outqueue.front();
  ssize_t		len;
  const char		*data = next.size ? &next.data[wcursor] : "";
  size_t		remaining = next.size - wcursor;

  if (istcp(protocol))
    len = send(fd, data, remaining, 0);
  else
    len = sendto
      (fd,
       data,
       remaining,
       0,
       (const struct sockaddr*)&next.info.sockaddr,
       next.info.socklen
       );
  if (len == -1)
    {
      if (errno == EINTR || errno == EAGAIN || errno == EWOULDBLOCK)
	return (true);
      queue_write_error(inqueue, next.info, errno);
      outqueue.clear();
      wcursor = 0;
      Doom();
      return (false);
    }

  // Si tout est écrit.
  wcursor += len;
  if (next.size == wcursor)
    {
      if (next.wt != NULL)
	next.wt(*(t_bunny_network_info*)&next.info, next.wtdata);
      outqueue.pop_front();
      wcursor = 0;
    }
  if (outqueue.empty())
    pollfd->events &= ~POLLOUT;
  return (true);
}

