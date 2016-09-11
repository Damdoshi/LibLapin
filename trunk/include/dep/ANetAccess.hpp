// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// LibLapin

#ifndef				__ANETACCESS_HPP__
# define			__ANETACCESS_HPP__
# include			<list>
# include			"INetAccess.hpp"

namespace			bpt
{
  namespace			NetAbs
  {
    class			ANetAccess : public INetAccess
    {
    private:
      std::list<Info*>		infolist;

    public:
      Info			*NewInfo(void);

    public:
      virtual bool		OpenSocket(Protocol		protocol,
					   Info			&master_info,
					   const std::string	&port,
					   const std::string	&ip = "") const = 0;
      virtual bool		Bind(const Info			&master_info) const = 0;
      virtual bool		Listen(const Info		&master_info) const = 0;
      virtual Info		*Accept(const Info		&master_info,
					Info			&newinfo) const = 0;
      virtual bool		Close(Socket			&socket) const = 0;
      virtual bool		Connect(const Info		&master_info) const = 0;
      virtual unsigned int	RecvFrom(const Info		&master_info,
					 char			*buffer,
					 unsigned int		len,
					 Info			*newinfo = NULL) const = 0;
      virtual unsigned int	SendTo(const Info		&master_info,
				       const char		*buffer,
				       unsigned int		len,
				       const Info		*info = NULL) const = 0;
      virtual bool	    	Select(Socket			max,
				       WatchedSocket		*read = NULL,
				       WatchedSocket		*write = NULL,
				       WatchedSocket		*exception = NULL,
				       Delay			*delay = NULL) const = 0;

      ANetAccess(void);
      virtual ~ANetAccess(void);
    };
  }
}

#endif	//			__ANETACCESS_HPP__
