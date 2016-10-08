// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2013
//
// BPT NetCom

#include	"Communicator.hpp"

bpt::NetCom::Communicator::s_WriteRequest::s_WriteRequest(const void		*data,
							  unsigned int		size,
							  unsigned int		datalen)
{
  const char	*buf;
  unsigned int	len;
  unsigned int	i;

  size_send = 0;
  buf = (char*)data;
  packet_size.size = size;
  this->cursor = UNUSED_BUFFER;
  this->buffer = new char[size];
  if (datalen == UMAX)
    len = size;
  else
    len = datalen;
  for (i = 0; i < len; i++)
    this->buffer[i] = buf[i];
}

bpt::NetCom::Communicator::s_WriteRequest::~s_WriteRequest(void)
{
  delete[] this->buffer;
}
