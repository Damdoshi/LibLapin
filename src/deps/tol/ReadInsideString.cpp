// Jason Brillante "Damdoshi"
// Lisa Monpierre "Leeza"
// Pentacle Technologie 2009-2013
//
// DABSIC
// Developer's All-purpose Block Structured Instruction Code

#include	"ParsingTools.hpp"

bool		bpt::ParsingTools::ReadInsideString(const bpt::string	&str,
						    unsigned int	&index,
						    bpt::string	&out) const
{
  bpt::stringstream	ss;
  unsigned int		i;

  i = index;
  while (CheckChar(str, i, StringDelimiter) == false)
    {
      unsigned int	j;
      wchar_t		c;

      j = i;
      if (ReadInsideChar(str, j, c) == false)
	{
	  out = ss.str();
	  return (false);
	}
      char		ch = c;

      if (str[i] == '\\' || j == i + 1)
	ss << ch;
      else
	ss << str.substr(i, j - i);
      i = j;
    }
  index = i;
  out = ss.str();
  return (true);
}
