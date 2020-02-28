// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2020
//
// Lapin library

#include	<string.h>
#include	"lapin_private.h"

t_bunny_configuration	*_bunny_read_text(const char			*code,
					  t_bunny_configuration		*config)
{
  if (bunny_configuration_setf_string(config, code, ".") == false)
    return (NULL);
  return (config);
}

char			*_bunny_write_text(t_bunny_configuration	*config)
{
  const char		*str;

  if (!bunny_configuration_getf_string(config, &str, "."))
    return (NULL);
  return (bunny_strdup(str));
}
