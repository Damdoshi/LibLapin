// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

Decision		json_read_field(const char		*code,
					ssize_t			&i,
					SmallConf		&conf,
					SmallConf		&root)
{
  char			buffer[128];
  SmallConf		*newconf;

  json_read_separator(code, i);

  if (code[i] == '@')
    {
      if (_bunny_handle_directive
	  (code, i, &conf, &root, json_read_separator) == false)
	return (BD_ERROR);
      json_read_separator(code, i);
      return (BD_OK);
    }

  if (readstring(code, i, &buffer[0], sizeof(buffer)) == false)
    scream_error_if
      (return (BD_ERROR), BE_SYNTAX_ERROR,
       "A c-string key was expected on line %d",
       whichline(code, i)
       );
  newconf = &conf[&buffer[0]];
  json_read_separator(code, i);

  // Not standard, but considering DABSIC, it is ok to have empty fields
  if (readtext(code, i, ":") == false)
    return (BD_OK);
  json_read_separator(code, i);

  if (code[i] == '{')
    return (json_read_scope(code, i, *newconf, root));

  if (code[i] == '[')
    return (json_read_array(code, i, *newconf, root));

  if (code[i] == '@')
    {
      if (_bunny_handle_directive
	  (code, i, newconf, &root, json_read_separator) == false)
	return (BD_ERROR);
      json_read_separator(code, i);
      return (BD_OK);
    }

  if (readvalue(code, i, *newconf, ",") == false)
    scream_error_if
      (return (BD_ERROR), BE_SYNTAX_ERROR,
       "A scope, array or value was expected on line %d",
       whichline(code, i)
       );
  json_read_separator(code, i);
  return (BD_OK);
}

