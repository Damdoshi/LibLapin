// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include	"lapin_private.h"

#define		PATTERN		"%p -> %s"

const char	*bunny_configuration_get_address(const t_bunny_configuration *config)
{
  SmallConf	*conf = (SmallConf*)config;

  return (conf->address.c_str());
}

bool			bunny_configuration_addressf(t_bunny_configuration		*config,
						     const char				**addr,
						     const char				*pat,
						     ...)
{
  t_bunny_configuration *got;
  char		buffer[1024 * 4];
  va_list	lst;

  va_start(lst, pat);
  vsnprintf(&buffer[0], sizeof(buffer), pat, lst);
  if ((got = bunny_configuration_go_get_node(config, &buffer[0])) == NULL)
    return (false);
  if (addr)
    *addr = bunny_configuration_get_address(got);
  return (true);
}

