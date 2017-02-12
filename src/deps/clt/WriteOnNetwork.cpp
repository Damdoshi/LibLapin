// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2013
//
// BPT NetCom

#include		"Client.hpp"

int			bpt::NetCom::Client::WriteOnNetwork(void)
{
  WriteRequest		*req = this->write_request.front();
  unsigned int		i;
  int			al;

  if (this->write_request.empty())
    return (1);
  if (req->cursor == UNUSED_BUFFER)
    {
      if ((i = SendTo(this->master_info, &req->packet_size.buffer[req->size_send], 4 - req->size_send)) == 0 || i == UMAX)
	return (i);
      req->size_send += i;
      if (req->size_send >= 4)
	req->cursor = req->buffer;
    }
  else
    {
      al = req->cursor - req->buffer;
      if ((i = SendTo(this->master_info, req->cursor, req->packet_size.size - al)) == 0 || i == UMAX)
	return (i);
      if ((i + al) >= req->packet_size.size)
	{
	  this->write_request.pop();
	  delete req;
	}
      else
	req->cursor += i;
    }
  return (i);
}
