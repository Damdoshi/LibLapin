// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

Decision		dabsic_read_inside_array(const char		*code,
						 ssize_t		&i,
						 SmallConf		&conf)
{
  Decision		ret;
  int			iteration;

  dabsic_read_separator(code, i);
  if (readtext(code, i, "="))
    {
      dabsic_read_separator(code, i);
      if (readvalue(code, i, conf, NULL) == false)
	scream_error_if
	  (return (BD_ERROR), BE_SYNTAX_ERROR,
	   "An expression or value was expected on line %d after '='",
	   whichline(code, i)
	   );
      dabsic_read_separator(code, i);
    }
  dabsic_read_separator(code, i);
  if (code[i] == '}')
    return (BD_OK);

  conf.construct = SmallConf::ARRAY;
  iteration = 0;
  do
    {
      SmallConf		&newconf = conf[iteration++];

      dabsic_read_separator(code, i);
      if ((ret = dabsic_read_sequence(code, i, newconf)) == BD_ERROR)
	return (BD_ERROR);
      if (ret == BD_OK)
       	goto Bottom;

      if ((ret = dabsic_read_function(code, i, newconf)) == BD_ERROR)
	return (BD_ERROR);
      if (ret == BD_OK)
	goto Bottom;

      if ((ret = dabsic_read_xml(code, i, newconf)) == BD_ERROR)
	return (BD_ERROR);
      if (ret == BD_OK)
	goto Bottom;

      if ((ret = dabsic_read_array(code, i, newconf)) == BD_ERROR)
	return (BD_ERROR);
      if (ret == BD_OK)
	goto Bottom;

      if ((ret = dabsic_read_scope(code, i, newconf)) == BD_ERROR)
	return (BD_ERROR);
      if (ret == BD_OK)
	goto Bottom;

      if (readvalue(code, i, newconf, ",") == false)
	scream_error_if
	  (return (BD_ERROR), BE_SYNTAX_ERROR,
	   "An expression, value or scope was expected on line %d",
	   whichline(code, i)
	   );

    Bottom:
      dabsic_read_separator(code, i);
    }
  while (readtext(code, i, ","));
  dabsic_read_separator(code, i);
  return (BD_OK);
}

