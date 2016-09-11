// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2013
//
// BPT NetCom

#include		"Client.hpp"

int			bpt::NetCom::Client::ReadOnNetwork(void)
{
  char			tmp[1024];
  unsigned int		al;
  unsigned int		i;

  if (this->buffer == NULL)
    {
      if ((i = RecvFrom(this->master_info, &this->packet_size.buffer[this->size_received], 4 - this->size_received)) <= 0)
	return (i);
      this->size_received += i;
      if (this->size_received == 4)
	{
	  if (this->packet_size.size <= this->max_size)
	    {
	      this->buffer = new char[this->packet_size.size + 1];
	      this->buffer[this->packet_size.size] = '\0';
	      this->cursor = this->buffer;
	    }
	  else
	    this->buffer = TOO_BIG;
	}
    }
  else
    if (this->buffer != TOO_BIG)
      {
	al = this->cursor - this->buffer;
	if ((i = RecvFrom(this->master_info, this->cursor, this->packet_size.size - al)) <= 0)
	  return (i);
	this->cursor += i;
      }
    else
      {
	if ((i = RecvFrom(this->master_info, &tmp[0], 1024)) <= 0)
	  return (i);
	this->packet_size.size -= i;
      }
  return (i);
}

