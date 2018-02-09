// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

Decision		json_read_array(const char		*code,
					ssize_t			&i,
					SmallConf		&conf,
					SmallConf		&root)
{
  int			line;

  json_read_separator(code, i);
  line = whichline(code, i);
  if (readtext(code, i, "[") == false)
    return (BD_NOT_FOUND);

  json_read_separator(code, i);

  if (readtext(code, i, "]"))
    return (BD_OK);

  if (json_read_inside_array(code, i, conf, root) == BD_ERROR)
    return (BD_ERROR);
  json_read_separator(code, i);

  if (readtext(code, i, "]") == false)
    scream_error_if
      (return (BD_ERROR), BE_SYNTAX_ERROR,
       "The ']' token was expected to close the array opened on line %d, on line %s:%d",
       "ressource,configuration,syntax",
       line, SmallConf::file_read.top().c_str(), whichline(code, i)
       );
  return (BD_OK);
}

