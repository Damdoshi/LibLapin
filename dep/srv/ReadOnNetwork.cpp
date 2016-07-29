// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2013
//
// BPT NetCom

#include		<cstdlib>
#include		<string.h>
#include		"Server.hpp"

int			bpt::NetCom::Server::RawRead(Client		&clt)
{
  bpt::NetCom::Buffer	tbuff;
  unsigned int		i;
  unsigned int		al;
  char			*nbuff;

  if (clt.buffer == NULL)
    clt.size_received = 0;
  al = clt.cursor - clt.buffer;
  if (clt.size_received <= al + this->chunk_size)
    {
      tbuff.character = clt.buffer;
      nbuff = new char[clt.size_received + this->chunk_size + 1];
      memcpy(nbuff, tbuff.unknown, clt.size_received);
      clt.size_received += this->chunk_size;
      if (clt.buffer != NULL)
	delete[] clt.buffer;
      clt.buffer = nbuff;
      clt.cursor = &clt.buffer[al];
    }
  if (al > this->max_size)
    {
      clt.cursor = clt.buffer;
      al = 0;
    }
  if ((i = RecvFrom(*clt.info, clt.cursor, clt.size_received - al - 1)) <= 0)
    return (i);
  clt.cursor += i;
  return (i);
}

int			bpt::NetCom::Server::SizableRead(Client		&clt)
{
  char			tmp[1024];
  unsigned int		al;
  unsigned int		i;

  if (clt.buffer == NULL)
    {
      if ((i = RecvFrom(*clt.info, &clt.packet_size.buffer[clt.size_received], 4 - clt.size_received)) == 0 || i == UMAX)
	return (i);
      clt.size_received += i;
      if (clt.size_received == 4)
	{
	  if (clt.packet_size.size <= this->max_size)
	    {
	      clt.buffer = new char[clt.packet_size.size + 1];
	      clt.buffer[clt.packet_size.size] = '\0';
	      clt.cursor = clt.buffer;
	    }
	  else
	    clt.buffer = TOO_BIG;
	}
    }
  else
    if (clt.buffer != TOO_BIG)
      {
	al = clt.cursor - clt.buffer;
	if ((i = RecvFrom(*clt.info, clt.cursor, clt.packet_size.size - al)) <= 0)
	  return (i);
	clt.cursor += i;
      }
    else
      {
	if ((i = RecvFrom(*clt.info, &tmp[0], 1024)) <= 0)
	  return (i);
	clt.packet_size.size -= i;
      }
  return (i);
}

int			bpt::NetCom::Server::ReadOnNetwork(Client	&clt)
{
  if (this->protocol == SIZABLE)
    return (this->SizableRead(clt));
  return (this->RawRead(clt));
}
