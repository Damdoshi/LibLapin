// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2026
// EFRITS SAS 2022-2026
// Pentacle Technologie 2008-2026
//
// Bibliothèque Lapin

#ifndef                         __LAPIN_NETWORK_PEER_HPP__
# define                        __LAPIN_NETWORK_PEER_HPP__
# include                       <stdint.h>
# include                       <deque>
# include                       <list>
# include                       <map>
# include                       <set>
# include                       <unordered_set>
# include                       <vector>
# include                       "protocol.hpp"
# include                       "communication.hpp"

/*
** il faut pouvoir accumuler des trucs a envoyer au joueur, meme quand
** il n'est pas connecté, afin de pouvoir rattraper le retard lorsqu'il revient
** DE FAIT: il faut que Peer soit mis au courant lorsqu'un truc est vraiment
** envoyé par un descriptor - car si ce n'est pas le cas, il faut relancer la
** demande d'écriture concernée
*/

namespace                       network
{
  class                         Descriptor;
  class                         Peer
  {
  private:
    struct                      ReliableUdpPending
    {
      uint32_t                  sequence = 0;
      std::vector<char>         packet;
      double                    first_send = 0;
      double                    last_send = 0;
      unsigned                  attempts = 0;
      t_bunny_written           wt = NULL;
      void                      *wtdata = NULL;
    };

    Info                        info;
    // Which descriptor are currently used for this peer
    std::set<Descriptor*>       descriptors;
    std::list<network::WriteRequest> outqueue;
    bool                        doomed = false;
    double                      last_message = 0;

    uint32_t                    rudp_next_sequence = 0;
    uint32_t                    rudp_last_received_sequence = 0;
    bool                        rudp_has_received_sequence = false;
    std::map<uint32_t, ReliableUdpPending> rudp_pending;
    std::unordered_set<uint32_t> rudp_delivered_sequences;
    std::deque<uint32_t>        rudp_delivered_order;
#ifndef				NDEBUG
    std::set<uint32_t>          rudp_test_dropped_data_sequences;
    std::set<uint32_t>          rudp_test_dropped_ack_sequences;
#endif

    ProtoSpec                   protocol;

    // Transfert de demande d'écriture de Peer a Descriptor
    bool                        TransfertWriteRequest(void);
    bool                        ReliableUdpTick(double now);

    friend class                ::Network;
    friend class                Descriptor;

  public:
    operator                    bool (void) const;
    operator                    const Info & (void) const;
    operator                    int (void) const;

    void                        SetProtocol(Protocol                    pcol,
                                            size_t                      size,
                                            char                        terminator,
                                            int                         timeout,
                                            bool                        resed);
    void                        SetProtocol(ProtoSpec const             &spec);

    // Associer ou retirer un descripteur du pair
    bool                        AttachDescriptor(Descriptor             &desc,
                                                 const ProtoSpec        &proto,
                                                 const Info             *info = NULL);
    Peer                        &operator<<(Descriptor                  &desc);
    bool                        DetachDescriptor(const Descriptor        &desc);
    Peer                        &operator>>(const Descriptor            &desc);

    // Dépot d'une demande d'écriture
    bool                        SetMessage(const char                   *data,
                                           size_t                       len,
                                           t_bunny_written              wt = NULL,
                                           void                         *wtdata = NULL);
    template <typename          T>
    bool                        SetMessage(T const                      &data,
                                           t_bunny_written              wt = NULL,
                                           void                         *wtdata = NULL)
    {
      return (SetMessage(&data, sizeof(data), wt, wtdata));
    }
    template <typename          T>
    Peer                        &operator<<(T const                     &data)
    {
      if (SetMessage(data) == false)
        throw IOException("Operator<< failed in cascade of a Write failure");
      return (*this);
    }
    bool                        PopWriteRequest(void);

    // On établi un nouvel ensemble d'information
    Peer                        &operator=(const Info                   &info);
    // On identifie que le pair est celui qu'on cherche ou pas
    bool                        operator==(const Info                   &info);
    bool                        operator!=(const Info                   &info);

    bool                        Doom(void);
    bool                        Close(void);

    bool                        Dump(t_bunny_configuration              *cnf) const;

    Peer(void);
    ~Peer(void);
  };
}


#endif  //                      __LAPIN_NETWORK_PEER_HPP__
