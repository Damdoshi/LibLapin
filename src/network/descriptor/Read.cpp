// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2026
// EFRITS SAS 2022-2026
// Pentacle Technologie 2008-2026
//
// Bibliothèque Lapin

#include        <poll.h>
#include        <arpa/inet.h>
#include        <stdlib.h>
#include        "lapin.h"
#include        "private/network/network.hpp"
#include        "private/network/reliable_udp.hpp"

static bool     should_drop_once(const char *envname, uint32_t sequence, std::set<uint32_t> &already)
{
  const char    *env = getenv(envname);
  int           mod;

  if (env == NULL || *env == 0)
    return (false);
  mod = atoi(env);
  if (mod <= 0)
    return (false);
  if ((sequence % (uint32_t)mod) != 0)
    return (false);
  if (already.find(sequence) != already.end())
    return (false);
  already.insert(sequence);
  return (true);
}

static bool     queue_rudp_ack(std::list<network::Communication> &outqueue,
                                struct pollfd *pollfd,
                                const network::Info &rinfo,
                                uint32_t sequence)
{
  network::ReliableUdpHeader ack;

  memset(&ack, 0, sizeof(ack));
  ack.magic = htonl(network::RUDP_MAGIC);
  ack.version = network::RUDP_VERSION;
  ack.type = network::RUDP_ACK;
  ack.header_size = htons((uint16_t)sizeof(network::ReliableUdpHeader));
  ack.acknowledge = htonl(sequence);
  try
    {
      outqueue.emplace_back(rinfo, (const char*)&ack, sizeof(ack), nullptr, nullptr);
    }
  catch (...)
    {
      return (false);
    }
  pollfd->events |= POLLOUT;
  return (true);
}

bool            network::Descriptor::Read(void)
{
  ProtoSpec     specs{protocol};
  ssize_t       len;
  Info          rinfo;

  // Si le buffer n'est pas établi, on l'établi. Si ca ne marche pas, on re essayera la prochaine fois
  if (inbuffer_size == 0)
    {
      size_t read_size = specs.size;

      // BP_UDP_RELIABLE expose specs.size comme taille utile maximale.
      // Sur le fil, le datagramme contient en plus l'en-tête RUDP interne.
      if (specs.protocol == BP_UDP_RELIABLE)
        read_size += sizeof(ReliableUdpHeader);
      if ((inbuffer = (char*)bunny_malloc(read_size)) == NULL)
        return (false);
      spdbuffer = (struct size_plus_data*)inbuffer;
      inbuffer_size = read_size; // Default len
    }

  // Si il reste de la place dans le buffer, on lit, sinon on indique qu'on a rien lu
  if (inbuffer_size - rcursor > 0)
    {
      rinfo.socklen = sizeof(rinfo.sockaddr);
      if ((len = recvfrom
           (fd,
            &inbuffer[rcursor],
            inbuffer_size - rcursor,
            0,
            (struct sockaddr*)&rinfo.sockaddr,
            &rinfo.socklen
            )) == -1)
        return (false);

      // On regarde si le pair dont on a recu un message est deja present
      auto it = network->peers.find(rinfo);
      if (it == network->peers.end())
        // On indique qu'il y a un nouveau pair
        inqueue.emplace_back(rinfo, true);

      // Création eventuelle du nouveau pair - ou récupération de l'existant
      auto &peer = network->peers[rinfo];

      // Récupération du protocole du pair
      specs = peer.protocol;
      if (!specs)
        specs = protocol;

      // La connexion est perdue
      if (len == 0 && istcp(specs.protocol))
        {
          // Préviens la déconnexion d'un client
          inqueue.emplace_back(rinfo, false);
          return (Close());
        }

      // On ajoute le pair au descripteur si ce n'est pas deja fait
      if (peer.descriptors.find(this) == peer.descriptors.end())
        if (peer.AttachDescriptor(*this, specs, &rinfo) == false && peer.descriptors.size() == 0)
          network->peers.erase(rinfo);

      // Purement indicatif - non exploité actuellement
      peer.last_message = bunny_get_time() / 1e9;
    }
  else
    len = 0;

  if (specs.protocol == BP_UDP_RELIABLE)
    {
      auto it = network->peers.find(rinfo);

      if (it == network->peers.end())
        return (false);
      if ((size_t)len < sizeof(ReliableUdpHeader))
        return (true);

      ReliableUdpHeader *hdr = (ReliableUdpHeader*)inbuffer;
      uint32_t magic = ntohl(hdr->magic);
      uint16_t header_size = ntohs(hdr->header_size);
      uint32_t sequence = ntohl(hdr->sequence);
      uint32_t acknowledge = ntohl(hdr->acknowledge);
      uint32_t payload_size = ntohl(hdr->payload_size);
      Peer &peer = it->second;

      if (magic != RUDP_MAGIC || hdr->version != RUDP_VERSION || header_size < sizeof(ReliableUdpHeader))
        return (true);
      if ((size_t)len < (size_t)header_size || payload_size > (size_t)len - header_size)
        return (true);

      if (hdr->type == RUDP_ACK)
        {
          if (should_drop_once("LIBLAPIN_RUDP_DROP_ACK_MOD", acknowledge, peer.rudp_test_dropped_ack_sequences))
            return (true);
          auto pit = peer.rudp_pending.find(acknowledge);
          if (pit != peer.rudp_pending.end())
            {
              if (pit->second.wt != NULL)
                pit->second.wt(*(t_bunny_network_info*)&rinfo, pit->second.wtdata);
              peer.rudp_pending.erase(pit);
            }
          return (true);
        }

      if (hdr->type != RUDP_DATA)
        return (true);

      // Test hook volontairement privé: simule une perte avant ACK et avant livraison.
      // La retransmission doit donc réparer le trou.
      if (should_drop_once("LIBLAPIN_RUDP_DROP_DATA_MOD", sequence, peer.rudp_test_dropped_data_sequences))
        return (true);

      if (queue_rudp_ack(outqueue, pollfd, rinfo, sequence) == false)
        return (false);

      if (sequence < peer.rudp_next_expected_sequence)
        return (true);

      if (peer.rudp_received_buffer.find(sequence) == peer.rudp_received_buffer.end())
        peer.rudp_received_buffer[sequence] = std::vector<char>(&inbuffer[header_size], &inbuffer[header_size] + payload_size);

      while (true)
        {
          auto bit = peer.rudp_received_buffer.find(peer.rudp_next_expected_sequence);
          if (bit == peer.rudp_received_buffer.end())
            break;
          try
            {
              inqueue.emplace_back(rinfo, bit->second.size());
            }
          catch (...)
            {
              return (false);
            }
          if (bit->second.size())
            memcpy(inqueue.back().data, bit->second.data(), bit->second.size());
          peer.rudp_has_received_sequence = true;
          peer.rudp_last_received_sequence = peer.rudp_next_expected_sequence;
          peer.rudp_received_buffer.erase(bit);
          peer.rudp_next_expected_sequence += 1;
        }
      rcursor = 0;
      return (true);
    }

  // UDP ou TCP IMMEDIATE
  if (isimmediate(specs.protocol))
    {
      // Aucun traitement n'est à faire ici: on a ce qu'on veut
      // On fait l'ajout, même si len est vide, car on
      // peut recevoir un datagramme de longueur 0.
      return (ShiftInBuffer(rinfo, specs, len));
    }

  /// TCP
  if (specs.protocol == BP_TCP_FIXED_SIZE)
    {
      // Normalement, on ne peut pas dépasser inbufer.size()
      // Car la lecture dans le buffer est conditionné à cette taille
      if (len + rcursor == inbuffer_size)
        return (ShiftInBuffer(rinfo, specs));
      rcursor += len;
    }

  /// TCP
  if (specs.protocol == BP_TCP_SIZED_PLUS_DATA)
    {
      size_t total;

      rcursor += len;
      // Si on a pas encore recu toute la taille, on ne fait rien, on l'attend
      if (rcursor < sizeof(spdbuffer->size))
        return (true);
      // Infraction au protocole
      if (spdbuffer->size > specs.size)
        {
          Close();
          return (false);
        }
      total = spdbuffer->size + sizeof(spdbuffer->size);
      // Si le buffer ne permet pas d'enregistrer le paquet entier, on augmente sa taille
      if (total > inbuffer_size)
        {
          char *tmp;

          if ((tmp = (char*)bunny_realloc(inbuffer, total)) == NULL)
            return (false);
          while (inbuffer_size < total)
            tmp[inbuffer_size++] = 0;
          inbuffer = tmp;
          spdbuffer = (struct size_plus_data*)inbuffer;
        }
      // Au cas où l'on ai recu plusieurs paquets d'un coup
      // ce que la LibLapin ne fait *pas* - donc en face,
      while (rcursor >= (total = spdbuffer->size + sizeof(spdbuffer->size)))
        if (ExtractFromInBuffer(rinfo, specs, total) == false)
          return (false);
      return (true);
    }

  /// TCP
  if (specs.protocol == BP_TCP_TERMINATED_DATA)
    {
      char      *term;

      rcursor += len; /// On gèrera tous les paquets qu'on a recu.
      while ((term = (char*)memchr(inbuffer, specs.terminator, rcursor)) != NULL)
        if (ExtractFromInBuffer(rinfo, specs, term - inbuffer) == false)
          return (false);
      // Infraction au protocole
      if (rcursor >= specs.size && specs.size != 0)
        {
          Close();
          return (false);
        }
      return (true);
    }
  return (true);
}
