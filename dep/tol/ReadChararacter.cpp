// Jason Brillante "Damdoshi"
// Lisa Monpierre "Leeza"
// Pentacle Technologie 2009-2013
//
// DABSIC
// Developer's All-purpose Block Structured Instruction Code

#include	"ParsingTools.hpp"

int		bpt::ParsingTools::ReadCharacter(const bpt::string	&str,
						 unsigned int		&index,
						 wchar_t		&out) const
{
  unsigned int	i = index;

  if (ReadText(str, i, CharacterDelimiter) == false)
    return (-1);
  if (ReadInsideChar(str, i, out) == false)
    {
      ReadChar(str, i, CharacterDelimiter);
      return (-2);
    }
  if (ReadText(str, i, CharacterDelimiter) == false)
    return (-3);
  index = i;
  return (0);
}

