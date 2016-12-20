// Jason Brillante "Damdoshi"
// Lisa Monpierre "Leeza"
// Pentacle Technologie 2009-2013
//
// DABSIC
// Developer's All-purpose Block Structured Instruction Code

#include	"ParsingTools.hpp"

bool		bpt::ParsingTools::CheckChar(const bpt::string	&str,
					     unsigned int	index,
					     const bpt::string	&token) const
{
  unsigned int	i;

  for (i = 0; i < token.size(); ++i)
    if (str[index] == token[i])
      return (true);
  return (false);
}

