// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

void			bunny_configuration_create_mode(bool			cmode)
{
  SmallConf::create_mode = cmode;
  scream_log_if("%s", "configuration", cmode ? "true" : "false");
}

bool			bunny_configuration_get_create_mode(void)
{
  return (SmallConf::create_mode);
}

