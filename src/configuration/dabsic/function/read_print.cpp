// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

Decision		dabsic_read_print(const char		*code,
					  ssize_t		&i,
					  Function		&func,
					  SmallConf		&funcnode,
					  SmallConf		&root)
{
  (void)funcnode;
  (void)root;
  do
    {
      if (readvalue(code, i, func.value[func.value.Size()], ",") == false)
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
