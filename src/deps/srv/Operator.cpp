// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2013
//
// BPT NetCom

#include				"Server.hpp"

const bpt::NetCom::Communication	&bpt::NetCom::Server::operator()(unsigned int	timeout)
{
  std::list<Client*>::iterator		i;
  NetAbs::INetAccess::Delay		delay;
  unsigned int				max;
  int					tmp;
  int					count;

  if (this->communication.comtype == MESSAGE)
    {
      this->communication.comtype = EXPIRED;
      delete[] this->communication.message.buffer.character;
    }
  if (CheckFullPacket() == true)
    return (this->communication);
  InitFdSet();
  max = FindMaxFd() + 1;
  if (timeout != UMAX)
    {
      delay.microseconds = timeout * 1000;
      delay.seconds = timeout / 1000;
      if ((count = Select(max, &this->fds_read, &this->fds_write, &this->fds_error, &delay)) == -1)
	return (RetError(SELECT_FAIL, delay.seconds * 1000 + delay.microseconds / 1000));
      if ((max =  delay.seconds * 1000 + delay.microseconds / 1000) == 0)
	return (RetExpired(0));
    }
  else
    {
      if ((count = Select(max, &this->fds_read, &this->fds_write, &this->fds_error)) == -1)
	return (RetError(SELECT_FAIL, 0));
      max = 0;
    }
  for (i = this->client.begin(); i != this->client.end() && count > 0; ++i)
    {
      if (this->fds_write.IsSet((*i)->info->socket))
	{
	  if ((tmp = WriteOnNetwork(**i)) == 0)
	    return (Disconnected((*i)->info->socket, max));
	  else if (tmp == -1)
	    return (RetError(WRITE_FAIL, max));
	  count -= 1;
	}
      if (this->fds_read.IsSet((*i)->info->socket))
	{
	  if ((tmp = ReadOnNetwork(**i)) == 0)
	    return (Disconnected((*i)->info->socket, max));
	  else if (tmp == -1)
	    return (RetError(READ_FAIL, max));
	  count -= 1;
	}
    }
  if (count > 0)
    NewConnexion(max);
  return (this->communication);
}

