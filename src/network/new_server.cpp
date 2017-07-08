// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include		"deps/NetCom.hpp"
#include		"lapin_private.h"

struct			bunny_server
{
  size_t		server;
  void			*a;
  int			b;
  uint16_t		c;
};

#define			PATTERN		"%d port, %d protocol -> %p"

t_bunny_server		*bunny_new_server_opt(uint16_t		port,
					      t_bunny_protocol	local)
{
  bpt::NetCom::Server	*bptserv;
  struct bunny_server	*server;
  std::stringstream	ss;
  bool			r;
  int			err;
  
  if ((server = (struct bunny_server*)bunny_malloc(sizeof(*server))) == NULL)
    scream_error_if(return (NULL), bunny_errno, PATTERN, port, local, server);
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
	  err = bunny_errno;
	  bunny_free(server);
	  scream_error_if(return (NULL), err, PATTERN, port, local, (void*)NULL);
	}
    }
  catch (...)
    {
      bunny_free(server);
      scream_error_if(return (NULL), ENOMEM, PATTERN, port, local, (void*)NULL);
    }
  server->a = (void*)bptserv;
  server->b = bptserv->GetFd();
  server->c = port;
  scream_log_if(PATTERN, port, local, server);
  return ((t_bunny_server*)server);
}
