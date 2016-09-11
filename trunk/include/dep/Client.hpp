// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2013
//
// BPT NetCom

#ifndef					__COMCLIENT_HPP__
# define				__COMCLIENT_HPP__
# include				<limits.h>
# include				"Communicator.hpp"

namespace				bpt
{
  namespace				NetCom
  {
    class				Client: public Communicator
    {
    private:
      /// About reading
      char				*buffer;
      char				*cursor;
      SizeBuffer			packet_size;
      unsigned char			size_received;

      bool				CheckFullPacket(void);
      void				InitFdSet(void);
      int				ReadOnNetwork(void);
      int				WriteOnNetwork(void);
      Communication			&Disconnected(unsigned int	time);

      std::queue<WriteRequest*>		write_request;
      std::string			host;

    public:
      virtual const Communication	&operator()(unsigned int	timeout = 0);
      bool				Write(const void		*buffer,
					      unsigned int		size,
					      unsigned int		client = UINT_MAX);
      bool				Start(const std::string		&host,
					      const std::string		&port);
      bool				Stop(void);

      Client(const std::string		&host = "",
	     const std::string		&port = "") throw (int);
      Client(PacketProtocol		protocol,
	     const std::string		&host = "",
	     const std::string		&port = "") throw (int);
      virtual ~Client(void);
    };
  }
}

#endif	//			__COMCLIENT_HPP__
