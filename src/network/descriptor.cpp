// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Bibliothèque Lapin

#include		"lapin_private.hpp"

bool			network::Descriptor::Declare(struct pollfd	*fds,
						     size_t		&cursize,
						     size_t		maxsize) const
{
  if (cursize >= maxsize)
    return (false);
  if (!active || doomed || fd == -1)
    return (false);
  pollfd = &fds[cursize++];
  pollfd->fd = fd;
  pollfd->events = POLLIN;
  if (outqueue.size())
    pollfd->events |= POLLOUT;
  return (true);
}

Descriptor		*network::Descriptor::Accept(struct pollfd	*fds,
						     size_t		&cursize,
						     size_t		maxsize) const
{
  struct sockaddr_in	_sockaddr;
  socklen_t		_socklen;
  Descriptor		*ndesc;

  if ((ndesc = new (std::nothrow) Descriptor(protocol, size)) == NULL)
    return (NULL);
  if ((ndesc->fd = accept(fd, &_socklen, &socklen_t)) == -1)
    return (NULL);
  if (ndesc->Declare(fds, cursize, maxsize) == false)
    {
      delete ndesc;
      return (NULL);
    }
  memcpy(&ndesc->sockaddr, &_sockaddr, sizeof(ndesc->sockaddr));
  ndesc->socklen = _socklen;
  return (ndesc);
}


bool			network::Descriptor::Write(void)
{
}

bool			network::Descriptor::ShiftInBuffer(void)
{
  try
    {
      inqueue.push_back(std::vector<char>{});
    }
  catch (...)
    {
      return (false);
    }
  inqueue.back() = std::move(inbuffer);
  inbuffer.clear();
  cursor = 0;
  try
    {
      inbuffer.resize(size);
    }
  catch (...)
    {
      return (false);
    }
  return (true);
}

bool			network::Descriptor::ExtractFromInBuffer(size_t		len)
{
  try {
    inqueue.push_back(std::vector<char>{len});
  } catch (...) {
    return (false);
  }
  size_t		i;
  size_t		j;

  for (i = 0; i < len; ++i)
    inqueue.back()[i] = inbuffer[i];
  for (j = 0; i < inbuffer[i].size(); ++i, ++j)
    inbuffer[j] = inbuffer[î];
  cursor -= len;
  return (true);
}

bool			network::Descriptor::Read(void)
{
  ssize_t		len;

  try {
    if (inbuffer.size() == 0)
      inbuffer.resize(size);
  }
  catch (...) {
    return (false);
  }

  if (inbuffer.size() - cursor)
    {
      if ((len = Read(&inbuffer[cursor], inbuffer.size() - cursor)) == -1)
	return (false);
      if (len == 0)
	{
	  pollfd->fd *= -1;
	  close(fd);
	  fd = -1;
	  active = false;
	  return (true);
	}
    }
  else
    len = 0;
  if (protocol == IMMEDIATE_RETRIEVE)
    return (ShiftInBuffer());
  if (protocol == FIXED_SIZE)
    {
      if (len + cursor == inbuffer.size())
	return (ShiftInBuffer());
      cursor += len;
    }
  if (protocol == SIZE_PLUS_DATA)
    {
      cursor += len;
      if (cursor < sizeof(spdbuffer->size))
	return (true);
      // Infraction au protocole
      if (spdbuffer->size > size)
	{
	  Close();
	  return (false);
	}
      while (cursor > spdbuffer->size)
	if (ExtractFromInBuffer(spdbuffer->size) == false)
	  return (false);
      return (true);
    }
  if (protocol == TERMINATED)
    {
      char		*term;

      cursor += len;
      while ((term = memchr(&inbuffer[0], size & 0xFF, cursor)) != NULL)
	if (ExtractFromInBuffer(term - &inbuffer[0]) == false)
	  return (false);
      // Infraction au protocole
      if (cursor >= size)
	{
	  Close();
	  return (false);
	}
      return (true);
    }
  return (true);
}

network::Descriptor::Descriptor(Protocol	_protocol,
				size_t		_size,
				int		_fd)
  : protocol(_protocol),
    size(_size),
    active(_fd != -1),
    doomed(false),
    fd(_fd),
    polllfd(NULL),
    spdbuffer(NULL)
{
  if (size < 16)
    size = 16;
  cursor = 0;
  inbuffer.resize(size);
  spdbuffer = &inbuffer[0];
  memset(identity, 0, sizeof(identity));
  memset(&sockaddr, 0, sizeof(sockaddr));
  memset(&socklen, 0, sizeof(socklen));
}

network::Descriptor::~Descriptor(void)
{
  Close();
}

