// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Bibliothèque Lapin

#ifndef					__LAPIN_NETWORK_DESCRIPTOR_HPP__
# define				__LAPIN_NETWORK_DESCRIPTOR_HPP__
# include				<sys/types.h>
# include				<sys/socket.h>
# include				<netinet/in.h>
# include				<unistd.h>
# include				<vector>
# include				<queue>
# include				<string>
# include				<iostream>
# include				<string.h>
# include				<list>

class					Network;
namespace				network
{
  class					Descriptor
  {
  public:
    class				IOException : public std::runtime_error
    {
    public:
      IOException(const std::string	&str) : runtime_error(str) {}
      ~IOException() {}
    };
    struct				Info
    {
      char				identity[32];
      struct sockaddr_in		sockaddr;
      socklen_t				socklen;

      Info				&operator=(const Info		&info)
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

    struct				Communication
    {
      Info				info;
      std::vector<char>			datas;

      Communication(const Info		&_info)
	: info(_info)
      {}
    };

    enum				Protocol
      {
        IMMEDIATE_RETRIEVE,		// UDP
        FIXED_SIZE,			// TCP - If all your packets have the same size.
        SIZE_PLUS_DATA,			// TCP - Size INCLUDE the size field
        TERMINATED			// TCP - Prefer SIZE_PLUS_DATA if possible. It is more efficent.
      };

  protected:
    Network				&network;
    // To update our little case, accordingly to what outqueue contains
    struct pollfd			*pollfd;

    Protocol				protocol;
    size_t				size;
    bool				active;
    bool				doomed;
    int					fd;
    Info				info;
    uint32_t				ip;
    uint16_t				port;

    std::list<Communication>		outqueue;
    size_t				wcursor;

    std::list<Communication>		inqueue;
    std::vector<char>			inbuffer;
    size_t				rcursor;

    struct size_plus_data
    {
      uint32_t				size;
      char				data[0];
    };
    size_plus_data			*spdbuffer;

    // To be used by Network
    bool				Declare(struct pollfd		*fds,
						size_t			&cursize,
						size_t			maxsize);
    Descriptor				*Accept(struct pollfd		*fds,
						size_t			&cursize,
						size_t			maxsize) const;
    // Handle protocol
    bool				Write(void);
    bool				Read(void);
    bool				ShiftInBuffer(const Info	&info);
    bool				ExtractFromInBuffer(size_t	len);

    bool				IsDoomed(void) const
    {
      return (doomed);
    }
    friend class			::Network;

  public:
    operator				bool (void) const
    {
      return (active && !doomed);
    }
    operator				int (void) const
    {
      return (fd);
    }
    operator				const Info & (void) const
    {
      return (info);
    }
    operator				const char * (void) const
    {
      return (info.identity);
    }

    Descriptor				&operator=(Protocol		&pro)
    {
      protocol = pro;
      return (*this);
    }
    Descriptor				&operator=(const char		*id)
    {
      snprintf(info.identity, sizeof(info.identity), "%s", id);
      return (*this);
    }
    Descriptor				&operator=(int			_fd)
    {
      if (fd != -1)
	close(fd);
      fd = _fd;
      return (*this);
    }

    bool				GetMessage(Communication	&com)
    {
      if (inqueue.empty())
	return (false);
      com.info = inqueue.front().info;
      com.datas = std::move(inqueue.front().datas);
      inqueue.pop_front();
      return (true);
    }

    // Push write requests for TCP protocols
    bool				SetMessage(const char		*data,
						   size_t		len)
    {
      if (protocol == IMMEDIATE_RETRIEVE)
	return (false);
      try {
	outqueue.push_back(Communication{info});
	outqueue.back().datas.assign(data, &data[len]);
      } catch (...) {
	return (false);
      }
      return (true);
    }
    // PUsh write requests for UDP protocols
    bool				SetMessage(const char		*data,
						   size_t		len,
						   const Info		&_info)
    {
      if (protocol != IMMEDIATE_RETRIEVE)
	return (false);
      try {
	outqueue.push_back(Communication{_info});
	outqueue.back().datas.assign(data, &data[len]);
      } catch (...) {
	return (false);
      }
      return (true);
    }
    template <typename T>
    Descriptor				&operator<<(T const		&data)
    {
      if (Write(&data, sizeof(data)) == false)
	throw IOException(__PRETTY_FUNCTION__);
      return (*this);
    }

    void				Doom(void)
    {
      doomed = true;
    }

    void				Close(void)
    {
      if (fd != -1)
	close(fd);
      fd = -1;
    }

    Descriptor(Network			&network,
	       Protocol			protocol = IMMEDIATE_RETRIEVE,
	       size_t			_size = 1024 * 64,
	       uint16_t			port = 0x6279, // "by"
	       const std::string	&ip = "");
    Descriptor(Network			&network,
	       int			fd,
	       Protocol			protocol = IMMEDIATE_RETRIEVE,
	       // default bufsize, fixed size, max size or terminator
	       // any value inferior to 16 will be set to 16, except if it is a terminator
	       // the terminator is only constituted of a single byte
	       size_t			size = 1024 * 64);
    virtual ~Descriptor(void);
  };

  template <>
  Descriptor				&Descriptor::operator<<<std::string>(std::string const &data)
  {
    if (SetMessage(data.c_str(), data.size()) == false)
      throw IOException(__PRETTY_FUNCTION__);
    return (*this);
  }
  template <>
  Descriptor				&Descriptor::operator<<<const char * const>(const char * const &data)
  {
    if (SetMessage(data, strlen(data)) == false)
      throw IOException(__PRETTY_FUNCTION__);
    return (*this);
  }
}

#endif	//		__LAPIN_NETWORK_DESCRIPTOR_HPP__
