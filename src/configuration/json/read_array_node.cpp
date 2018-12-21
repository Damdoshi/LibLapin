// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
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

  if (expr_read_expression(code, i, conf[conf.Size()], Expression::BEOF_TERNARY) == BD_ERROR)
    return (BD_ERROR);
  json_read_separator(code, i);
  return (BD_OK);
}

