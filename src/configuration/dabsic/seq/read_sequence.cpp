// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

/*
** Comment token: '#' '[* ... *]' ';'
**
** SEQUENCE := LABEL COMMAND COMMENTARIES '\n'
**
** LABEL := [INTEGER | C_STRING ':']? 
**
** COMMAND := C_STRING [EXPRESSION [',' EXPRESSION]*]?
*/

t_bunny_configuration	*_bunny_read_sequence(const char		*code,
					      t_bunny_configuration	*config)
{
  SmallConf		*conf = (SmallConf*)config;
  ssize_t		i;
  bool			cmode = SmallConf::create_mode;

  i = 0;
  SmallConf::create_mode = true;
  conf->construct = SmallConf::MAP;
  if (dabsic_read_inside_sequence(code, i, *conf, *conf) != BD_OK)
    {
      SmallConf::create_mode = cmode;
      return (NULL);
    }
  SmallConf::create_mode = cmode;
  scream_log_if("%s code, %p config -> %p", code, config, config);
  return (config);
}

