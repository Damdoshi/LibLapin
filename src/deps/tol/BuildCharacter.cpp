// Jason Brillante "Damdoshi"
// Lisa Monpierre "Leeza"
// Pentacle Technologie 2009-2013
//
// DABSIC
// Developer's All-purpose Block Structured Instruction Code

#include	<string.h>
#include	"ParsingTools.hpp"

bpt::string	bpt::ParsingTools::BuildCharacter(wchar_t	c,
						  bool		in_string,
						  int		*out) const
{
  if (out)
    *out = 1;
  switch (c)
    {
    case '\a':
      return ("\\a");
    case '\b':
      return ("\\b");
    case '\v':
      return ("\\v");
    case '\f':
      return ("\\f");
    case '\n':
      return ("\\n");
    case '\t':
      return ("\\t");
    case '\r':
      return ("\\r");
    case '\0':
      return ("\\0");
    case '\'':
      if (in_string)
	return ("'");
      return ("\\'");
    case '"':
      if (in_string == false)
	return ("\"");
      return ("\\\"");
    default:
      bpt::stringstream ss;
      char		tab[sizeof(wchar_t) + 1];
      wchar_t		x;

      x = Endian(c);
      memcpy(&tab[0], &x, sizeof(x));
      tab[sizeof(x)] = '\0';
      if (tab[0] & 0x80)
	{
	  ss << &tab[0];
	  if (out)
	    *out = strlen(&tab[0]);
	}
      else
	{
	  char		_c = c;

	  if (c < ' ' || (c >= 127 && c <= 255))
	    ss << "\\0" << std::oct << c;
	  else
	    ss << _c;
	}
      return (ss.str());
    }
  return ("");
}

