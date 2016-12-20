// Jason Brillante "Damdoshi"
// Lisa Monpierre "Leeza"
// Pentacle Technologie 2009-2013
//
// DABSIC
// Developer's All-purpose Block Structured Instruction Code

#include	"ParsingTools.hpp"

int		bpt::ParsingTools::ReadString(const bpt::string		&str,
					      unsigned int		&index,
					      bpt::string		&out) const
{
  unsigned int	i = index;

  if (ReadText(str, i, StringDelimiter) == false)
    return (-1);
  if (ReadInsideString(str, i, out) == false)
    {
      ReadText(str, i, StringDelimiter);
      return (-2);
    }
  if (ReadText(str, i, StringDelimiter) == false)
    return (-3);
  index = i;
  return (0);
}

