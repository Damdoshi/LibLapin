// Jason Brillante "Damdoshi"
// Lisa Monpierre "Leeza"
// Pentacle Technologie 2009-2013
//
// DABSIC
// Developer's All-purpose Block Structured Instruction Code

#include	"ParsingTools.hpp"

void		bpt::ParsingTools::Where(const bpt::string	&str,
					 unsigned int		index,
					 unsigned int		&line,
					 unsigned int		&col) const
{
  unsigned int	i;
  
  for (i = 0, col = 0, line = 0; i < index; ++i)
    if (str[i] == L'\n')
      {
	line += 1;
	col = 0;
      }
    else
      col += 1;
  col += 1;
  line += 1;
}

