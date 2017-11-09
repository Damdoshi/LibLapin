// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

std::string		_clean_raw_data(const char		*code,
					size_t			len)
{
  while (*code == '\n' || *code == '\r' || *code == ' ' || *code == '\t')
    {
      code += 1;
      len -= 1;
    }
  while (len > 0 &&
	 (code[len - 1] == '\n' || code[len - 1] == '\r'
	  || code[len - 1] == ' ' || code[len - 1] == '\t'))
    len -= 1;
  return (std::string(code, len));
}

