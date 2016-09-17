// Jason Brillante "Damdoshi"
// Lisa Monpierre "Leeza"
// Pentacle Technologie 2009-2013
//
// DABSIC
// Developer's All-purpose Block Structured Instruction Code

#include	"ParsingTools.hpp"

wchar_t		bpt::ParsingTools::CaseConvert(wchar_t	c) const
{
  if (c >= L'a' && c <= L'z')
    return (c - (L'a' - L'A'));
  return (c);
}

