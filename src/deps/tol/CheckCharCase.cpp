// Jason Brillante "Damdoshi"
// Lisa Monpierre "Leeza"
// Pentacle Technologie 2009-2013
//
// DABSIC
// Developer's All-purpose Block Structured Instruction Code

#include	"ParsingTools.hpp"

bool		bpt::ParsingTools::CheckCharCase(const bpt::string	&str,
						 unsigned int		index,
						 const bpt::string	&token) const
{
  unsigned int	i;

  for (i = 0; i < token.length(); ++i)
    {
      wchar_t	a;
      wchar_t	b;

      a = CaseConvert(str[index]);
      b = CaseConvert(token[i]);
      if (a == b)
	return (true);
    }
  return (false);
}

