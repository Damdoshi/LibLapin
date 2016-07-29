// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include		<string.h>
#include		"dep/NetCom.hpp"
#include		"lapin.h"

struct			bunny_client
{
  void			*a;
  int			b;
  char			*c;
  uint16_t		d;
};

t_bunny_client		*bunny_new_client(const char		*host,
					  uint16_t		port)
{
  struct bunny_client	*bclt;
  bpt::NetCom::Client	*clt;
  std::stringstream	ss;

  if ((bclt = (struct bunny_client*)bunny_malloc(sizeof(*bclt))) == NULL)
    return (NULL);
  ss << port;
  try
    {
      if ((clt = new (std::nothrow)bpt::NetCom::Client(std::string(host), ss.str())) == NULL)
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

