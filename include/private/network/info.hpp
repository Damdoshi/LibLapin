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
  struct		Info : public t_bunny_network_info
  {
    operator		bool (void) const
    {
      return (socklen != 0);
    }
    bool		operator<(const Info		&info) const
    {
      if (this == &info)
	return (false);
      return (memcmp((void*)this, (void*)&info, socklen) < 0);
    }
    bool		operator==(const Info		&info) const
    {
      if (this == &info)
	return (true);
      if (socklen != info.socklen)
	return (false);
      if (memcmp((void*)&sockaddr, (void*)&info.sockaddr, socklen))
	return (false);
      return (true);
    }
    bool		operator!=(const Info		&info) const
    {
      return (!(*this == info));
    }

    Info		&operator=(const Info		&info)
    {
      if (this != &info)
	memcpy((void*)this, (void*)&info, sizeof(*this));
      return (*this);
    }
    bool		Dump(t_bunny_configuration	*cnf) const
    {
      char		buf[512];
      uint8_t		*iptr = (uint8_t*)&sockaddr;
      size_t		len;

      len = 0;
      buf[0] = 0;
      if (!socklen)
	snprintf(buf, sizeof(buf), "Invalid network info.\n");
      else
	{
	  for (size_t j = 0; j < socklen; ++j)
	    len += snprintf(&buf[len], sizeof(buf) - len, "%hhu.", iptr[j]);
	  buf[len - 1] = 0;
	}
      return (bunny_configuration_setf_string(cnf, buf, "NetInfo"));
    }
    Info(void)
    {
      memset((void*)this, 0, sizeof(*this));
    }
    Info(const struct sockaddr_in	&in,
	 const socklen_t		&le)
    {
      memcpy(&sockaddr, &in, sizeof(sockaddr));
      socklen = le;
    }
    Info(const Info			&info)
    {
      *this = info;
    }
    ~Info(void)
    {}
  };
}

#endif	//		__LAPIN_NETWORK_INFO_HPP__
