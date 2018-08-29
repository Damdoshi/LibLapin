// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

void			bunny_configuration_push_path(const char	*file)
{
  SmallConf::file_path.push_back(file);
}
