// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include		<string.h>
#include		"deps/NetCom.hpp"
#include		"lapin_private.h"

struct			bunny_client
{
  size_t		server;
  void			*a;
  int			b;
  char			*c;
  uint16_t		d;
};

#define			PATTERN		"%s host, %d port, %d protocol -> %p"

t_bunny_client		*bunny_new_client_opt(const char	*host,
					      uint16_t		port,
					      t_bunny_protocol	local)
{
  struct bunny_client	*bclt;
  bpt::NetCom::Client	*clt;
  std::stringstream	ss;
  bool			r;
  int			err;

  if ((bclt = (struct bunny_client*)bunny_malloc(sizeof(*bclt))) == NULL)
    scream_error_if(return (NULL), bunny_errno, PATTERN, "network", host, port, local, bclt);
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
	  err = bunny_errno;
	  bunny_free(bclt);
	  scream_error_if(return (NULL), err, PATTERN, "network", host, port, local, (void*)NULL);
	}
    }
  catch (...)
    {
      bunny_free(bclt);
      scream_error_if(return (NULL), ENOMEM, PATTERN, "network", host, port, local, (void*)NULL);
    }
  if ((bclt->c = bunny_strdup(host)) == NULL)
    {
      delete clt;
      bunny_free(bclt);
      scream_error_if(return (NULL), ENOMEM, PATTERN, "network", host, port, local, (void*)NULL);
    }
  bclt->a = (void*)clt;
  bclt->b = clt->GetFd();
  bclt->d = port;
  scream_log_if(PATTERN, "network", host, port, local, bclt);
  return ((t_bunny_client*)bclt);
}
