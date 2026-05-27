// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2026
// EFRITS SAS 2022-2026
// Pentacle Technologie 2008-2026
//
// Bibliothèque Lapin

#include			<arpa/inet.h>
#include			<string.h>
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

static bool			queue_rudp_control(std::list<network::Communication> &outqueue,
					   struct pollfd			*pollfd,
					   const network::Info		&info,
					   network::ReliableUdpPacketType type,
					   uint32_t			sequence,
					   uint32_t			acknowledge)
{
  network::ReliableUdpHeader	hdr;

  memset(&hdr, 0, sizeof(hdr));
  hdr.magic = htonl(network::RUDP_MAGIC);
  hdr.version = network::RUDP_VERSION;
  hdr.type = type;
  hdr.header_size = htons((uint16_t)sizeof(network::ReliableUdpHeader));
  hdr.sequence = htonl(sequence);
  hdr.acknowledge = htonl(acknowledge);
  try
    {
      outqueue.emplace_back(info, (const char*)&hdr, sizeof(hdr), nullptr, nullptr);
    }
  catch (...)
    {
      return (false);
    }
  pollfd->events |= POLLOUT;
  return (true);
}

static double			heartbeat_delay(const network::ProtoSpec &protocol)
{
  if (protocol.timeout <= 0)
    return (network::RUDP_HEARTBEAT_DELAY);

  double delay = protocol.timeout / 3000.0;

  if (delay < network::RUDP_RESEND_DELAY)
    delay = network::RUDP_RESEND_DELAY;
  if (delay > network::RUDP_HEARTBEAT_DELAY)
    delay = network::RUDP_HEARTBEAT_DELAY;
  return (delay);
}

bool				network::Peer::ReliableUdpTick(double now)
{
  if (protocol.protocol != BP_UDP_RELIABLE)
    return (false);

  double			max_lifetime = protocol.timeout > 0 ? protocol.timeout / 1000.0 : 0;
  bool				queued = false;

  if (max_lifetime > 0 && last_message != 0 && now - last_message >= max_lifetime)
    {
      rudp_pending.clear();
      rudp_pending_heartbeats.clear();
      outqueue.clear();
      doomed = true;
      return (false);
    }

  for (auto it = rudp_pending.begin(); it != rudp_pending.end();)
    {
      ReliableUdpPending	&pending = it->second;

      if ((max_lifetime > 0 && now - pending.first_send >= max_lifetime) ||
	  pending.attempts >= RUDP_MAX_ATTEMPTS)
	{
	  it = rudp_pending.erase(it);
	  doomed = true;
	  continue;
	}
      ++it;
    }

  if (max_lifetime > 0)
    for (auto it = rudp_pending_heartbeats.begin(); it != rudp_pending_heartbeats.end();)
      if (now - it->second >= max_lifetime)
	it = rudp_pending_heartbeats.erase(it);
      else
	++it;

  Descriptor			*desc = pick_descriptor(descriptors);
  if (desc != NULL)
    {
      double delay = heartbeat_delay(protocol);

      if (now - rudp_last_heartbeat >= delay && rudp_pending_heartbeats.empty())
	{
	  uint32_t sequence = rudp_next_heartbeat_sequence++;

	  if (queue_rudp_control(desc->outqueue, desc->pollfd, info, RUDP_HEARTBEAT, sequence, 0))
	    {
	      rudp_pending_heartbeats[sequence] = now;
	      rudp_last_heartbeat = now;
	      queued = true;
	    }
	}
    }

  if (!protocol.resend)
    return (queued);
  if (desc == NULL)
    return (queued);

  for (auto it = rudp_pending.begin(); it != rudp_pending.end(); ++it)
    {
      ReliableUdpPending	&pending = it->second;

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
