// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

/*
** SCOPE := '{' INSIDE_SCOPE '}'
**
** INSIDE_SCOPE := FIELD? [',' FIELD]*
**
** FIELD := [FIELDNAME  ':' [LITTERAL, SCOPE, ARRAY]] | DIRECTIVE
**
** FIELDNAME := [C_SYMBOL | '[' INT ']']
**
** LITTERAL := C_STRING | INT | DOUBLE | BOOLEAN | DIRECTIVE
**
** ARRAY: := '[' INSIDE_ARRAY ']'
**
** INSIDE_ARRAY := ARRAY_NODE? [',' ARRAY_NODE]*
**
** ARRAY_NODE := LITTERAL | SCOPE | DIRECTIVE
*/

t_bunny_configuration	*_bunny_read_lua(const char			*code,
					 t_bunny_configuration		*config)
{
  SmallConf		*conf = (SmallConf*)config;
  ssize_t		i;
  bool			cmode = SmallConf::create_mode;

  i = 0;
  SmallConf::create_mode = true;
  conf->construct = SmallConf::MAP;
  if (lua_read_scope(code, i, *conf, *conf) != BD_OK)
    {
      SmallConf::create_mode = cmode;
      return (NULL);
    }
  SmallConf::create_mode = cmode;
  scream_log_if("%s code, %p config -> %p", "ressource,configuration", code, config, config);
  return (config);
}

