// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

// TODO:
// Create a function pointer table and remove all this mess...

t_bunny_my_read_configuration gl_bunny_my_read_configuration = NULL;

#define			PATTERN		"%d type, %s code, %p config -> %p"

t_bunny_configuration	*bunny_read_configuration(t_bunny_configuration_type		type,
						  const char				*code,
						  t_bunny_configuration			*config)
{
  t_bunny_configuration	*nw = NULL;
  bool			local;

  if ((local = (config == NULL)))
    if ((config = bunny_new_configuration()) == NULL)
      scream_error_if(return (NULL), bunny_errno, PATTERN, type, code, config, nw);

  if (type == BC_INI)
    {
      if ((nw = _bunny_read_ini(code, config)) == NULL && local)
	bunny_delete_configuration(config);
      if (!nw)
	scream_error_if(return (NULL), bunny_errno, PATTERN, type, code, config, nw);
      scream_log_if(PATTERN, type, code, config, nw);
      return (nw);
    }

  if (type == BC_DABSIC)
    {
      if ((nw = _bunny_read_dabsic(code, config)) == NULL && local)
	bunny_delete_configuration(config);
      if (!nw)
	scream_error_if(return (NULL), bunny_errno, PATTERN, type, code, config, nw);
      scream_log_if(PATTERN, type, code, config, nw);
      return (nw);
    }
  
  if (type == BC_XML)
    {
      if ((nw = _bunny_read_xml(code, config)) == NULL && local)
	bunny_delete_configuration(config);
      if (!nw)
	scream_error_if(return (NULL), bunny_errno, PATTERN, type, code, config, nw);
      scream_log_if(PATTERN, type, code, config, nw);
      return (nw);
    }

  if (type == BC_LUA)
    {
      if ((nw = _bunny_read_lua(code, config)) == NULL && local)
	bunny_delete_configuration(config);
      if (!nw)
	scream_error_if(return (NULL), bunny_errno, PATTERN, type, code, config, nw);
      scream_log_if(PATTERN, type, code, config, nw);
      return (nw);
    }

  if (type == BC_CSV)
    {
      if ((nw = _bunny_read_csv(code, config)) == NULL && local)
	bunny_delete_configuration(config);
      if (!nw)
	scream_error_if(return (NULL), bunny_errno, PATTERN, type, code, config, nw);
      scream_log_if(PATTERN, type, code, config, nw);
      return (nw);
    }

  if (gl_bunny_my_read_configuration)
    {
      if ((nw = gl_bunny_my_read_configuration(type, code, config)) == NULL && local)
	bunny_delete_configuration(config);
      if (!nw)
	scream_error_if(return (NULL), bunny_errno, PATTERN, type, code, config, nw);
      scream_log_if(PATTERN, type, code, config, nw);
      return (nw);
    }

  scream_error_if(return (NULL), EINVAL, PATTERN, type, code, config, nw);
  return (NULL);
}

