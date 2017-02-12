// Jason Brillante "Damdoshi"
// Lisa Monpierre "Leeza"
// Pentacle Technologie 2009-2013
//
// DABSIC
// Developer's All-purpose Block Structured Instruction Code

#ifdef		__BPT_DEBUG__
# include	<iostream>
#endif
#include	"ParsingTools.hpp"

bool		bpt::ParsingTools::ReadCharCase(const bpt::string	&str,
						unsigned int		&index,
						const bpt::string	&token) const
{
  unsigned int	i;
  unsigned int	j;
  wchar_t	c;
  bool		fnd;

  i = index;
  do
    {
      c = CaseConvert(str[i]);
      fnd = false;
      for (j = 0; j < token.size() && c != CaseConvert(token[j]); ++j);
      if (j < token.size())
	{
	  fnd = true;
	  ++i;
	}
    }
  while (fnd);
  if (i != index)
    {
#ifdef		__BPT_DEBUG__
      std::wcout << str.substr(index, i - index);
#endif
      index = i;
      return (true);
    }
  return (false);
}
