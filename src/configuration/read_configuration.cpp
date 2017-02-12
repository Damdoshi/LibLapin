// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

t_bunny_my_read_configuration gl_bunny_my_read_configuration = NULL;

t_bunny_configuration	*bunny_read_configuration(t_bunny_configuration_type		type,
						  const char				*code,
						  t_bunny_configuration			*config)
{
  t_bunny_configuration	*nw;
  bool			local;

  if ((local = (config == NULL)))
    if ((config = bunny_new_configuration()) == NULL)
      return (NULL);

  if (type == BC_INI)
    {
      if ((nw = _bunny_read_ini(code, config)) == NULL && local)
	bunny_delete_configuration(config);
      return (nw);
    }

  if (type == BC_DABSIC)
    {
      if ((nw = _bunny_read_dabsic(code, config)) == NULL && local)
	bunny_delete_configuration(config);
      return (nw);
    }
  
  if (type == BC_XML)
    {
      if ((nw = _bunny_read_xml(code, config)) == NULL && local)
	bunny_delete_configuration(config);
      return (nw);
    }

  if (type == BC_LUA)
    {
      if ((nw = _bunny_read_lua(code, config)) == NULL && local)
	bunny_delete_configuration(config);
      return (nw);
    }

  if (gl_bunny_my_read_configuration)
    {
      if ((nw = gl_bunny_my_read_configuration(type, code, config)) == NULL && local)
	bunny_delete_configuration(config);
      return (nw);
    }

  return (NULL);
}

