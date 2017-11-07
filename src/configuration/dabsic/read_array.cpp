// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

Decision		dabsic_read_array(const char		*code,
					  ssize_t		&i,
					  SmallConf		&conf,
					  SmallConf		&root)
{
  char			buffer[128];
  int			line;

  dabsic_read_separator(code, i);
  line = whichline(code, i);
  if (readtext(code, i, "{"))
    {
      if (getfieldname(code, i, &buffer[0], sizeof(buffer), conf, true, false))
	{
	  if (conf.given_name)
	    scream_error_if
	      (return (BD_ERROR), BE_SYNTAX_ERROR,
	       "Setting a new name to an already named node on line %d",
	       whichline(code, i)
	       );
	  if (conf.father->nodes.find(conf.name) != conf.father->nodes.end())
	    {
	      conf.father->nodes.erase(conf.name);
	      conf.father->nodes[&buffer[0]] = &conf;
	    }
	  conf.name = &buffer[0];
	  conf.given_name = true;
	}
    }
  else if (readtext(code, i, "[Data") == false && readtext(code, i, "[Array") == false)
    return (BD_NOT_FOUND);
  dabsic_read_separator(code, i);

  if (dabsic_read_inside_array(code, i, conf, root) == BD_ERROR)
    return (BD_ERROR);

  dabsic_read_separator(code, i);
  if (readtext(code, i, "]") == false && readtext(code, i, "}") == false)
    scream_error_if
      (return (BD_ERROR), BE_SYNTAX_ERROR,
       "The token ']' or '}' was expected to close the "
       "array scope opened on line %d, on line %d",
       line, whichline(code, i)
       );
  dabsic_read_separator(code, i);
  return (BD_OK);
}

