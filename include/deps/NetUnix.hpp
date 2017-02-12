// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// NetUnix

#ifndef				__NETUNIX_HPP__
# define			__NETUNIX_HPP__
# ifndef			__WIN32
#  include			<sys/socket.h>
#  include			<sys/select.h>
#  include			<arpa/inet.h>
#  include			<netdb.h>
# else
#  include			<ws2tcpip.h>
# endif
# include			"ANetAccess.hpp"

namespace			bpt
{
  namespace			NetAbs
  {
    class			NetUnix : public ANetAccess
    {
    public:
      virtual bool		OpenSocket(Protocol			protocol,
					   Info				&master_info,
					   const std::string		&port,
					   const std::string		&ip = "") const;
      virtual bool		Bind(const Info				&master_info) const;
      virtual bool		Listen(const Info			&master_info) const;
      virtual Info		*Accept(const Info			&master_info,
					Info				&newinfo) const;
      virtual bool		Close(Socket				&socket) const;
      virtual bool		Connect(const Info			&master_info) const;
      virtual unsigned int	RecvFrom(const Info			&master_info,
					char				*buffer,
					unsigned int			len,
					Info				*newinfo = NULL) const;
      virtual unsigned int	SendTo(const Info			&master_info,
					const char			*buffer,
					unsigned int			len,
					const Info			*info = NULL) const;
      virtual bool		Select(Socket				max,
				       WatchedSocket			*read = NULL,
				       WatchedSocket			*write = NULL,
				       WatchedSocket			*exception = NULL,
				       Delay				*delay = NULL) const;
      NetUnix(void);
      virtual ~NetUnix(void);
    };
  }
}

#endif	//			__NETUNIX_HPP__
