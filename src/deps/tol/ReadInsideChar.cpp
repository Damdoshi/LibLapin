// Jason Brillante "Damdoshi"
// Lisa Monpierre "Leeza"
// Pentacle Technologie 2009-2013
//
// DABSIC
// Developer's All-purpose Block Structured Instruction Code

#include	<stdlib.h>
#include	<string.h>
#include	"ParsingTools.hpp"
#include    "lapin.h"

bool		bpt::ParsingTools::ReadInsideChar(const bpt::string	&str,
						  unsigned int		&index,
						  wchar_t		&out) const
{
  if (str[index] & 0x80) // Unicode character
    {
      unsigned int len;

      if ((len = bunny_strnlen(&str.c_str()[index], sizeof(out))) > sizeof(out))
	len = sizeof(out);
      memcpy(&out, &str.c_str()[index], len);
      if ((str[index] & 0xE0) == 0xC0) // 110x xxxx
	{
	  out &= 0xFFFF;
	  index += 2;
	}
      else if ((str[index] & 0xF0) == 0xE0) // 1110 xxxx
	{
	  out &= 0xFF;
	  index += 3;
	}
      else if ((str[index] & 0xF8) == 0xF0) // 1111 0xxx
	index += 4;
      else
	return (false);
      out = Endian(out);
      return (true);
    }
  else if (str[index] != '\\')
    {
      out = str[index++];
      return (true);
    }
  index += 1;
  switch (str[index++])
    {
    case 'a':
      out = '\a';
      return (true);
    case 'b':
      out = '\b';
      return (true);
    case 'v':
      out = '\v';
      return (true);
    case 'f':
      out = '\f';
      return (true);
    case 'n':
      out = '\n';
      return (true);
    case 't':
      out = '\t';
      return (true);
    case '\\':
      out = '\\';
      return (true);
    case 'r':
      out = '\r';
      return (true);
    case '"':
      out = '"';
      return (true);
    case '\'':
      out = '\'';
      return (true);
    case '0':
      {
	unsigned int	i = index;

	ReadChar(str, index, Octal);
	bpt::string	sub = str.substr(i, index - i);
	std::string	num(sub.begin(), sub.end());

	out = strtoll(num.c_str(), NULL, 8);
	return (true);
      }
    default:
      return (false);
    }
  return (false);
}

