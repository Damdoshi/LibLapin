// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Bibliothèque Lapin

#include	"lapin_private.h"


bool		Network::SetMessage(const Info		&info,
				    const char		*data,
				    size_t		len)
{
  auto		it = peers.find(info);

  if (it == peers.end())
    return (false);
  return (it->second.Write(data, len));
}

template <>
bool		Network::SetMessage<std::string>(const Info		&info,
						 std::string const	&r)
{
  return (SetMessage(info, r.c_str(), sizeof(r.size())));
}
