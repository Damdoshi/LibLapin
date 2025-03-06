// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<unistd.h>
#include		"lapin_private.h"

bool			bunny_configuration_resolve_path(const char	*file,
							 char		*buffer,
							 int		size_buffer)
{
  std::list<std::string>::reverse_iterator it;

  for (it = SmallConf::file_path.rbegin(); it != SmallConf::file_path.rend(); ++it)
    {
      size_t		siz;

      if (*it != "")
	siz = snprintf(&buffer[0], size_buffer, "%s/%s", it->c_str(), file);
      else
	siz = snprintf(&buffer[0], size_buffer, "%s", file);
      if (siz == size_buffer)
	continue ;
      if (access(&buffer[0], R_OK) == 0)
	return (true);
    }
  return (false);
}
