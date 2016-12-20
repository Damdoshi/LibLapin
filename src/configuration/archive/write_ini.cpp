// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include		<string.h>
#include		"lapin_private.h"

extern char		*ini_last_error;

char			*bunny_write_ini(const t_bunny_ini	*_ini)
{
  if (_ini == NULL)
    return (NULL);
  bpt::Ini		*ini = (bpt::Ini*)_ini;
  std::stringstream	ss;
  char			*str;

  ini->Save(ss);
  if ((str = (char*)bunny_malloc((ss.str().size() + 1) * sizeof(*str))) == NULL)
    return (NULL);
  return (strcpy(str, ss.str().c_str()));
}

