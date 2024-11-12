// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Bibliothèque Lapin

/*
#include		"private/network.hpp"

template <>
network::Descriptor	&network::Descriptor::operator<<<std::string>(std::string const &data)
{
  if (SetMessage(data.c_str(), data.size()) == false)
    throw IOException(__PRETTY_FUNCTION__);
  return (*this);
}
template <>
network::Descriptor	&network::Descriptor::operator<<<const char *>(const char * const &data)
{
  if (SetMessage(data, strlen(data)) == false)
    throw IOException(__PRETTY_FUNCTION__);
  return (*this);
}
*/
