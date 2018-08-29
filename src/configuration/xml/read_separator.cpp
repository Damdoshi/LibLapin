// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

void			xml_read_separator(const char		*code,
					   ssize_t		&i)
{
  bool			once;

  once = true;
  skipspace(code, i);
  while (once == true)
    {
      once = false;
      while (strncmp(&code[i], "<!--", 4) == 0)
	{
	  once = true;
	  while (code[i] != '\0' && strncmp(&code[i], "-->", 3) != 0)
	    ++i;
	  if (code[i])
	    i += 3;
	  skipspace(code, i);
	}
    }
}
