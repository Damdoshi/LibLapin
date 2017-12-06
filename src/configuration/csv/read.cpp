// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

Decision		csv_read(const char				*code,
				 ssize_t				&i,
				 SmallConf				&conf,
				 SmallConf				&root)
{
  int			x, y;

  y = 0;
  x = 0;
  conf.construct = SmallConf::ARRAY;
  while (code[i] && code[i] != ']')
    {
      skipspace_inline(code, i);
      if (code[i])
	{
	  if (code[i] == '@')
	    {
	      if (_bunny_handle_directive(code, i, &conf[y][x], &root, skipspace_inline) == false)
		scream_error_if
		  (return (BD_ERROR), BE_SYNTAX_ERROR,
		   "%s code, %p config -> %p "
		   "(Cannot load required file from line %d, column %d)",
		   "ressource,configuration,syntax",
		   code, &conf, (void*)NULL, y, x);
	    }
	  else if (readvalue(code, i, conf[y][x], ";\n") == false)
	    scream_error_if
	      (return (BD_ERROR), BE_SYNTAX_ERROR,
	       "%s code, %p config -> %p "
	       "(A correct value was expected on line %d, column %d)",
	       "ressource,configuration,syntax",
	       code, &conf, (void*)NULL, y, x);
	  conf[y].construct = SmallConf::ARRAY;
	  skipspace_inline(code, i);
	  if (readtext(code, i, "\n"))
	    {
	      x = 0;
	      y += 1;
	    }
	  else if (readtext(code, i, ";"))
	    x += 1;
	}
    }
  return (BD_OK);
}

t_bunny_configuration	*_bunny_read_csv(const char			*code,
					 t_bunny_configuration		*config)
{
  SmallConf		&conf = *(SmallConf*)config;
  bool			cmode;
  ssize_t		i;

  i = 0;
  cmode = SmallConf::create_mode;
  SmallConf::create_mode = true;
  if (csv_read(code, i, conf, conf) != BD_OK)
    {
      SmallConf::create_mode = cmode;
      return (NULL);
    }
  SmallConf::create_mode = cmode;
  scream_log_if("%s code, %p config -> %p", "ressource,configuration", code, config, config);
  return (config);
}
