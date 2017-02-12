// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2013
//
// BPT NetCom

#include		"Client.hpp"

void			bpt::NetCom::Client::InitFdSet(void)
{
  this->fds_read.Clear();
  this->fds_write.Clear();
  this->fds_error.Clear();
  this->fds_read.Set(this->master_info.socket);
  if (!write_request.empty())
    this->fds_write.Set(this->master_info.socket);
  this->fds_error.Set(this->master_info.socket);
}
