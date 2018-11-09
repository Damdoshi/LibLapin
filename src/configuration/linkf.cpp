// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include	"lapin_private.h"

bool		bunny_configuration_linkf(t_bunny_configuration	*cnf,
					  const char		*pat,
					  ...)
{
  char		buffer[1024 * 4];
  t_bunny_configuration *got;
  va_list	lst;
  bool		cmode;

  cmode = SmallConf::create_mode;
  SmallConf::create_mode = true;

  va_start(lst, pat);
  vsnprintf(&buffer[0], sizeof(buffer), pat, lst);
  if ((got = bunny_configuration_go_get_node(cnf, &buffer[0])) == NULL)
    {
      SmallConf::create_mode = cmode;
      return (false);
    }
  ((SmallConf*)got)->Link((SmallConf*)cnf);
  SmallConf::create_mode = cmode;
  return (true);
}

void		bunny_configuration_link(t_bunny_configuration	*dst,
					 t_bunny_configuration	*ori)
{
  SmallConf	*a = (SmallConf*)dst;
  SmallConf	*b = (SmallConf*)ori;

  b->Link(a);
}

