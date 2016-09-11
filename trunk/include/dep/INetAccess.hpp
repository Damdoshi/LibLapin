// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// LibLapin

#ifndef				__INETACCESS_HPP__
# define			__INETACCESS_HPP__
# include			<iostream>
# include			<map>
# define			UMAX					((unsigned int)-1)

namespace			bpt
{
  namespace			NetAbs
  {
    class			INetAccess
    {
    public:
      typedef unsigned int	Socket;
      typedef enum		e_protocol
	{
	  TCP			= 0,
	  UDP			= 1
	}			Protocol;
      class			Info
      {
      public:
	Socket			socket;
	unsigned int		ip;
	unsigned int		port;

	Info(void) {}
	Info(const Info		&i) : socket(i.socket), ip(i.ip), port(i.port) {}
	~Info(void) {}
      };
      class			WatchedSocket
      {
      public:
	std::map<unsigned int, bool>	state;

	void			Clear(const Socket&			socket);
	void			Set(const Socket&			socket);
	bool			IsSet(const Socket&			socket);
	void			Clear(void);
      };
      typedef struct		s_delay
      {
	unsigned int		seconds;
	unsigned int		microseconds;
      }				Delay;

      virtual bool		OpenSocket(Protocol			protocol,
					   Info				&master_info,
					   const std::string		&port,
					   const std::string		&ip = "") const = 0;
      virtual bool		Bind(const Info				&master_info) const = 0;
      virtual bool		Listen(const Info			&master_info) const = 0;
      virtual Info		*Accept(const Info			&master_info,
					Info				&newinfo) const = 0;
      virtual bool		Close(Socket				&socket) const = 0;
      virtual bool		Connect(const Info			&master_info) const = 0;
      virtual unsigned int	RecvFrom(const Info			&master_info,
					 char				*buffer,
					 unsigned int			len,
					 Info				*newinfo = NULL) const = 0;
      virtual unsigned int	SendTo(const Info			&master_info,
				       const char			*buffer,
				       unsigned int			len,
				       const Info			*info = NULL) const = 0;
      virtual bool		Select(Socket				max,
				       WatchedSocket			*read = NULL,
				       WatchedSocket			*write = NULL,
				       WatchedSocket			*exception = NULL,
				       Delay				*delay = NULL) const = 0;
      virtual ~INetAccess(void){}
    };
  }
}

#endif		//		__INETACCESS_HPP__
