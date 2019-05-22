// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<unistd.h>
#include		"lapin_private.h"

const char		*bunny_configuration_resolve_path(const char	*file)
{
  static char		buffer[256];
  std::list<std::string>::reverse_iterator it;

  for (it = SmallConf::file_path.rbegin(); it != SmallConf::file_path.rend(); ++it)
    {
      size_t		siz;

      if (*it != "")
	snprintf(&buffer[0], sizeof(buffer), "%s/%s", it->c_str(), file);
      else
	snprintf(&buffer[0], sizeof(buffer), "%s", file);
      if (access(&buffer[0], R_OK) == 0)
	return (&buffer[0]);
    }
  return (NULL);
}
