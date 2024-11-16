// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2025
// EFRITS SAS 2022-2025
// Pentacle Technologie 2008-2025
//
// Bibliothèque Lapin

#include			"lapin_private.h"

network::Descriptor::operator	bool (void) const
{
  return (active && !doomed);
}

network::Descriptor::operator	int (void) const
{
  return (fd);
}

network::Descriptor::operator	const Info & (void) const
{
  return (info);
}

network::Descriptor::operator	const Info * (void) const
{
  return (&info);
}

network::Descriptor::operator	const char * (void) const
{
  return (info.identity);
}

network::Descriptor::operator	std::string (void) const
{
  char				buffer[NBRCELL(info.identity) + 1];

  strcpy(buffer, info.identity);
  return (std::string(buffer));
}
