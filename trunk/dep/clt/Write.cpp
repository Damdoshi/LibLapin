// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2013
//
// BPT NetCom

#include		"Client.hpp"

bool			bpt::NetCom::Client::Write(const void		*buffer,
						   unsigned int		size,
						   unsigned int		user)
{
  WriteRequest		*wr;

  (void)user;
  if (size == 0 || size > this->max_size || (wr = new WriteRequest(buffer, size)) == NULL)
    return (false);
  write_request.push(wr);
  return (true);
}
