// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include		"deps/NetCom.hpp"
#include		"lapin.h"

struct			bunny_server
{
  size_t		server;
  void			*a;
  int			b;
  uint16_t		c;
};

t_bunny_server		*bunny_new_server_opt(uint16_t		port,
					      t_bunny_protocol	local)
{
  bpt::NetCom::Server	*bptserv;
  struct bunny_server	*server;
  std::stringstream	ss;
  bool			r;

  if ((server = (struct bunny_server*)bunny_malloc(sizeof(*server))) == NULL)
    return (NULL);
  server->server = true;
  ss << port;
  try
    {
      bptserv = new bpt::NetCom::Server;
      if (local == BPT_UNIX)
	r = bptserv->Start(ss.str(), bpt::NetAbs::INetAccess::UNIX);
      else
	r = bptserv->Start(ss.str(), bpt::NetAbs::INetAccess::TCP);
      if (r == false)
	{
	  bunny_free(server);
	  return (NULL);
	}
    }
  catch (...)
    {
      bunny_free(server);
      return (NULL);
    }
  server->a = (void*)bptserv;
  server->b = bptserv->GetFd();
  server->c = port;
  return ((t_bunny_server*)server);
}
