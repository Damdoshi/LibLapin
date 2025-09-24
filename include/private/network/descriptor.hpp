// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Bibliothèque Lapin

#ifndef				__LAPIN_NETWORK_DESCRIPTOR_HPP__
# define			__LAPIN_NETWORK_DESCRIPTOR_HPP__
# include			<stdint.h>
# include			<unistd.h>
# include			<queue>
# include			<string>
# include			<iostream>
# include			<list>
# include			<set>
# include			"protocol.hpp"
# include			"communication.hpp"

class				Network;
namespace			network
{
  class				Peer;
  class				Descriptor
  {
  protected:
    Network			*network;
    // To update our little case, accordingly to what outqueue contains
    struct pollfd		*pollfd;
    // Position inside network class
    size_t			position;

    // Associated peers, that would be disconnected if this descriptor is closed
    std::set<Peer*>		associated_peers;
    network::Info		info; // To be returned by Open, that's all.

    // Seulement pour les serveurs TCP.
    ProtoSpec			protocol;
    
    bool			active;
    bool			doomed;
    int				fd;

    uint32_t			ip;
    uint16_t			port;

    std::list<Communication>	outqueue;
    size_t			wcursor;

    std::list<Communication>	inqueue;

    char			*inbuffer; // NULL si unbuffer_size 0
    size_t			inbuffer_size;
    size_t			rcursor;

    struct size_plus_data
    {
      uint32_t			size;
      char			data[0];
    };
    size_plus_data		*spdbuffer;

    // To be used by Network
    bool			Declare(void);
    network::Info		Accept(size_t			&cursize,
				       size_t			maxsize);
    // Handle protocol
    bool			Write(void);
    bool			Read(void);
    bool			ShiftInBuffer(const Info	&info,
					      const ProtoSpec	&spec,
					      size_t		len = 0);
    bool			ExtractFromInBuffer(const Info	&info,
						    const ProtoSpec &spec,
						    size_t	len);

    bool			IsWritingFor(const Info		&info);

    bool			IsDoomed(void) const
    {
      return (doomed);
    }

    Descriptor(void) : network(NULL) {}
    friend class		::Network;
    friend class		Peer;

  public:
    network::Info		Open(network::ProtoSpec const	&protocol,
				     uint16_t			port,
				     const std::string		&ip);
    network::Info		Open(network::ProtoSpec const	&protocol,
				     int			fd,
				     network::Info		info);

    // Getters
    operator			bool (void) const;
    operator			int (void) const;

    // Associer ou retirer un pair du descripteur.
    // Renvoi le nombre de pairs restants
    bool			AttachPeer(Peer			&desc);
    Peer			&operator<<(Peer		&desc);
    int				DetachPeer(const Peer		&desc);
    Peer			&operator>>(const Peer		&desc);

    // Get last message and remove it from inbox
    bool			GetMessage(Communication	&com);
    int				GetReceivedPacketCount(void) const;
    int				GetSendingPacketCount(void) const;

    bool			SetMessage(const char		*data,
					   size_t		len,
					   const Info		&info,
					   const ProtoSpec	&specs,
					   t_bunny_written	wt = NULL,
					   void			*wtdata = NULL);
    template <typename T>
    bool			SetMessage(T const		&data,
					   const Info		&info,
					   const ProtoSpec	&specs,
					   t_bunny_written	wt = NULL,
					   void			*wtdata = NULL)
    {
      if (SetMessage(&data, sizeof(data), info, specs, wt, wtdata) == false)
	throw IOException(__PRETTY_FUNCTION__);
      return (*this);
    }

    void			Doom(void);
    bool			Close(void);

    bool			Dump(t_bunny_configuration	*cnf,
				     size_t			index) const;

    Descriptor(Network		&network);
    virtual ~Descriptor(void);
  };
}

#endif	//		__LAPIN_NETWORK_DESCRIPTOR_HPP__
