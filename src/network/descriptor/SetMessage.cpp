// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2026
// EFRITS SAS 2022-2026
// Pentacle Technologie 2008-2026
//
// Bibliothèque Lapin

#include	<limits.h>
#include	<arpa/inet.h>
#include	"lapin.h"
#include	"private/network/network.hpp"
#include	"private/network/reliable_udp.hpp"

bool		network::Descriptor::SetMessage(const char	*data,
						size_t		len,
						const Info	&info,
						const ProtoSpec &specs,
						t_bunny_written wt,
						void		*wtdata)
{
  if (len > specs.size && specs.size != 0)
    return (false);
  try {
    if (specs.protocol == BP_UDP_RELIABLE)
      {
	auto it = network->peers.find(info);

	if (it == network->peers.end())
	  return (false);
	if (len > UINT32_MAX)
	  return (false);

	Peer &peer = it->second;
	if (peer.rudp_pending.size() >= RUDP_SEND_WINDOW)
	  return (false);
	const uint32_t sequence = peer.rudp_next_sequence++;
	const size_t total = sizeof(ReliableUdpHeader) + len;
	Peer::ReliableUdpPending pending;

	pending.sequence = sequence;
	pending.packet.resize(total);
	pending.last_send = bunny_get_time() / 1e9;
	pending.attempts = 1;
	pending.wt = wt;
	pending.wtdata = wtdata;

	ReliableUdpHeader *hdr = (ReliableUdpHeader*)pending.packet.data();
	memset(hdr, 0, sizeof(*hdr));
	hdr->magic = htonl(RUDP_MAGIC);
	hdr->version = RUDP_VERSION;
	hdr->type = RUDP_DATA;
	hdr->header_size = htons((uint16_t)sizeof(ReliableUdpHeader));
	hdr->sequence = htonl(sequence);
	hdr->acknowledge = 0;
	hdr->payload_size = htonl((uint32_t)len);
	if (len)
	  memcpy(&pending.packet[sizeof(ReliableUdpHeader)], data, len);

	outqueue.emplace_back(info, pending.packet.data(), pending.packet.size(), nullptr, nullptr);
	peer.rudp_pending[sequence] = std::move(pending);
      }
    else if (specs.protocol == BP_UDP_IMMEDIATE)
      outqueue.emplace_back(info, data, len, wt, wtdata);
    else if (specs.protocol == BP_TCP_FIXED_SIZE)
      {
	if (specs.size == len)
	  outqueue.emplace_back(info, data, len, wt, wtdata);
	else
	  {
	    outqueue.emplace_back(info, specs.size, wt, wtdata);
	    memcpy(outqueue.back().data, data, len);
	    memset(&outqueue.back().data[len], 0, specs.size - len);
	  }
      }
    else if (specs.protocol == BP_TCP_SIZED_PLUS_DATA)
      {
	struct size_plus_data *spd = NULL;

	if (len > UINT32_MAX)
	  return (false);
	outqueue.emplace_back(info, len + sizeof(spd->size), wt, wtdata);
	spd = (struct size_plus_data*)outqueue.back().data;
	spd->size = len;
	memcpy(spd->data, data, len);
      }
    else // BP_TCP_TERMINATED_DATA
      {
	outqueue.emplace_back(info, len + sizeof(specs.terminator), wt, wtdata);
	memcpy(outqueue.back().data, data, len);
	memcpy(&outqueue.back().data[len], &specs.terminator, sizeof(specs.terminator));
      }
    pollfd->events |= POLLOUT;
  } catch (...) {
    return (false);
  }
  return (true);
}
