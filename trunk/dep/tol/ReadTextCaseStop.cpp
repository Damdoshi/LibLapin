// Jason Brillante "Damdoshi"
// Lisa Monpierre "Leeza"
// Pentacle Technologie 2009-2013
//
// DABSIC
// Developer's All-purpose Block Structured Instruction Code

#include	"ParsingTools.hpp"

bool		bpt::ParsingTools::ReadTextCaseStop(const bpt::string	&str,
						    unsigned int	&index,
						    const bpt::string	&token,
						    const bpt::string	&stop) const
{
  unsigned int	i;

  i = index;
  if (ReadTextCase(str, i, token) == false)
    return (false);
  if (CheckCharCase(str, i, stop))
    return (false);
  index = i;
  return (true);
}

bool		bpt::ParsingTools::ReadTextCaseStop(const bpt::string	&str,
						    unsigned int	&index,
						    const bpt::string	*token,
						    unsigned int	len,
						    const bpt::string	&stop) const
{
  unsigned int	i;

  i = index;
  if (ReadTextCase(str, i, token, len) == false)
    return (false);
  if (CheckCharCase(str, i, stop))
    return (false);
  index = i;
  return (true);
}

