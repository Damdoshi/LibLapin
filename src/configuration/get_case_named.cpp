// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include	"lapin_private.h"

bool		bunny_configuration_get_case_named(t_bunny_configuration	*cnf,
						   t_bunny_configuration	**data,
						   const char			*pat,
						   ...)
{
  t_bunny_configuration *nod;
  char		buffer[1024 * 4];
  va_list	lst;

  va_start(lst, pat);
  vsnprintf(&buffer[0], sizeof(buffer), pat, lst);

  for (int i = 0; bunny_configuration_getf_node(cnf, &nod, "[%d]", i); ++i)
    if (!strcmp(bunny_configuration_get_name(nod), &buffer[0]))
      {
	if (data)
	  *data = nod;
	return (true);
      }
  return (false);
}

