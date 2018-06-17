// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include	"lapin_private.h"

ssize_t		bunny_configuration_casesf(const t_bunny_configuration	*cnf,
					   const char			*pat,
					   ...)
{
  t_bunny_configuration *got;
  char		buffer[1024 * 4];
  va_list	lst;
  bool		cmode;

  cmode = SmallConf::create_mode;
  SmallConf::create_mode = false;

  va_start(lst, pat);
  vsnprintf(&buffer[0], sizeof(buffer), pat, lst);
  if ((got = bunny_configuration_go_get_node
       ((t_bunny_configuration*)cnf, &buffer[0])) == NULL)
    {
      SmallConf::create_mode = cmode;
      return (-1);
    }
  SmallConf::create_mode = cmode;
  return (bunny_configuration_get_nbr_case(got));
}

