// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Bibliothèque Lapin

#include	"lapin_private.h"

bool		Network::SetMessage(const std::string	&id,
				    const char		*data,
				    size_t		len)
{
  auto		it = descriptors.find(id);

  if (it == descriptors.end())
    return (false);
  return (it->second->SetMessage(data, len));
}

bool		Network::SetMessage(const Info		&info,
				    const char		*data,
				    size_t		len)
{
  auto		it = descriptors.find(info.identity);

  if (it == descriptors.end())
    return (false);
  return (it->second->SetMessage(data, len, info));
}

template <>
bool		Network::SetMessage<std::string>(const Info		&info,
						 std::string const	&r)
{
  return (SetMessage(info, r.c_str(), sizeof(r.size())));
}
