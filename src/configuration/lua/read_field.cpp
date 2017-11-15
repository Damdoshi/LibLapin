// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

Decision		lua_read_field(const char		*code,
				       ssize_t			&i,
				       SmallConf		&conf,
				       SmallConf		&root)
{
  char			buffer[128];
  SmallConf		*newconf;

  lua_read_separator(code, i);

  if (code[i] == '@')
    {
      if (_bunny_handle_directive
	  (code, i, &conf, &root, lua_read_separator) == false)
	return (BD_ERROR);
      lua_read_separator(code, i);
      return (BD_OK);
    }

  if (readtext(code, i, "["))
    {
      char		*x;

      strtol(&code[i], &x, 0);
      if (x != &code[i])
	{
	  strncpy(&buffer[0], &code[i], x - &code[i]);
	  buffer[x - &code[i]] = '\0';
	}
      else if (readstring(code, i, &buffer[0], sizeof(buffer)) == false)
	scream_error_if
	  (return (BD_ERROR), BE_SYNTAX_ERROR,
	   "An integer or a CString was expected after the '[' key token on line %d",
	   whichline(code, i)
	   );
      if (readtext(code, i, "]") == false)
	scream_error_if
	  (return (BD_ERROR), BE_SYNTAX_ERROR,
	   "The token ']' was expected after opening a integer key on line %d",
	   whichline(code, i)
	   );
    }
  else if (getfieldname(code, i, &buffer[0], sizeof(buffer), conf, true, true) == false)
    scream_error_if
      (return (BD_ERROR), BE_SYNTAX_ERROR,
       "A field name or integer between '[]' was expected on line %d",
       whichline(code, i)
       );

  newconf = &conf[&buffer[0]];
  lua_read_separator(code, i);

  // Not standard, but considering DABSIC, it is ok to have empty fields
  if (readtext(code, i, "=") == false)
    return (BD_OK);
  lua_read_separator(code, i);

  if (code[i] == '{')
    return (lua_read_scope(code, i, *newconf, root));

  if (code[i] == '[')
    return (lua_read_array(code, i, *newconf, root));

  if (code[i] == '@')
    {
      if (_bunny_handle_directive
	  (code, i, newconf, &root, lua_read_separator) == false)
	return (BD_ERROR);
      lua_read_separator(code, i);
      return (BD_OK);
    }

  if (readvalue(code, i, *newconf, ",") == false)
    scream_error_if
      (return (BD_ERROR), BE_SYNTAX_ERROR,
       "A scope, array or value was expected on line %d",
       whichline(code, i)
       );
  lua_read_separator(code, i);
  return (BD_OK);
}

