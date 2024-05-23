// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

Decision		dabsic_read_sequence_line(const char		*code,
						  ssize_t		&i,
						  Sequence::Line	&line,
						  SmallConf		&root)
{
  char			buffer[128];
  size_t		it;

  dabsic_read_separator(code, i);
  if (getfieldname(code, i, &buffer[0], sizeof(buffer), root, true, false) == false)
    return (BD_NOT_FOUND);
  line.command = &buffer[0];

  skipspace_inline(code, i);

  it = 0;
  line.nbr_parameters = 0;
  do
    {
      if (it >= line.parameters.size())
	line.parameters.resize(it + 4);
      if (it != 0)
	dabsic_read_separator(code, i);
      if (readvalue(code, i, line.parameters[it], ",") == false)
	{
	  if (it != 0)
	    scream_error_if
	      (return (BD_ERROR), BE_SYNTAX_ERROR,
	       "A value was expected after ',' on line %s:%d",
	       "configuration,syntax",
	       SmallConf::file_read.top().c_str(), whichline(code, i)
	       );
	  return (BD_OK);
	}
      else
	line.nbr_parameters = ++it;
      dabsic_read_separator(code, i);
    }
  while (readtext(code, i, ","));
  dabsic_read_separator(code, i);
  return (BD_OK);
}

