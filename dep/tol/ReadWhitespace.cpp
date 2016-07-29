// Jason Brillante "Damdoshi"
// Lisa Monpierre "Leeza"
// Pentacle Technologie 2009-2013
//
// DABSIC
// Developer's All-purpose Block Structured Instruction Code

#include	"ParsingTools.hpp"

bool		bpt::ParsingTools::ReadWhitespace(const bpt::string	&str,
						  unsigned int		&index) const
{
  unsigned int	_index;

  _index = index;
  while (ReadChar(str, index, " \t") ||
	 ReadText(str, index, "\\\r\n") ||
	 ReadText(str, index, "\\\n") ||
	 ReadText(str, index, "\\\r"));
  return (_index != index);
}
