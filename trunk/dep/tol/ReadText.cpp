// Jason Brillante "Damdoshi"
// Lisa Monpierre "Leeza"
// Pentacle Technologie 2009-2013
//
// DABSIC
// Developer's All-purpose Block Structured Instruction Code

#ifdef		__BPT_DEBUG__
# include	<iostream>
#endif
#include	"ParsingTools.hpp"

bool		bpt::ParsingTools::ReadText(const bpt::string	&str,
					    unsigned int	&index,
					    const bpt::string	&token) const
{
  if (CheckText(str, index, token))
    {
#ifdef		__BPT_DEBUG__
      std::wcout << str.substr(index, token.length());
#endif
      index += token.length();
      return (true);
    }
  return (false);
}

bool		bpt::ParsingTools::ReadText(const bpt::string	&str,
					    unsigned int	&index,
					    const bpt::string	*token,
					    unsigned int	len) const
{
  unsigned int	i;

  for (i = 0; i < len; ++i)
    if (ReadText(str, index, token[i]))
      return (true);
  return (false);
}

