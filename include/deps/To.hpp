// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2013
//
// BPT NetCom

#ifndef			__TO_HPP__
# define		__TO_HPP__
#include		<string>
#include		<sstream>

template <typename T>
T			to(const std::string	&str)
{
  std::istringstream    iss(str);
  T                     i;

  iss >> i;
  return (i);
}

#endif	//		__TO_HPP__
