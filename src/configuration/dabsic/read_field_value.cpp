// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

Decision		dabsic_read_field_value(const char		*code,
						ssize_t			&i,
						SmallConf		&conf,
						SmallConf		&root)
{
  Decision		ret;

  dabsic_read_separator(code, i);
  if (readtext(code, i, "=") == false)
    return (BD_NOT_FOUND);
  dabsic_read_separator(code, i);

  if ((ret = dabsic_read_sequence(code, i, conf, root)) == BD_OK)
    return (ret);
  if (ret == BD_ERROR)
    return (ret);

  if ((ret = dabsic_read_function(code, i, conf, root)) == BD_OK)
    return (ret);
  if (ret == BD_ERROR)
    return (ret);

  if ((ret = dabsic_read_csv(code, i, conf, root)) == BD_OK)
    return (ret);
  if (ret == BD_ERROR)
    return (ret);

  if ((ret = dabsic_read_xml(code, i, conf, root)) == BD_OK)
    return (ret);
  if (ret == BD_ERROR)
    return (ret);

  if ((ret = dabsic_read_array(code, i, conf, root)) == BD_OK)
    return (ret);
  if (ret == BD_ERROR)
    return (ret);

  if ((ret = dabsic_read_scope(code, i, conf, root)) == BD_OK)
    return (ret);
  if (ret == BD_ERROR)
    return (ret);

  if (code[i] == '@')
    {
      if (_bunny_handle_directive
	  (code, i, &conf, &root, dabsic_read_separator) == false)
	return (BD_ERROR);
      dabsic_read_separator(code, i);
    }

  if ((ret = dabsic_read_litterals(code, i, conf, root)) == BD_OK)
    return (ret);
  if (ret == BD_ERROR)
    return (ret);

  scream_error_if
    (return (BD_ERROR), BE_SYNTAX_ERROR,
     "A scope, value or directive was expected after '=' on line %d",
     whichline(code, i)
     );
  return (BD_ERROR);
}

