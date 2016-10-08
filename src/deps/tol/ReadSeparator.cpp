// Jason Brillante "Damdoshi"
// Lisa Monpierre "Leeza"
// Pentacle Technologie 2009-2013
//
// DABSIC
// Developer's All-purpose Block Structured Instruction Code

#include	"ParsingTools.hpp"

bool		bpt::ParsingTools::ReadSeparator(const bpt::string	&str,
						 unsigned int		&index) const
{
  return (ReadChar(str, index, " \t\n\r;"));
}

