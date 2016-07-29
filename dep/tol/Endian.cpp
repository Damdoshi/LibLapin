// Jason Brillante "Damdoshi"
// Lisa Monpierre "Leeza"
// Pentacle Technologie 2009-2013
//
// DABSIC
// Developer's All-purpose Block Structured Instruction Code

#include		"ParsingTools.hpp"

wchar_t			bpt::ParsingTools::Endian(wchar_t		in) const
{
  wchar_t		out;
  char			*din = (char*)&in;
  char			*dout = (char*)&out;
  unsigned int		i;

  for (i = 0; i < sizeof(out); ++i)
    dout[sizeof(out) - i - 1] = din[i];
  return (out);
}

