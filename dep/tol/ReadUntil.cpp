// Jason Brillante "Damdoshi"
// Lisa Monpierre "Leeza"
// Pentacle Technologie 2009-2013
//
// DABSIC
// Developer's All-purpose Block Structured Instruction Code

#include	"ParsingTools.hpp"

bool		bpt::ParsingTools::ReadUntil(const bpt::string	&str,
					     unsigned int	&index,
					     const bpt::string	&token) const
{
  unsigned int	i;

  for (i = index; i < str.length(); ++i)
    if (ReadChar(str, i, token))
      {
	index = i;
	return (true);
      }
  return (false);
}

