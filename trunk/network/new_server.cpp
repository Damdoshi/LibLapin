// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include		"dep/NetCom.hpp"
#include		"lapin.h"

struct			bunny_server
{
  void			*a;
  int			b;
  uint16_t		c;
};

t_bunny_server		*bunny_new_server(uint16_t		port)
{
  bpt::NetCom::Server	*bptserv;
  struct bunny_server	*server;
  std::stringstream	ss;

  if ((server = (struct bunny_server*)bunny_malloc(sizeof(*server))) == NULL)
    return (NULL);
  ss << port;
  try
    {
      if ((bptserv = new (std::nothrow) bpt::NetCom::Server(ss.str())) == NULL)
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

