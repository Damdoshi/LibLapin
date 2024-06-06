// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

static void		read_separator(const char			*code,
				       ssize_t				&i)
{
  bool			once;

  once = true;
  skipspace(code, i);
  while (once == true)
    {
      once = false;
      while (strncmp(&code[i], "#/", 2) == 0)
	{
	  once = true;
	  while (code[i] != '\0' && strncmp(&code[i], "/#", 2) != 0)
	    ++i;
	  if (code[i])
	    i += 2;
	  skipspace(code, i);
	}

      while (code[i] == '#')
	{
	  while (code[i] != '\0' && code[i] != '\n' && code[i] != '\r')
	    ++i;
	  skipspace(code, i);
	}
    }
}

static bool		read_inside_scope(t_bunny_configuration		*fileroot,
					  const char			*code,
					  ssize_t			&i,
					  SmallConf			&conf)
{
  t_bunny_configuration	*cnf = (t_bunny_configuration*)&conf;

  read_separator(code, i);
  if ((cnf = bunny_configuration_resolve_address
       (&cnf, 1, code, i)) == NULL)
    scream_error_if
      (return (false), BE_SYNTAX_ERROR,
       "%p fileroot, '%.5s...' code, %d i, %p config -> %s "
       "(Error while getting field name on line %s:%d)",
       "configuration,syntax",
       fileroot, code, (int)i, &conf, "false",
       SmallConf::file_read.top().c_str(), whichline(code, i));
  read_separator(code, i);
  if (readtext(code, i, "=") == false)
    return (false);
  SmallConf		&newnode = *(SmallConf*)cnf;
  int			iteration;

  // Exploitation de la taille afin de s'adapter aux éventuels @push
  newnode.construct = SmallConf::ARRAY;
  do
    {
      iteration = newnode.array.size();
      read_separator(code, i);
      if (code[i] == '@')
	{
	  if (_bunny_handle_directive
	      (code, i, &newnode[iteration], fileroot, read_separator,
	       Expression::BEOF_TERNARY
	       ) != BD_OK)
	    return (false);
	}
      else if (code[i] == '$')
	{
	  if (expr_read_expression(code, ++i, newnode[iteration], Expression::BEOF_TERNARY) == false)
	    return (false);
	}
      else
	readvalue(code, i, newnode[iteration], ",");
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
  t_bunny_configuration	*cnf = (t_bunny_configuration*)&root;

  read_separator(code, i);
  if ((cnf = bunny_configuration_resolve_address
       (&cnf, 1, code, i)) == NULL)
    scream_error_if
      (return (NULL), BE_SYNTAX_ERROR,
       "'%.5s...' code, %p config -> %p "
       "(Error while getting scope name or scope address on line %s:%d)",
       "configuration,syntax",
       code, &root, cnf,
       SmallConf::file_read.top().c_str(), whichline(code, i));
  read_separator(code, i);
  if (readtext(code, i, "]") == false)
    scream_error_if
      (return (NULL), BE_SYNTAX_ERROR,
       "'%.5s...' code, %p config -> %p "
       "(The ']' token was expected after scope name on line %s:%d)",
       "configuration,syntax",
       code, &root, (void*)NULL,
       SmallConf::file_read.top().c_str(), whichline(code, i));
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
	  if (_bunny_handle_directive
	      (code, i, child, config, read_separator,
	       Expression::BEOF_TERNARY
	       ) != BD_OK)
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
  scream_log_if
    ("'%.5s...' code, %p config -> %p", "ressource,configuration", code, config, config);
  return (config);

 RestoreExit:
  SmallConf::create_mode = cmode;
  return (NULL);
}

