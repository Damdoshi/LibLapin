// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2013
//
// BPT NetCom

#include		<string.h>
#include		"Server.hpp"

bool			bpt::NetCom::Server::Write(const void		*buffer,
						   unsigned int		size,
						   unsigned int		user)
{
  std::list<Client*>::iterator			it;
  WriteRequest					*wr;
  unsigned int					i;

  i = 0;
  if (size == 0 || size > this->max_size)
    return (false);
  for (it = client.begin(); it != client.end() && (*it)->info->socket != user; ++it);
  if (it == client.end())
    return (false);
  if (this->protocol == RAW)
    i = strlen(EOC);
  if ((wr = new WriteRequest(buffer, size + i, size)) == NULL)
    return (false);
  if (this->protocol == RAW)
    {
      wr->cursor = wr->buffer;
      memcpy(&wr->buffer[size], EOC, i);
    }
  (*it)->write_request.push(wr);
  return (true);
}
