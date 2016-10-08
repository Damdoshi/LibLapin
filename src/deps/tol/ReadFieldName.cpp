// Jason Brillante "Damdoshi"
// Lisa Monpierre "Leeza"
// Pentacle Technologie 2009-2013
//
// DABSIC
// Developer's All-purpose Block Structured Instruction Str

#include	"ParsingTools.hpp"

int		bpt::ParsingTools::ReadFieldName(const bpt::string	&str,
						 unsigned int		&index,
						 bpt::string		&out) const
{
  unsigned int		j;

  j = index;
  if (ReadCharCase(str, j, FieldNameFirstChar) == false)
    return (-1);
  ReadCharCase(str, j, FieldName);
  if ((out = str.substr(index, j - index)) == "_")
    return (-2);
  index = j;
  return (0);
}

