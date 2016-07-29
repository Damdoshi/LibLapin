// Jason Brillante "Damdoshi"
// Lisa Monpierre "Leeza"
// Pentacle Technologie 2009-2013
//
// DABSIC
// Developer's All-purpose Block Structured Instruction Code

#include	"ParsingTools.hpp"

bool		bpt::ParsingTools::ReadUntilIgnoreStringCase(const bpt::string	&str,
							     unsigned int	&index,
							     const bpt::string	&token) const
{
  unsigned int	i;
  bpt::string	_useless;
  
  for (i = index; i < str.size(); ++i)
    if (ReadCharCase(str, i, token) == true)
      {
	index = i;
	return (true);
      }
    else if (str[i] == L'"')
      ReadString(str, i, _useless);
  return (false);
}
