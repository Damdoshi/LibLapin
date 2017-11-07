// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

Decision		dabsic_read_litterals(const char		*code,
					      ssize_t			&i,
					      SmallConf			&conf,
					      SmallConf			&root)
{
  int			iteration;

  (void)root;
  if (conf.construct == SmallConf::ARRAY)
    {
      dabsic_read_separator(code, i);
      if (readvalue(code, i, conf, ",") == false)
	scream_error_if
	  (return (BD_ERROR), BE_SYNTAX_ERROR,
	   "An expression or value was expected on line %d",
	   whichline(code, i)
	   );
      dabsic_read_separator(code, i);
    }
  iteration = 0;
  do
    {
      dabsic_read_separator(code, i);
      if (readvalue(code, i, conf[iteration++], ",") == false)
	scream_error_if
	  (return (BD_ERROR), BE_SYNTAX_ERROR,
	   "An expression or value was expected on line %d",
	   whichline(code, i)
	   );
      dabsic_read_separator(code, i);
    }
  while (readtext(code, i, ","));
  dabsic_read_separator(code, i);
  return (BD_OK);
}

