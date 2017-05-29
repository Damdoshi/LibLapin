// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include		<string.h>
#include		"deps/NetCom.hpp"
#include		"lapin.h"

struct			bunny_client
{
  size_t		server;
  void			*a;
  int			b;
  char			*c;
  uint16_t		d;
};

t_bunny_client		*bunny_new_client_opt(const char	*host,
					      uint16_t		port,
					      t_bunny_protocol	local)
{
  struct bunny_client	*bclt;
  bpt::NetCom::Client	*clt;
  std::stringstream	ss;
  bool			r;

  if ((bclt = (struct bunny_client*)bunny_malloc(sizeof(*bclt))) == NULL)
    return (NULL);
  ss << port;
  bclt->server = false;
  try
    {
      clt = new bpt::NetCom::Client;
      if (local == BPT_UNIX)
	r = clt->Start(std::string(host), ss.str(), bpt::NetAbs::INetAccess::UNIX);
      else
	r = clt->Start(std::string(host), ss.str(), bpt::NetAbs::INetAccess::TCP);
      if (r == false)
	{
	  bunny_free(bclt);
	  return (NULL);
	}
    }
  catch (...)
    {
      bunny_free(bclt);
      return (NULL);
    }
  if ((bclt->c = strdup(host)) == NULL)
    {
      delete clt;
      bunny_free(bclt);
      return (NULL);
    }
  bclt->a = (void*)clt;
  bclt->b = clt->GetFd();
  bclt->d = port;
  return ((t_bunny_client*)bclt);
}
