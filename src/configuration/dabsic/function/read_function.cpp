// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

/*
** SCRIPT := VARIABLES STATEMENT
** TERMINATOR := ['\n' | '\r' | ';']+
**
** VARIABLES := [VARIABLE TERMINATOR]*
** VARIABLE :=
** | 'string' C_SYMBOL ['=' value]?
** | 'real' C_SYMBOL ['=' value]?
** | 'integer' C_SYMBOL ['=' value]?
**
** STATEMENT := IF | WHILE | FOR | DO | EXPRESSION
*/

t_bunny_configuration	*_bunny_read_function(const char		*code,
					      t_bunny_configuration	*config)
{
  SmallConf		*conf = (SmallConf*)config;
  ssize_t		i;
  bool			cmode = SmallConf::create_mode;

  i = 0;
  SmallConf::create_mode = true;
  conf->construct = SmallConf::MAP;
  if (dabsic_read_inside_function(code, i, NULL, *conf, *conf) != BD_OK)
    {
      SmallConf::create_mode = cmode;
      return (NULL);
    }
  SmallConf::create_mode = cmode;
  scream_log_if
    ("%s code, %p config -> %p", "ressource,configuration", code, config, config);
  return (config);
}

