// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

SmallConf		*dabsic_function_type(const char		*code,
					      ssize_t			&i,
					      SmallConf			*newnode)
{
  if (readtext(code, i, ":"))
    {
      SmallConf::Type	type = SmallConf::NOTYPE;

      dabsic_read_separator(code, i);
      if (readtext(code, i, "string"))
	type = SmallConf::STRING;
      else if (readtext(code, i, "real"))
	type = SmallConf::DOUBLE;
      else if (readtext(code, i, "node"))
	type = SmallConf::RAWSTRING;
      else if (readtext(code, i, "integer") || readtext(code, i, "int"))
	type = SmallConf::INTEGER;
      else if (readtext(code, i, "void") == false)
	scream_error_if
	  (return (NULL), BE_SYNTAX_ERROR,
	   "A return type was expected after ':' on line %s:%d",
	   "configuration,syntax",
	   SmallConf::file_read.top().c_str(), whichline(code, i)
	   );
      dabsic_read_separator(code, i);
      if (type != SmallConf::NOTYPE)
	newnode->last_type = type;
      else
	newnode->have_value = false;
    }
  dabsic_read_separator(code, i);
  return (newnode);
}

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

  // READ PARAMETERS
  if (readtext(code, i, "("))
    {
      (*newnode)[".prototype"].construct = SmallConf::ARRAY;
      dabsic_read_separator(code, i);
      if (readtext(code, i, ")"))
	{
	  dabsic_read_separator(code, i);
	  // READ RETURN TYPE
	  if (dabsic_function_type(code, i, newnode) == NULL)
	    {
	      delete newnode;
	      return (NULL);
	    }
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
	  else if (readtext(code, i, "node"))
	    type = SmallConf::RAWSTRING;
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
	  SmallConf		&pr = (*newnode)[".prototype"][iteration++];

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
      dabsic_read_separator(code, i);
      // READ RETURN TYPE
      if (dabsic_function_type(code, i, newnode) == NULL)
	{
	  delete newnode;
	  return (NULL);
	}
    }
  dabsic_read_separator(code, i);
  ssize_t j = i;

  newnode->is_const = SmallConf::NO_POLITIC;
  newnode->is_solid = SmallConf::NO_POLITIC;
  newnode->is_eternal = SmallConf::NO_POLITIC;
  do
    {
      i = j;
      if (readtextcase(code, j, "const"))
	{
	  if (readtextcase(code, j, "!") == false)
	    newnode->is_const = SmallConf::LOCAL_POLITIC;
	  else
	    newnode->is_const = SmallConf::RECURSIVE_POLITIC;
	}

      if (readtextcase(code, j, "solid"))
	{
	  if (readtextcase(code, j, "!") == false)
	    newnode->is_solid = SmallConf::LOCAL_POLITIC;
	  else
	    newnode->is_solid = SmallConf::RECURSIVE_POLITIC;
	}

      if (readtextcase(code, j, "eternal"))
	{
	  if (readtextcase(code, j, "!") == false)
	    newnode->is_eternal = SmallConf::LOCAL_POLITIC;
	  else
	    newnode->is_eternal = SmallConf::RECURSIVE_POLITIC;
	}

      dabsic_read_separator(code, j);
    }
  while (i != j);
  i = j;
  return (newnode);
}

