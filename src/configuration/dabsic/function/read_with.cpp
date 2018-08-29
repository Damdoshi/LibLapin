// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

Decision		dabsic_read_with(const char	*code,
					 ssize_t	&i,
					 Function	&func,
					 SmallConf	&funcnode,
					 SmallConf	&root)
{
  if (readaddress(code, i, func.value) == false)
    scream_error_if
      (return (BD_ERROR), BE_SYNTAX_ERROR,
       "An address was expected after 'with' on line %s:%d",
       "ressource,configuration,syntax",
       SmallConf::file_read.top().c_str(), whichline(code, i)
       );
  func.value.name = func.value.original_value;
  func.value.symbol = true;
  dabsic_read_separator(code, i);

  if (dabsic_read_inside_function(code, i, &func, funcnode, root) == BD_ERROR)
    return (BD_ERROR);

  if (readtextcase(code, i, "EndWith"))
    {
      dabsic_read_separator(code, i);
      return (BD_OK);
    }
  scream_error_if
    (return (BD_ERROR), BE_SYNTAX_ERROR,
     "The EndWith token was expected on line %s:%d",
     "ressource,configuration,syntax",
     SmallConf::file_read.top().c_str(), whichline(code, i)
     );
}

