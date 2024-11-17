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
# include			"communication.hpp"

class				Network;
namespace			network
{
  class				Peer;
  class				Descriptor
  {
  public:
    enum			Protocol
      {
        IMMEDIATE_RETRIEVE,	// UDP
        FIXED_SIZE,		// TCP - If all your packets have the same size.
        SIZE_PLUS_DATA,		// TCP - Size INCLUDE the size field
        TERMINATED		// TCP - Prefer SIZE_PLUS_DATA if possible. It is more efficent.
      };

  protected:
    Network			&network;
    // To update our little case, accordingly to what outqueue contains
    struct pollfd		*pollfd;
    // Associated peers, that would be disconnected if this descriptor is closed
    std::set<Peer*>		associated_peers;

    Protocol			protocol;
    size_t			size;
    char			terminator;

    bool			active;
    bool			doomed;
    int				fd;

    uint32_t			ip;
    uint16_t			port;

    std::list<Communication>	outqueue;
    size_t			wcursor;

    std::list<Communication>	inqueue;
    std::vector<char>		inbuffer;
    size_t			rcursor;

    struct size_plus_data
    {
      uint32_t			size;
      char			data[0];
    };
    size_plus_data		*spdbuffer;

    // To be used by Network
    bool			Declare(struct pollfd		*fds,
					size_t			&cursize,
					size_t			maxsize);
    Descriptor			*Accept(struct pollfd		*fds,
					size_t			&cursize,
					size_t			maxsize) const;
    // Handle protocol
    bool			Write(void);
    bool			Read(void);
    bool			ShiftInBuffer(const Info	&info);
    bool			ExtractFromInBuffer(const Info	&info,
						    size_t	len);

    bool			IsWritingFor(const Info		&info);

    bool			IsDoomed(void) const
    {
      return (doomed);
    }
    friend class		::Network;

  public:
    bool			Open(Protocol			protocol
				     = IMMEDIATE_RETRIEVE,
				     size_t			size
				     = 1024 * 64,
				     char			terminator
				     = 0,
				     uint16_t			port
				     = 0x6279, // "by"
				     const std::string		&ip
				     = "",
				     int			fd
				     = -1);

    // Getters
    operator			bool (void) const;
    operator			int (void) const;

    // Associer ou retirer un pair du descripteur.
    // Renvoi le nombre de pairs restants
    int				AttachPeer(Peer			&desc);
    Peer			&operator<<(Peer		&desc);
    int				DetachPeer(const Peer		&desc);
    Peer			&operator>>(const Peer		&desc);

    // Get last message and remove it from inbox
    bool			GetMessage(Communication	&com);
    int				GetReceivedPacketCount(void) const;
    int				GetSendingPacketCount(void) const;

    bool			Write(const char		*data,
				      size_t			len,
				      const Info		&info);
    template <typename T>
    bool			Write(T const			&data,
				      const Info		&info)
    {
      if (SetMessage(&data, sizeof(data), info) == false)
	throw IOException(__PRETTY_FUNCTION__);
      return (*this);
    }

    void			Doom(void);
    void			Close(void);

    Descriptor(Network		&network);
    virtual ~Descriptor(void);
  };
}

#endif	//		__LAPIN_NETWORK_DESCRIPTOR_HPP__
