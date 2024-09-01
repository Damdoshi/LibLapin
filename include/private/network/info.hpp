// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Bibliothèque Lapin

#ifndef			__LAPIN_NETWORK_INFO_HPP__
# define		__LAPIN_NETWORK_INFO_HPP__
# include		<sys/types.h>
# include		<sys/socket.h>
# include		<netinet/in.h>
# include		<string.h>

namespace		network
{
  struct		Info
  {
    char		identity[32];
    struct sockaddr_in	sockaddr;
    socklen_t		socklen;

    Info		&operator=(const Info		&info)
    {
      if (this != &info)
	memcpy((void*)this, (void*)&info, sizeof(*this));
      return (*this);
    }
    Info(void)
    {
      memset(identity, 0, sizeof(identity));
      memset(&sockaddr, 0, sizeof(sockaddr));
      memset(&socklen, 0, sizeof(socklen));
    }
    Info(const Info			&info)
    {
      *this = info;
    }
  };
}

#endif	//		__LAPIN_NETWORK_INFO_HPP__
