// Jason Brillante "Damdoshi"
// Lisa Monpierre "Leeza"
// Pentacle Technologie 2009-2013
//
// DABSIC
// Developer's All-purpose Block Structured Instruction Code

#include	"ParsingTools.hpp"

bool		bpt::ParsingTools::CheckTextCase(const bpt::string	&str,
						 unsigned int		index,
						 const bpt::string	&token) const
{
  unsigned int	i;

  for (i = 0; i < token.length(); ++i)
    {
      if (index + i > str.length())
	return (false);
      wchar_t	a;
      wchar_t	b;

      a = CaseConvert(str[index + i]);
      b = CaseConvert(token[i]);
      if (a != b)
	return (false);
    }
  return (true);
}

bool		bpt::ParsingTools::CheckTextCase(const bpt::string	&str,
						 unsigned int		index,
						 const bpt::string	*token,
						 unsigned int		len) const
{
  unsigned int	i;

  for (i = 0; i < len; ++i)
    if (CheckTextCase(str, index, token[i]))
      return (true);
  return (false);
}



