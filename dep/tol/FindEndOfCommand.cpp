// Jason Brillante "Damdoshi"
// Lisa Monpierre "Leeza"
// Pentacle Technologie 2009-2013
//
// DABSIC
// Developer's All-purpose Block Structured Instruction Code

#include	"ParsingTools.hpp"

void		bpt::ParsingTools::FindEndOfCommand(const bpt::string	&str,
						    unsigned int	&index) const
{
  unsigned int	j;
  bpt::string	_useless;
  
  j = index;
  while (j < str.size())
    if (str[j] == L'"')
      ReadString(str, j, _useless);
    else if (str[j] == L';')
      {
	index = ++j;
	return ;
      }
    else if (j > 0 && str[j] == L'\n' && str[j - 1] != L'\\')
      {
	index = ++j;
	return ;
      }
    else
      j += 1;
}
