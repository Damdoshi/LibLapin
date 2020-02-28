// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2020
//
// Lapin library

#include	<string.h>
#include	"lapin_private.h"

t_bunny_configuration	*_bunny_read_data(const char		*code,
					  size_t		len,
					  t_bunny_configuration	*config)
{
  const unsigned char	*ptr = (const unsigned char*)code;
  size_t		i;

  for (i = 0; i < len; ++i)
    if (bunny_configuration_setf_int(config, ((unsigned int)ptr[i]) & 0xFF, "[%zu]", i) == false)
      return (NULL);
  return (config);
}

