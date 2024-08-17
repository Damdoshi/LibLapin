// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Bibliothèque Lapin

#ifndef					__LAPIN_NETWORK_DESCRIPTOR_HPP__
# define				__LAPIN_NETWORK_DESCRIPTOR_HPP__

namespace				network
{
  class					Descriptor
  {
  public:
    enum				Protocol
      {
       IMMEDIATE_RETRIEVE,
       FIXED_SIZE,
       SIZE_PLUS_DATA, // Size INCLUDE the size field
       TERMINATED,
      };

  protected:
    Protocol				protocol;
    size_t				size;
    bool				active;
    bool				doomed;
    int					fd;
    char				identity[32];
    struct sockaddr_in			sockaddr;
    socklen_t				socklen;

    // To update our little case, accordingly to what outqueue contains
    struct pollfd			*pollfd;

    std::queue<std::vector<char>>	outqueue;
    std::list<std::vector<char>>	inqueue;
    std::vector<char>			inbuffer;
    size_t				cursor;

    struct size_plus_data
    {
      uint32_t				size;
      char				data[0];
    };
    size_plus_data			*spdbuffer;

    // To use read of receivefrom, to use sendto or write.
    virtual ssize_t			Write(const char		*data,
					      size_t			datalen) const = 0;
    virtual ssize_t			Read(char			*data,
					     size_t			datalen) const = 0;

    // To be used by Network
    virtual bool			Declare(struct pollfd		*fds,
						size_t			&cursize,
						size_t			maxsize) const;
    virtual Descriptor			*Accept(struct pollfd		*fds,
						size_t			&cursize,
						size_t			maxsize) const;

    // Handle protocol
    bool				Write(void);
    bool				Read(void);
    bool				ShiftInBuffer(void);
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
    operator				const char * (void) const
    {
      return (identity);
    }

    Descriptor				&operator=(const char		*id)
    {
      snprintf(identity, sizeof(identity), "%s", id);
      return (*this);
    }
    Descriptor				&operator=(int			_fd)
    {
      if (fd != -1)
	close(fd);
      fd = _fd;
      return (*this);
    }

    std::vector<char>			*Read(void)
    {
      if (inqueue.empty())
	return (NULL);
      std::vector<char>			nw = std::move(inqueue.front());

      inqueue.pop();
      return (nw);
    }

    // Push write requests
    bool				Write(const char		*data,
					      size_t			len)
    {
      try {
	outqueue.push(std::move(std::vector{}.assign(data, &data[len])));
      } catch (...) {
	return (false);
      }
      return (true);
    }
    template <typename T>
    Descriptor				&operator<<(T const		&data)
    {
      if (Write(&data, sizeof(data)) == false)
	throw WriteFailure();
      return (*this);
    }
    template <>
    Descriptor				&operator<<<std::string>(std::string const &data)
    {
      if (Write(data.c_str(), data.size()) == false)
	throw WriteFailure();
      return (*this);
    }
    template <>
    Descriptor				&operator<<<const char *>(char const *&data)
    {
      if (Write(data, strlen(data)) == false)
	throw WriteFailure();
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

    Descriptor(Protocol			protocol = SIZE_PLUS_DATA,
	       // default bufsize, fixed size, max size or terminator
	       // any value inferior to 16 will be set to 16, except if it is a terminator
	       // the terminator is only constituted of a single byte
	       size_t			size = 4096,
	       int			fd = -1);
    virtual ~Descriptor(void);
  };
}

#endif	//		__LAPIN_NETWORK_DESCRIPTOR_HPP__
