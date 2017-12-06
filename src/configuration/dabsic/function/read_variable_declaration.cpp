// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

Decision		dabsic_read_variable_declaration(const char	*code,
							 ssize_t	&i,
							 Function	&func,
							 SmallConf	&funcnode,
							 SmallConf	&root)
{
  Function		&root_function = *funcnode.function;
  char			buffer[128];

  (void)func;
  (void)root;
  dabsic_read_separator(code, i);
  if (readtext(code, i, "string"))
    {
      dabsic_read_separator(code, i);
      if (getfieldname
	  (code, i, &buffer[0], sizeof(buffer), funcnode, true, true) == false)
	scream_error_if
	  (return (BD_ERROR), BE_SYNTAX_ERROR,
	   "Expected variable name after type 'string' on line %d",
	   "configuration,syntax",
	   whichline(code, i)
	   );
      if (root_function.local_variables.Access(&buffer[0]))
	scream_error_if
	  (return (BD_ERROR), BE_SYNTAX_ERROR,
	   "Variable name %s already taken on line %d",
	   "configuration,syntax",
	   &buffer[0], whichline(code, i)
	   );
      SmallConf		&nw = root_function.local_variables[&buffer[0]];

      dabsic_read_separator(code, i);
      if (readtext(code, i, "="))
	{
	  dabsic_read_separator(code, i);
	  if (readvalue(code, i, nw, ";") == false)
	    scream_error_if
	      (return (BD_ERROR), BE_SYNTAX_ERROR,
	       "Expected value after '=' token in variable assignment on line %d",
	       "configuration,syntax",
	       whichline(code, i)
	       );
	  if (nw.last_type == SmallConf::INTEGER || nw.last_type == SmallConf::DOUBLE)
	    scream_error_if
	      (return (BD_ERROR), BE_SYNTAX_ERROR,
	       "Invalid type for value assigned to %s: must be string, on line %d",
	       "configuration,syntax",
	       &buffer[0], whichline(code, i)
	       );
	}
      else
	nw.last_type = SmallConf::STRING;
      return (BD_OK);
    }

  if (readtext(code, i, "real"))
    {
      dabsic_read_separator(code, i);
      if (getfieldname
	  (code, i, &buffer[0], sizeof(buffer), funcnode, true, true) == false)
	scream_error_if
	  (return (BD_ERROR), BE_SYNTAX_ERROR,
	   "Expected variable name after type 'real' on line %d",
	   "configuration,syntax",
	   whichline(code, i)
	   );
      SmallConf		&nw = root_function.local_variables[&buffer[0]];

      dabsic_read_separator(code, i);
      if (readtext(code, i, "="))
	{
	  dabsic_read_separator(code, i);
	  if (readvalue(code, i, nw, ";") == false)
	    scream_error_if
	      (return (BD_ERROR), BE_SYNTAX_ERROR,
	       "Expected value after '=' token in variable assignment on line %d",
	       "configuration,syntax",
	       whichline(code, i)
	       );
	  if (nw.last_type != SmallConf::DOUBLE)
	    scream_error_if
	      (return (BD_ERROR), BE_SYNTAX_ERROR,
	       "Invalid type for value assigned to %s: must be string, on line %d",
	       "configuration,syntax",
	       &buffer[0], whichline(code, i)
	       );
	}
      else
	nw.last_type = SmallConf::DOUBLE;
      return (BD_OK);
    }

  if (readtext(code, i, "integer") || readtext(code, i, "int"))
    {
      dabsic_read_separator(code, i);
      if (getfieldname
	  (code, i, &buffer[0], sizeof(buffer), funcnode, true, true) == false)
	scream_error_if
	  (return (BD_ERROR), BE_SYNTAX_ERROR,
	   "Expected variable name after type 'real' on line %d",
	   "configuration,syntax",
	   whichline(code, i)
	   );
      SmallConf		&nw = root_function.local_variables[&buffer[0]];

      dabsic_read_separator(code, i);
      if (readtext(code, i, "="))
	{
	  dabsic_read_separator(code, i);
	  if (readvalue(code, i, nw, ";") == false)
	    scream_error_if
	      (return (BD_ERROR), BE_SYNTAX_ERROR,
	       "Expected value after '=' token in variable assignment on line %d",
	       "configuration,syntax",
	       whichline(code, i)
	       );
	  if (nw.last_type != SmallConf::INTEGER)
	    scream_error_if
	      (return (BD_ERROR), BE_SYNTAX_ERROR,
	       "Invalid type for value assigned to %s: must be string, on line %d",
	       "configuration,syntax",
	       &buffer[0], whichline(code, i)
	       );
	}
      else
	nw.last_type = SmallConf::INTEGER;
      return (BD_OK);
    }

  return (BD_NOT_FOUND);
}
