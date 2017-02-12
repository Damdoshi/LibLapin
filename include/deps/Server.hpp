// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2013
//
// BPT NetCom

#ifndef					__COMSERVER_HPP__
# define				__COMSERVER_HPP__
# include				<list>
# include				"Communicator.hpp"

namespace				bpt
{
  namespace				NetCom
  {
    class				Server : public bpt::NetCom::Communicator
    {
    private:
      typedef struct			s_Client
      {
	std::queue<WriteRequest*>	write_request;
	NetAbs::INetAccess::Info	*info;
	char				*buffer;
	char				*cursor;
	SizeBuffer			packet_size;
	unsigned int			size_received;
	PacketProtocol			protocol;
	bool				doomed;

	s_Client(PacketProtocol		protocol = SIZABLE);
	~s_Client(void);
      }					Client;

      /// Tools
      unsigned int			NewClient(void);
      void				InitFdSet(void);
      unsigned int			FindMaxFd(void);

      /// Internal scheduling
      int				RawWrite(Client			&clt,
						 WriteRequest		&req);
      int				SizableWrite(Client		&clt,
						     WriteRequest	&req);
      int				WriteOnNetwork(Client		&clt);
      int				RawRead(Client			&clt);
      int				SizableRead(Client		&clt);
      int				ReadOnNetwork(Client		&clt);
      bool				SizablePacket(void);
      bool				RawPacket(void);
      bool				CheckFullPacket(void);

      /// Build return package
      bool				NewConnexion(unsigned int	time);
      Communication			&Disconnected(unsigned int	usr,
						      unsigned int	time);

      std::list<Client*>		client;

    public:
      virtual const Communication	&operator()(unsigned int	timeout = UMAX);
      bool				Write(const void		*buffer,
					      unsigned int		size,
					      unsigned int		client = -1);

      bool				AnyFullPacket(void);
      bool				KillClient(unsigned int		client);
      bool				DoomClient(unsigned int		client);
      unsigned int			GetIP(unsigned int		usr);

      bool				Start(const std::string		&port);
      bool				Stop(void);

      Server(const std::string		&port = "") throw (int);
      Server(PacketProtocol		protocol,
	     const std::string		&port = "") throw (int);
      virtual ~Server(void);
    };
  }
}

#endif	//				__COMSERVER_HPP__
