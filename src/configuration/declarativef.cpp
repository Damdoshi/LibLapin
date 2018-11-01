// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include	"lapin_private.h"

bool			bunny_configuration_declarativef(t_bunny_configuration		*cnf,
							 const char			*fmt,
							 ...)
{
  char		buffer[1024 * 4];
  t_bunny_configuration *nod;
  va_list	lst;
  int		x;

  va_start(lst, fmt);
  vsnprintf(&buffer[0], sizeof(buffer), fmt, lst);
  if ((nod = bunny_configuration_go_get_node(cnf, &buffer[0])) == NULL)
    return (false);
  if (bunny_configuration_get_int(nod, &x) == false)
    return (true);
  return (!!x);
}

