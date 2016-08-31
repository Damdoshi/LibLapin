// Jason Brillante "Damdoshi"
// Lisa Monpierre "Leeza"
// Pentacle Technologie 2009-2013
//
// DABSIC
// Developer's All-purpose Block Structured Instruction Code

#include	<string.h>
#include	"ParsingTools.hpp"
#include	"lapin.h"

bpt::string	bpt::ParsingTools::BuildString(const bpt::string	&str) const
{
  bpt::stringstream	ss;
  unsigned int		i;
  unsigned int		len;
  char			tab[sizeof(wchar_t) + 1];

  for (i = 0, len = 0; i < str.size(); i += len)
    if (str[i] != '\0')
      {
	if (str[i] & 0x80)
	  {
	    if ((len = bunny_strnlen(&str.c_str()[i], sizeof(wchar_t))) > sizeof(wchar_t))
	      len = sizeof(wchar_t);
	    memcpy(&tab, &str.c_str()[i], len);
	    if ((str[i] & 0xE0) == 0xC0) // 110x xxxx
	      len = 2;
	    else if ((str[i] & 0xF0) == 0xE0) // 1110 xxxx
	      len = 3;
	    else if ((str[i] & 0xF8) == 0xF0) // 1111 0xxx
	      len = 4;
	    else
	      return ("");
	    tab[len] = '\0';
	    ss << tab;
	  }
	else
	  {
	    ss << BuildCharacter(str[i], true);
	    len = 1;
	  }
      }
  return (ss.str());
}

