// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Bibliothèque Lapin

#include	"lapin_private.h"

bool		Network::SetMessage(Info		info,
				    const char		*data,
				    size_t		len,
				    t_bunny_written	wt,
				    void		*wtdata)
{
  auto		it = peers.find(info);

  if (it == peers.end())
    return (false);
  return (it->second.SetMessage(data, len, wt, wtdata));
}

template <>
bool		Network::SetMessage<std::string>(Info			info,
						 std::string const	&r,
						 t_bunny_written	wt,
						 void			*wtdata)
{
  return (SetMessage(info, r.c_str(), r.size(), wt, wtdata));
}
