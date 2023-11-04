// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

Decision		xml_read_between_markup(const char		*code,
						ssize_t			&i,
						SmallConf		&conf,
						SmallConf		&root)
{
  std::string		str;
  ssize_t		line;
  ssize_t		j;

  xml_read_separator(code, i);
  line = whichline(code, i);
  while (code[i] != '\0' && strncmp(&code[i], "</", 2) != 0)
    {
      for (j = i; code[j] && code[j] != '<'; ++j);
      if (code[j] == '\0')
	scream_error_if
	  (return (BD_ERROR), BE_SYNTAX_ERROR,
	   "A closing markup was expected to close the "
	   "XML scope '%s' opened on line %zu, on line %s:%d",
	   "configuration,syntax",
	   conf.name.c_str(), line,
	   SmallConf::file_read.top().c_str(), whichline(code, i)
	   );

      // Register raw value
      if (j - i > 1)
	if ((str = _clean_raw_data(&code[i], j - i)) != "")
	  conf[conf.Size()].SetString(str);

      // Closing markup found
      if (code[j + 1] == '/')
	{
	  i = j;
	  return (BD_OK);
	}

      // Markup found
      i = j + 1;
      if (code[i] == '@') // <@insert ... />
	{
	  const char	*cod = strstr(&code[i], "/>");

	  if (!cod)
	    scream_error_if
	      (return (BD_ERROR), BE_SYNTAX_ERROR,
	       "Special markup end was expected on line %s:%d",
	       "configuration,syntax",
	       SmallConf::file_read.top().c_str(), whichline(code, i)
	       );
	  std::string	sub(code, i, cod - &code[i]);
	  ssize_t	ii = 0;
	  
	  if (_bunny_handle_directive
	      (sub.c_str(), ii, &conf, &root, xml_read_separator,
	       Expression::BEOF_CAT
	       ) != BD_OK)
	    return (BD_ERROR);
	  i += ii;
	  xml_read_separator(code, i);
	  if (readtext(code, i, "/>") == false)
	    scream_error_if
	      (return (BD_ERROR), BE_SYNTAX_ERROR,
	       "Special markup end was expected on line %s:%d",
	       "configuration,syntax",
	       SmallConf::file_read.top().c_str(), whichline(code, i)
	       );
	  xml_read_separator(code, i);
	}
      else if (xml_read_markup(code, i, conf[conf.Size()], root) == BD_ERROR)
	return (BD_ERROR);
    }
  xml_read_separator(code, i);
  return (BD_OK);
}
