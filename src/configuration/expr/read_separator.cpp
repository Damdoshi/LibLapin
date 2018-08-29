// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

void			skipspace_inline_back(const char	*str,
					      ssize_t		&i)
{
  while (str[i] && (str[i] == ' ' || str[i] == '\t'))
    ++i;
  if (str[i] == '\\')
    skipspace_inline_back(str, ++i);
}

void			expr_read_separator(const char		*code,
					    ssize_t		&i)
{
  bool			once;

  once = true;
  skipspace_inline_back(code, i);
  while (once == true)
    {
      once = false;
      while (code[i] == '\'')
	{
	  once = true;
	  while (code[i] != '\0' && code[i] != '\n' && code[i] != '\r')
	    ++i;
	  skipspace_inline_back(code, i);
	}
      while (strncmp(&code[i], "[*", 2) == 0)
	{
	  once = true;
	  while (code[i] != '\0' && strncmp(&code[i], "*]", 2) != 0)
	    ++i;
	  if (code[i])
	    i += 2;
	  skipspace_inline_back(code, i);
	}
    }
}
