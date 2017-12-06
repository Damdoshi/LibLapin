// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

void			lisp_read_separator(const char		*code,
					    ssize_t		&i)
{
  bool			once;

  once = true;
  skipspace(code, i);
  while (once == true)
    {
      once = false;
      while (strncmp(&code[i], ";", 1) == 0)
	{
	  once = true;
	  while (code[i] != '\0' && code[i] != '\n' && code[i] != '\r')
	    ++i;
	  skipspace(code, i);
	}
    }
}

Decision		lisp_read_list(const char		*code,
				       ssize_t			&i,
				       SmallConf		&conf,
				       SmallConf		&root)
{
  do
    {
      lisp_read_separator(code, i);
      if (readtext(code, i, "("))
	{
	  int		line;

	  line = whichline(code, i);
	  if (lisp_read_list(code, i, conf[conf.Size()], root) == BD_ERROR)
	    return (BD_ERROR);
	  if (readtext(code, i, ")") == false)
	    scream_error_if
	      (return (BD_ERROR), BE_SYNTAX_ERROR,
	       "The ')' token was expected to close the list opened "
	       "on line %d, on line %d",
	       "configuration,syntax",
	       line, whichline(code, i)
	       );
	}
      else if (code[i] == '@')
	{
	  if (_bunny_handle_directive
	      (code, i, &conf, &root, lisp_read_separator) == false)
	    return (BD_ERROR);
	}
      else if (readvalue(code, i, conf[conf.Size()], " )") == false)
	scream_error_if
	  (return (BD_ERROR), BE_SYNTAX_ERROR,
	   "A value, list or directive was expected on line %d",
	   "configuration,syntax",
	   whichline(code, i)
	   );
      lisp_read_separator(code, i);
    }
  while (code[i] && code[i] != ')');
  return (BD_OK);
}

t_bunny_configuration	*_bunny_read_lisp(const char		*code,
					  t_bunny_configuration	*config)
{
  SmallConf		*conf = (SmallConf*)config;
  ssize_t		i;
  bool			cmode = SmallConf::create_mode;

  i = 0;
  SmallConf::create_mode = true;
  conf->construct = SmallConf::MAP;
  if (lisp_read_list(code, i, *conf, *conf) != BD_OK)
    {
      SmallConf::create_mode = cmode;
      return (NULL);
    }
  SmallConf::create_mode = cmode;
  scream_log_if("%s code, %p config -> %p", "ressource,configuration", code, config, config);
  return (config);
}
