// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

t_bunny_my_write_configuration gl_bunny_my_write_configuration = NULL;

char			*bunny_write_configuration(t_bunny_configuration_type		type,
						   const t_bunny_configuration		*config)
{
  if (type == BC_INI)
    return (_bunny_write_ini(config));
  if (type == BC_DABSIC)
    return (_bunny_write_dabsic(config));
  if (type == BC_XML)
    return (_bunny_write_xml(config));
  if (type == BC_LUA)
    return (_bunny_write_lua(config));

  if (gl_bunny_my_write_configuration)
    return (gl_bunny_my_write_configuration(type, config));
  return (NULL);
}

