// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

void			dabsic_read_separator(const char		*code,
					      ssize_t			&i)
{
  bool			once;

  once = true;
  skipspace(code, i);
  while (once == true)
    {
      once = false;
      while (code[i] == '\'')
	{
	  once = true;
	  while (code[i] != '\0' && code[i] != '\n' && code[i] != '\r')
	    ++i;
	  skipspace(code, i);
	}
      while (strncmp(&code[i], "[*", 2) == 0)
	{
	  once = true;
	  while (code[i] != '\0' && strncmp(&code[i], "*]", 2) != 0)
	    ++i;
	  if (code[i])
	    i += 2;
	  skipspace(code, i);
	}
    }
}
