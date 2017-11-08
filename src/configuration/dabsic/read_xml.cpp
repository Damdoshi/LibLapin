// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

Decision		dabsic_read_xml(const char		*code,
					ssize_t			&i,
					SmallConf		&conf,
					SmallConf		&root)
{
  dabsic_read_separator(code, i);
  if (readtext(code, i, "<xml>") == false)
    return (BD_NOT_FOUND);
  dabsic_read_separator(code, i);

  if (dabsic_read_inside_xml(code, i, conf, root) == BD_ERROR)
    return (BD_ERROR);

  dabsic_read_separator(code, i);
  if (readtext(code, i, "</xml>") == false)
    scream_error_if
      (return (BD_ERROR), BE_SYNTAX_ERROR,
       "The token '</xml>' was expected to close the XML scope on line %d",
       whichline(code, i)
       );
  dabsic_read_separator(code, i);
  return (BD_OK);
}

