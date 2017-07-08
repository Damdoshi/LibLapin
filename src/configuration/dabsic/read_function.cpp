// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

bool			read_function(const char		*code,
				      ssize_t			&i,
				      SmallConf			&config)
{
  (void)config;
  if (!readtext(code, i, "]"))
    scream_error_if
      (return (false), BE_SYNTAX_ERROR,
       "%s code, %p config -> %s "
       "(A ']' closing the function section was expected on line %d)",
       code, &config, "false", whichline(code, i));
  return (true);
}

