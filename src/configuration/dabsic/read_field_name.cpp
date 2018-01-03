// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

SmallConf		*dabsic_field_name(const char			*code,
					   ssize_t			&i,
					   SmallConf			&config,
					   bool				manda)
{
  SmallConf		*newnode;
  char			buffer[128];
  int			iteration;

  dabsic_read_separator(code, i);
  if (getfieldname(code, i, &buffer[0], sizeof(buffer), config, true, manda) == false)
    {
      if (manda)
	scream_error_if
	  (return (NULL), BE_SYNTAX_ERROR,
	   "A name was expected line %s:%d",
	   "configuration,syntax",
	   SmallConf::file_read.top().c_str(), whichline(code, i)
	   );
      return (NULL);
    }
  if ((newnode = &config[&buffer[0]]) == NULL)
    scream_error_if
      (return (NULL), ENOMEM,
       "Memory exhausted while processing line %s:%d",
       "configuration,syntax",
       SmallConf::file_read.top().c_str(), whichline(code, i)
       );
  dabsic_read_separator(code, i);

  if (readtext(code, i, "("))
    {
      dabsic_read_separator(code, i);
      if (readtext(code, i, ")"))
	{
	  dabsic_read_separator(code, i);
	  return (newnode);
	}
      iteration = 0;
      do
	{
	  SmallConf::Type	type;

	  dabsic_read_separator(code, i);
	  if (readtext(code, i, "string"))
	    type = SmallConf::STRING;
	  else if (readtext(code, i, "real"))
	    type = SmallConf::DOUBLE;
	  else if (readtext(code, i, "integer") || readtext(code, i, "int"))
	    type = SmallConf::INTEGER;
	  else
	    scream_error_if
	      (return (NULL), BE_SYNTAX_ERROR,
	       "A parameter type was expected on line %s:%d",
	       "configuration,syntax",
	       SmallConf::file_read.top().c_str(), whichline(code, i)
	       );
	  dabsic_read_separator(code, i);
	  if (getfieldname(code, i, &buffer[0], sizeof(buffer), *newnode, true, true) == false)
	    {
	      delete newnode;
	      scream_error_if
		(return (NULL), BE_SYNTAX_ERROR,
		 "The token ')' was expected to close the prototype on line %s:%d",
		 "configuration,syntax",
		 SmallConf::file_read.top().c_str(), whichline(code, i)
		 );
	    }
	  SmallConf		&pr = (*newnode)[".parameters"][iteration++];

	  pr.name = &buffer[0];
	  pr.last_type = type;
	  dabsic_read_separator(code, i);
	  if (readtext(code, i, "="))
	    {
	      dabsic_read_separator(code, i);
	      if (expr_read_expression
		  (code, i, pr, Expression::BEOF_TERNARY) == BD_ERROR)
		{
		  delete newnode;
		  return (NULL);
		}
	      dabsic_read_separator(code, i);
	    }
	}
      while (readtext(code, i, ","));
      dabsic_read_separator(code, i);
      if (readtext(code, i, ")") == false)
	{
	  scream_error_if
	    (return (NULL), BE_SYNTAX_ERROR,
	     "The token ')' was expected to close the prototype on line %s:%d",
	     "configuration,syntax",
	     SmallConf::file_read.top().c_str(), whichline(code, i)
	     );
	  delete newnode;
	}
    }
  return (newnode);
}

