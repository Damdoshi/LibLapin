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
	   "A name was expected line %d",
	   whichline(code, i)
	   );
      return (NULL);
    }
  if ((newnode = &config[&buffer[0]]) == NULL)
    scream_error_if
      (return (NULL), ENOMEM,
       "Memory exhausted while processing line %d",
       whichline(code, i)
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
	  dabsic_read_separator(code, i);
	  if (getfieldname(code, i, &buffer[0], sizeof(buffer), *newnode, true, true) == false)
	    {
	      delete newnode;
	      scream_error_if
		(return (NULL), BE_SYNTAX_ERROR,
		 "The token ')' was expected to close the prototype on line %d",
		 whichline(code, i)
		 );
	    }
	  (*newnode)[".parameters"][iteration++].SetString(&buffer[0]);
	  dabsic_read_separator(code, i);
	}
      while (readtext(code, i, ","));
      dabsic_read_separator(code, i);
      if (readtext(code, i, ")") == false)
	{
	  scream_error_if
	    (return (NULL), BE_SYNTAX_ERROR,
	     "The token ')' was expected to close the prototype on line %d",
	     whichline(code, i)
	     );
	  delete newnode;
	}
    }
  return (newnode);
}

