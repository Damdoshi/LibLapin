// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

static void		read_separator(const char			*code,
				       ssize_t				&i)
{
  skipspace(code, i);
  while (code[i] == '#')
    {
      while (code[i] != '\0' && code[i] != '\n' && code[i] != '\r')
	++i;
      skipspace(code, i);
    }
}

static bool		read_inside_scope(t_bunny_configuration		*fileroot,
					  const char			*code,
					  ssize_t			&i,
					  SmallConf			&conf)
{
  char			buffer[512];

  read_separator(code, i);
  if (getfieldname(code, i, &buffer[0], sizeof(buffer), conf, false) == false)
    return (false);
  read_separator(code, i);
  if (readtext(code, i, "=") == false)
    return (false);
  SmallConf		&newnode = conf[&buffer[0]];
  int			iteration = 0;

  newnode.construct = SmallConf::ARRAY;
  do
    {
      read_separator(code, i);
      if (code[i] == '@')
	{
	  if (_bunny_handle_directive(code, i, &newnode[iteration++], fileroot, read_separator) == false)
	    return (false);
	}
      else if (code[i] == '$')
	{
	  if (expr_read_expression(code, ++i, newnode[iteration++], Expression::BEOF_TERNARY) == false)
	    return (false);
	}
      else
	readvalue(code, i, newnode[iteration++], ",");
      read_separator(code, i);
    }
  while (readtext(code, i, ","));
  shrink_single_element_array(newnode);
  return (true);
}

static
SmallConf		*read_new_scope(const char			*code,
					ssize_t				&i,
					SmallConf			&root)
{
  t_bunny_configuration	*cnf;

  read_separator(code, i);
  if ((cnf = _bunny_configuration_go_get_node
       ((t_bunny_configuration*)&root, code, i)) == NULL)
    scream_error_if
      (return (NULL), BE_SYNTAX_ERROR,
       "%s code, %p config -> %p "
       "(Error while getting scope name or scope address on line %d)",
       code, &root, cnf, whichline(code, i));
  read_separator(code, i);
  if (readtext(code, i, "]") == false)
    scream_error_if
      (return (NULL), BE_SYNTAX_ERROR,
       "%s code, %p config -> %p "
       "(The ']' token was expected after scope name on line %d)",
       code, &root, (void*)NULL, whichline(code, i));
  ((SmallConf*)cnf)->construct = SmallConf::MAP;
  read_separator(code, i);
  return ((SmallConf*)cnf);
}

t_bunny_configuration	*_bunny_read_ini(const char			*code,
					 t_bunny_configuration		*config)
{
  SmallConf		&conf = *(SmallConf*)config;
  SmallConf		*child;
  bool			cmode = SmallConf::create_mode;
  ssize_t		i;

  i = 0;
  SmallConf::create_mode = true;
  child = &conf; // Create the INI "default node"
  child->construct = SmallConf::MAP;
  while (code[i])
    {
      read_separator(code, i);
      if (readtext(code, i, "["))
	{
	  if ((child = read_new_scope(code, i, conf)) == NULL)
	    goto RestoreExit;
	}
      else if (code[i] == '@')
	{
	  if (_bunny_handle_directive(code, i, child, config, read_separator) == false)
	    goto RestoreExit;
	}
      else if (code[i] != '\0')
	{
	  if (read_inside_scope(config, code, i, *child) == false)
	    goto RestoreExit;
	}
      read_separator(code, i);
    }
  SmallConf::create_mode = cmode;
  scream_log_if("%s code, %p config -> %p", code, config, config);
  return (config);

 RestoreExit:
  SmallConf::create_mode = cmode;
  return (NULL);
}

