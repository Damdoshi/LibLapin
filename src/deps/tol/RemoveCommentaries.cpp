// Jason Brillante "Damdoshi"
// Lisa Monpierre "Leeza"
// Pentacle Technologie 2009-2013
//
// DABSIC
// Developer's All-purpose Block Structured Instruction Code

#include	"ParsingTools.hpp"

void		bpt::ParsingTools::RemoveCommentaries(bpt::string	&str) const
{
  unsigned int	i;

  i = 0;
  while (str[i] != '\0')
    if (str.compare(i, 2, "//") == 0)
      for (;str[i] != '\0' && str[i] != '\n'; ++i)
	str[i] = ' ';
    else if (str.compare(i, 2, "/*") == 0)
      {
	for (;str[i] != '\0' && str.compare(i, 2, "*/") != 0; ++i)
	  str[i] = ' ';
	if (str[i] != '\0')
	  {
	    str[i++] = ' ';
	    str[i++] = ' ';
	  }
      }
    else
      i += 1;
}
