// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

Decision		dabsic_read_inside_scope(const char		*code,
						 ssize_t		&i,
						 SmallConf		&conf,
						 SmallConf		&root)
{
  Decision		ret;

  conf.construct = SmallConf::MAP;
  if (dabsic_read_field_value(code, i, conf, root) == BD_ERROR)
    return (BD_ERROR);
  while (code[i] != '\0' && code[i] != ']')
    if ((ret = dabsic_read_field(code, i, conf, root)) != BD_OK)
      {
	if (code[i] != '\0' && code[i] != ']')
	  {
	    scream_error_if
	    (return (BD_ERROR), BE_SYNTAX_ERROR,
	     "An end of scope was expected on line %s:%d",
	     "ressource,configuration,syntax",
	     SmallConf::file_read.top().c_str(), whichline(code, i)
	     );
	  }
	return (ret);
      }
  return (BD_OK);
}

