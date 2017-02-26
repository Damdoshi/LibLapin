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

static bool		read_inside_scope(const char			*code,
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

  do
    {
      read_separator(code, i);
      readvalue(code, i, newnode[iteration++], ',');
      read_separator(code, i);
    }
  while (readtext(code, i, ","));
  return (true);
}

static
SmallConf		*read_new_scope(const char			*code,
					ssize_t				&i,
					SmallConf			&root)
{
  char			buffer[256];

  read_separator(code, i);
  if (getfieldname(code, i, &buffer[0], sizeof(buffer), root, false) == false)
    return (NULL);
  read_separator(code, i);
  if (readtext(code, i, "]") == false)
    {
      fprintf(stderr, "The ']' token was expected after scope name. (Line %d)\n", whichline(code, i));
      return (NULL);
    }
  return (&root[&buffer[0]]);
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
  child = &conf["@"]; // Create the INI "default node"
  while (code[i])
    {
      read_separator(code, i);
      if (readtext(code, i, "["))
	{
	  if ((child = read_new_scope(code, i, conf)) == NULL)
	    {
	      SmallConf::create_mode = cmode;
	      return (NULL);
	    }
	}
      else if (code[i] != '\0')
	{
	  if (read_inside_scope(code, i, *child) == false)
	    {
	      SmallConf::create_mode = cmode;
	      return (NULL);
	    }
	}
      read_separator(code, i);
    }
  SmallConf::create_mode = cmode;
  return (config);
}

