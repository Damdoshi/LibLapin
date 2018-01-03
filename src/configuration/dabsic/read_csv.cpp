// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

Decision		dabsic_read_csv(const char		*code,
					ssize_t			&i,
					SmallConf		&conf,
					SmallConf		&root)
{
  dabsic_read_separator(code, i);
  if (readtext(code, i, "[CSV") == false)
    return (BD_NOT_FOUND);
  dabsic_read_separator(code, i);

  if (csv_read(code, i, conf, root) != BD_OK)
    return (BD_ERROR);

  dabsic_read_separator(code, i);
  if (readtext(code, i, "]") == false)
    scream_error_if
      (return (BD_ERROR), BE_SYNTAX_ERROR,
       "The token ']' was expected to close the CSV scope on line %s:%d",
       "ressource,configuration,syntax",
       SmallConf::file_read.top().c_str(), whichline(code, i)
       );
  dabsic_read_separator(code, i);
  return (BD_OK);
}

