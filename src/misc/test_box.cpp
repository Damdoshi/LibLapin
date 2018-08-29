// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

bool			bunny_test_box(const void	*_data,
				       off_t		offset,
				       off_t		maxlen,
				       const char	*str)
{
  const char		*data = (const char*)_data;

  if (offset + 4 >= maxlen)
    return (false);
  if (bunny_strnlen(str, 4) != 4)
    return (false);
  return (strncmp(&data[offset], str, 4) == 0);
}
