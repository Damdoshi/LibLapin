// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

Decision		json_read_array_node(const char		*code,
					     ssize_t		&i,
					     SmallConf		&conf,
					     SmallConf		&root)
{
  json_read_separator(code, i);
  if (code[i] == '{')
    return (json_read_scope(code, i, conf[conf.Size()], root));

  if (code[i] == '[')
    return (json_read_array(code, i, conf[conf.Size()], root));

  if (code[i] == '@')
    {
      if (_bunny_handle_directive
	  (code, i, &conf, &root, json_read_separator) == false)
	return (BD_ERROR);
      json_read_separator(code, i);
      return (BD_OK);
    }

  if (readvalue(code, i, conf[conf.Size()], ",") == false)
    scream_error_if
      (return (BD_ERROR), BE_SYNTAX_ERROR,
       "A scope, array or value was expected on line %d",
       whichline(code, i)
       );
  json_read_separator(code, i);
  return (BD_OK);
}

