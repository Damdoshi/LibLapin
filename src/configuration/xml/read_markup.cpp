// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

Decision		xml_read_markup(const char		*code,
					ssize_t			&i,
					SmallConf		&conf,
					SmallConf		&root)
{
  char			buffer[128];
  ssize_t		line;

  line = whichline(code, i);
  if (getfieldname(code, i, &buffer[0], sizeof(buffer), conf, true, true) == false)
    scream_error_if
      (return (BD_ERROR), BE_SYNTAX_ERROR,
       "A name was expected line %s:%d",
       "configuration,syntax",
       SmallConf::file_read.top().c_str(), whichline(code, i)
       );
  conf.name = &buffer[0];
  conf.given_name = true;
  xml_read_separator(code, i);

  // Markup values are not standard, but I think it is a nice to have extent
  // and allows compatibility with Dabsic on array/node/value elements.
  if (readtext(code, i, "="))
    {
      xml_read_separator(code, i);
      if (readvalue(code, i, conf, NULL) == false)
	scream_error_if
	  (return (BD_ERROR), BE_SYNTAX_ERROR,
	   "An expression or value was expected on line %s:%d",
	   "configuration,syntax",
	   SmallConf::file_read.top().c_str(), whichline(code, i)
	   );
      xml_read_separator(code, i);
    }

  while (code[i] != '/' && code[i] != '>')
    {
      SmallConf		*newconf;

      if (getfieldname(code, i, &buffer[0], sizeof(buffer), conf, true, true) == false)
	scream_error_if
	  (return (BD_ERROR), BE_SYNTAX_ERROR,
	   "A markup property was expected line %s:%d",
	   "configuration,syntax",
	   SmallConf::file_read.top().c_str(), whichline(code, i)
	   );
      newconf = &conf[&buffer[0]];
      xml_read_separator(code, i);
      if (readtext(code, i, "="))
	{
	  // Array properties are not standard, but I think it is a nice to have extent
	  // that improves compatibility with Dabsic, even if elements in arrays in properties
	  // are only litterals.
	  do
	    {
	      xml_read_separator(code, i);
	      if (readvalue(code, i, (*newconf)[newconf->Size()], NULL) == false)
		scream_error_if
		  (return (BD_ERROR), BE_SYNTAX_ERROR,
		   "An expression or value was expected on line %s:%d",
		   "configuration,syntax",
		   SmallConf::file_read.top().c_str(), whichline(code, i)
		   );
	      xml_read_separator(code, i);
	    }
	  while (readtext(code, i, ","));
	  shrink_single_element_array(*newconf);
	  xml_read_separator(code, i);
	}
    }
  if (readtext(code, i, ">"))
    {
      if (xml_read_between_markup(code, i, conf, root) == BD_ERROR)
	return (BD_ERROR);
      xml_read_separator(code, i);
      if (readtext(code, i, "</") == false)
	scream_error_if
	  (return (BD_ERROR), BE_SYNTAX_ERROR,
	   "A closing markup was expected to close the "
	   "XML scope '%s' opened on line %zu, on line %s:%d",
	   "configuration,syntax",
	   conf.name.c_str(), line,
	   SmallConf::file_read.top().c_str(), whichline(code, i)
	   );
      xml_read_separator(code, i);
      if (readtext(code, i, conf.name.c_str()) == false)
	scream_error_if
	  (return (BD_ERROR), BE_SYNTAX_ERROR,
	   "A closing markup was expected to close the "
	   "XML scope '%s' opened on line %zu, on line %s:%d",
	   "configuration,syntax",
	   conf.name.c_str(), line,
	   SmallConf::file_read.top().c_str(), whichline(code, i)
	   );
      xml_read_separator(code, i);
      if (readtext(code, i, ">") == false)
	scream_error_if
	  (return (BD_ERROR), BE_SYNTAX_ERROR,
	   "A closing markup was expected to close the "
	   "XML scope '%s' opened on line %zu, on line %s:%d",
	   "configuration,syntax",
	   conf.name.c_str(), line,
	   SmallConf::file_read.top().c_str(), whichline(code, i)
	   );
      xml_read_separator(code, i);
      return (BD_OK);
    }
  if (readtext(code, i, "/>") == false)
    scream_error_if
      (return (BD_ERROR), BE_SYNTAX_ERROR,
       "Markup end or additionnal property was expected on line %s:%d",
       "configuration,syntax",
       SmallConf::file_read.top().c_str(), whichline(code, i)
       );
  xml_read_separator(code, i);
  return (BD_OK);
}
