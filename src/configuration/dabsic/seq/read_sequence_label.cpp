// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

bool			dabsic_read_sequence_label(const char		*code,
						   ssize_t		&i,
						   std::string		&out)
{
  SmallConf		unused;
  char			buffer[128];
  ssize_t		j = i;

  dabsic_read_separator(code, j);
  if (getfieldname(code, j, &buffer[0], sizeof(buffer), unused, true, false) == false)
    return (false);
  dabsic_read_separator(code, j);
  if (readtext(code, j, ":") == false)
    return (false);
  dabsic_read_separator(code, j);

  i = j;
  out = &buffer[0];
  return (true);
}

