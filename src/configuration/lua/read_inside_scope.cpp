// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

Decision		lua_read_inside_scope(const char	*code,
					      ssize_t		&i,
					      SmallConf		&conf,
					      SmallConf		&root)
{
  do
    {
      lua_read_separator(code, i);
      if (lua_read_field(code, i, conf, root) == BD_ERROR)
	return (BD_ERROR);
      lua_read_separator(code, i);
    }
  while (readtext(code, i, ","));
  lua_read_separator(code, i);
  return (BD_OK);
}

