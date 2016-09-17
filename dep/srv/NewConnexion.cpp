// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2013
//
// BPT NetCom

#include		"Server.hpp"

bool			bpt::NetCom::Server::NewConnexion(unsigned int	time)
{
  if (this->fds_read.IsSet(this->master_info.socket) == false)
    {
      RetExpired(time);
      return (false);
    }
  if ((this->communication.connected.client = NewClient()) == UMAX)
    RetError(ACCEPT_FAIL, time);
  else
    {
      this->communication.comtype = CONNECTED;
      this->communication.connected.time = time;
    }
  return (true);
}
