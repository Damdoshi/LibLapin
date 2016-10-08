// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2014
//
// INI io system

#include		"Ini.hpp"

bpt::Ini::Ini(void)
  : npos(errmsg)
{
  /// Create the default scope
  datas[""].size();
}

bpt::Ini::~Ini(void)
{}
