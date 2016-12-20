// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Bibliotheque Lapin

#include		<string.h>
#include		"lapin_private.h"

extern char		*ini_last_error;

t_bunny_ini		*bunny_read_ini(const char		*str)
{
  if (str == NULL)
    return (NULL);
  bpt::Ini		*ini = new (std::nothrow) bpt::Ini;

  if (ini == NULL)
    return (NULL);
  std::string		fil = str;

  try
    {
      if (ini->Read(fil) == false)
	{
	  if (ini_last_error != NULL)
	    free(ini_last_error);
	  ini_last_error = strdup(ini->errmsg.c_str());
	  delete ini;
	  return (NULL);
	}
    }
  catch (...)
    {
      return (NULL);
    }
  return ((t_bunny_ini*)ini);
}
