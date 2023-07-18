// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2020
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

Decision		dabsic_read_scope(const char		*code,
					  ssize_t		&i,
					  SmallConf		&conf,
					  SmallConf		&root)
{
  char			buffer[128];
  int			init_index;

  dabsic_read_separator(code, i);
  init_index = i;
  if (bunny_check_text(code, &i, "[")
      && bunny_check_text(code, &i, "[]") == false
      && bunny_check_text(code, &i, "[.]") == false)
    {
      readtext(code, i, "[");
      if (getfieldname(code, i, &buffer[0], sizeof(buffer), conf, true, false))
	{
	  if (conf.given_name)
	    scream_error_if
	      (return (BD_ERROR), BE_SYNTAX_ERROR,
	       "Setting a new name to an already named node on line %s:%d",
	       "ressource,configuration,syntax",
	       SmallConf::file_read.top().c_str(), whichline(code, i)
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
  else if (readtext(code, i, "[Scope") == false)
    return (BD_NOT_FOUND);
  dabsic_read_separator(code, i);

  if (dabsic_read_inside_scope(code, i, conf, root) == BD_ERROR)
    return (BD_ERROR);

  dabsic_read_separator(code, i);
  if (readtext(code, i, "]") == false)
    scream_error_if
      (return (BD_ERROR), BE_SYNTAX_ERROR,
       "The token ']' was expected to close the dictionnary "
       "scope opened on line %d, on line %s:%d",
       "ressource,configuration,syntax",
       whichline(code, init_index), SmallConf::file_read.top().c_str(), whichline(code, i)
       );
  dabsic_read_separator(code, i);
  return (BD_OK);
}

