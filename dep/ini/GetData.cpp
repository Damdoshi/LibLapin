// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014
//
// INI io system

#include					"Ini.hpp"

std::map<bpt::string, bpt::Ini::Scope>		&bpt::Ini::GetData(void)
{
  return (datas);
}

const std::map<bpt::string, bpt::Ini::Scope>	&bpt::Ini::GetData(void) const
{
  return (datas);
}

