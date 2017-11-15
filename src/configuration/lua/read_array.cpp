// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

Decision		lua_read_array(const char		*code,
				       ssize_t			&i,
				       SmallConf		&conf,
				       SmallConf		&root)
{
  int			line;

  lua_read_separator(code, i);
  line = whichline(code, i);
  if (readtext(code, i, "[") == false)
    return (BD_NOT_FOUND);

  lua_read_separator(code, i);
  if (lua_read_inside_array(code, i, conf, root) == BD_ERROR)
    return (BD_ERROR);
  lua_read_separator(code, i);

  if (readtext(code, i, "]") == false)
    scream_error_if
      (return (BD_ERROR), BE_SYNTAX_ERROR,
       "The ']' token was expected to close the array opened on line %d, on line %d",
       line, whichline(code, i)
       );
  return (BD_OK);
}

