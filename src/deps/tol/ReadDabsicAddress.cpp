// Jason Brillante "Damdoshi"
// Lisa Monpierre "Leeza"
// Pentacle Technologie 2009-2013
//
// DABSIC
// Developer's All-purpose Block Structured Instruction Str

#include	"ParsingTools.hpp"

int		bpt::ParsingTools::ReadDabsicAddress(const bpt::string	&str,
						     unsigned int	&index,
						     bpt::string	&out) const
{
  unsigned int	i = index;

  if (!CheckCharCase(str, i, FieldNameFirstChar) &&
      !CheckTextCase(str, i, DabsicRoot) &&
      !CheckTextCase(str, i, CurrentNode))
    return (-1);
  do
    if (!ReadCharCase(str, i, FieldNameFirstChar))	// '_' or first letter of a field
      {
	if (ReadTextCase(str, i, DabsicRoot))		// So maybe [] ?
	  {
	    if (i != index + 2)				// Doing blob.[].foo is bad
	      return (-3);
	  }
	else if (!ReadTextCase(str, i, CurrentNode))	// {} for current node
	  return (-2);
      }
    else
      ReadCharCase(str, i, FieldName);
  while (ReadTextCase(str, i, DirectAccess) || ReadTextCase(str, i, AddressAccess));
  out = str.substr(index, i - index);
  index = i;
  return (0);
}

