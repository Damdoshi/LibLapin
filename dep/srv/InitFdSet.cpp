// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2013
//
// BPT NetCom

#include		"Server.hpp"

void			bpt::NetCom::Server::InitFdSet(void)
{
  std::list<Client*>::iterator	i;

  this->fds_read.Clear();
  this->fds_write.Clear();
  this->fds_error.Clear();
  this->fds_read.Set(this->master_info.socket);
  this->fds_write.Set(this->master_info.socket);
  this->fds_error.Set(this->master_info.socket);
  for (i = this->client.begin(); i != this->client.end(); ++i)
    {
      this->fds_read.Set((*i)->info->socket);
      if (!(*i)->write_request.empty())
	this->fds_write.Set((*i)->info->socket);
      this->fds_error.Set((*i)->info->socket);
    }
}
