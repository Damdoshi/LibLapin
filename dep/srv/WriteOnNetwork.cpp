// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2013
//
// BPT NetCom

#include		"Server.hpp"

int			bpt::NetCom::Server::RawWrite(Client			&client,
						      WriteRequest		&req)
{
  unsigned int		i;
  int			al;

  al = req.cursor - req.buffer;
  if ((i = SendTo(*client.info, req.cursor, req.packet_size.size - al)) == 0 || i == UMAX)
    return (i);
  if ((i + al) >= req.packet_size.size)
    {
      client.write_request.pop();
      delete &req;
    }
  else
    req.cursor += i;
  return (i);
}

int			bpt::NetCom::Server::SizableWrite(Client		&client,
							  WriteRequest		&req)
{
  unsigned int		i;

  if (req.cursor == UNUSED_BUFFER)
    {
      if ((i = SendTo(*client.info, &req.packet_size.buffer[req.size_send], 4 - req.size_send)) == 0 || i == UMAX)
	return (i);
      req.size_send += i;
      if (req.size_send >= 4)
	req.cursor = req.buffer;
      return (i);
    }
  return (this->RawWrite(client, req));
}

int			bpt::NetCom::Server::WriteOnNetwork(Client		&client)
{
  WriteRequest		*req;

  if (client.write_request.empty())
    {
      if (client.doomed == true)
	return (0);
      return (1);
    }
  req = client.write_request.front();
  if (this->protocol == SIZABLE)
    return (this->SizableWrite(client, *req));
  return (this->RawWrite(client, *req));
}
