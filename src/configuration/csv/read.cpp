// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

t_bunny_configuration	*_bunny_read_csv(const char			*code,
					 t_bunny_configuration		*config)
{
  SmallConf		&conf = *(SmallConf*)config;
  bool			cmode;
  int			x, y;
  ssize_t		i;

  cmode = SmallConf::create_mode;
  SmallConf::create_mode = true;
  y = 0;
  x = 0;
  i = 0;
  while (code[i])
    {
      skipspace_inline(code, i);
      if (code[i])
	{
	  if (code[i] == '@')
	    {
	      if (_bunny_handle_directive(code, i, &conf[y][x], NULL, skipspace_inline) == false)
		scream_error_if
		  (return (NULL), BE_SYNTAX_ERROR,
		   "%s code, %p config -> %p "
		   "(Cannot load required file from line %d, column %d)",
		   code, config, (void*)NULL, y, x);
	    }
	  else if (readvalue(code, i, conf[y][x], ";\n") == false)
	    scream_error_if
	      (return (NULL), BE_SYNTAX_ERROR,
	       "%s code, %p config -> %p "
	       "(A correct value was expected on line %d, column %d)",
	       code, config, (void*)NULL, y, x);
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
  SmallConf::create_mode = cmode;
  scream_log_if("%s code, %p config -> %p", code, config, config);
  return (config);
}

