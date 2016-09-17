// Jason Brillante "Damdoshi"
// Lisa Monpierre "Leeza"
// Pentacle Technologie 2009-2013
//
// DABSIC
// Developer's All-purpose Block Structured Instruction Code

#include	"ParsingTools.hpp"

bool		bpt::ParsingTools::CheckText(const bpt::string	&str,
					     unsigned int	index,
					     const bpt::string	&token) const
{
  return ((str.compare(index, token.length(), token) == 0));
}

