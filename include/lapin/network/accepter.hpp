// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Bibliothèque Lapin

#ifndef			__LAPIN_NETWORK_ACCEPTER_HPP__
# define		__LAPIN_NETWORK_ACCEPTER_HPP__

namespace		network
{
  class			Accepter : public Descriptor
  {
  protected:
    struct protoent	*protoent;
    uint16_t		port;
    struct sockaddr_in	neinfo;

  public:
    void		Declare(struct pollfd	*fds,
				size_t		&cursize,
				size_t		maxsize) const;
    Descriptor		*Accept(struct pollfd	*fds,
				size_t		&cursize,
				size_t		maxsize) const;

    Accepter(uint16_t	port);
    ~Accepter(void);
  };
}

#endif	//		__LAPIN_NETWORK_ACCEPTER_HPP__
