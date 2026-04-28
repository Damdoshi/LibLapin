// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2026
// EFRITS SAS 2022-2026
// Pentacle Technologie 2008-2026
//
// Bibliothèque Lapin

#include			"lapin.h"
#include			"private/network/network.hpp"
#include			"private/network/reliable_udp.hpp"

static network::Descriptor	*pick_descriptor(std::set<network::Descriptor*> &descriptors)
{
  if (!descriptors.size())
    return (NULL);
  auto				it = descriptors.begin();
  size_t			max = rand() % descriptors.size();

  for (size_t i = 0; i < max; ++i)
    ++it;
  return (*it);
}

bool				network::Peer::ReliableUdpTick(double now)
{
  if (protocol.protocol != BP_UDP_RELIABLE)
    return (false);
  if (!protocol.resend)
    return (false);
  Descriptor			*desc = pick_descriptor(descriptors);
  if (desc == NULL)
    return (false);

  bool				queued = false;
  for (auto it = rudp_pending.begin(); it != rudp_pending.end(); ++it)
    {
      ReliableUdpPending	&pending = it->second;

      if (pending.attempts >= RUDP_MAX_ATTEMPTS)
	continue;
      if (pending.last_send != 0 && now - pending.last_send < RUDP_RESEND_DELAY)
	continue;
      try
	{
	  desc->outqueue.emplace_back(info, pending.packet.data(), pending.packet.size(), nullptr, nullptr);
	}
      catch (...)
	{
	  return (queued);
	}
      desc->pollfd->events |= POLLOUT;
      pending.last_send = now;
      pending.attempts += 1;
      queued = true;
    }
  return (queued);
}

bool				network::Peer::TransfertWriteRequest(void)
{
  Descriptor			*desc = pick_descriptor(descriptors);

  if (desc == NULL)
    return (false);
  network::WriteRequest		&wr = outqueue.front();
  bool				result;

  if ((result = desc->SetMessage(wr.data.data(), wr.data.size(), info, protocol, wr.wt, wr.wtdata)))
    outqueue.pop_front();
  return (result);
}
