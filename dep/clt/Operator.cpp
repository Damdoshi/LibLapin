// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2013
//
// BPT NetCom

#include				"Client.hpp"

const bpt::NetCom::Communication	&bpt::NetCom::Client::operator()(unsigned int	timeout)
{
  NetAbs::INetAccess::Delay		delay;
  unsigned int				max;
  int					tmp;

  if (this->communication.comtype == MESSAGE)
    {
      this->communication.comtype = EXPIRED;
      delete[] this->communication.message.buffer.character;
    }
  if (CheckFullPacket() == true)
    return (this->communication);
  InitFdSet();
  if (timeout != UMAX)
    {
      delay.microseconds = timeout * 1000;
      delay.seconds = timeout / 1000;
      if (Select(this->master_info.socket + 1, &this->fds_read, &this->fds_write, &this->fds_error, &delay) == false)
	return (RetError(SELECT_FAIL, delay.seconds * 1000 + delay.microseconds / 1000));
      if ((max =  delay.seconds * 1000 + delay.microseconds / 1000) == 0)
	return (RetExpired(0));
    }
  else
    {
      if (Select(this->master_info.socket + 1, &this->fds_read, &this->fds_write, &this->fds_error) == false)
	return (RetError(SELECT_FAIL, 0));
      max = 0;
    }
  if (this->fds_read.IsSet(this->master_info.socket))
    {
      if ((tmp = ReadOnNetwork()) == 0)
	return (Disconnected(max));
      else if (tmp == -1)
	return (RetError(READ_FAIL, max));
    }
  if (this->fds_write.IsSet(this->master_info.socket))
    {
      if ((tmp = WriteOnNetwork()) == 0)
	return (Disconnected(max));
      else if (tmp == -1)
	return (RetError(WRITE_FAIL, max));
    }
  return (this->communication);
}

