// Jason Brillante "Damdoshi"
// Lisa Monpierre "Leeza"
// Pentacle Technologie 2009-2013
//
// DABSIC
// Developer's All-purpose Block Structured Instruction Code

#include	"ParsingTools.hpp"

void		bpt::ParsingTools::FindNextCommand(const bpt::string	&str,
						   unsigned int		&index) const
{
  FindEndOfCommand(str, index);
  ReadChar(str, index, ";\n \t");
}
