// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

/*
** DABSIC ::= INSIDE_SCOPE
**
** INSIDE_SCOPE ::= FIELD_VALUE? [FIELD]*
**
** FIELD_VALUE ::= '=' [SCOPE | SEQUENCE | FUNCTION | XML | ARRAY | LITTERALS]
**
** FIELD ::=
**   FIELD_NAME FIELD_VALUE
** | '[' FIELD_NAME INSIDE_SCOPE ']'
** | '{' FIELD_NAME INSIDE_ARRAY '}'
** | '<' FIELD_NAME INSIDE_XML   '>'
**
** SCOPE ::= ['[Scope' | '['] INSIDE_SCOPE ']'
** SEQUENCE ::= '[Sequence' INSIDE_SEQUENCE ']'
** FUNCTION ::= '[Function' INSIDE_FUNCTION ']'
** XML ::= ['[XML' | '<'] INSIDE_XML [']' | '>']
** ARRAY ::= ['[Data' | '[Array' | '{'] INSIDE_ARRAY [']' | '}']
**
** LITTERALS ::= EXPRESSION [',' EXPRESSION]*
**
** FIELD_NAME ::= C_SYMBOL ['(' C_SYMBOL [',' C_SYMBOL]* ')']?    # '(' right after
**
** INSIDE_ARRAY ::= [SCOPE | SEQUENCE | FUNCTION | XML | ARRAY | EXPRESSION]*
**
*/

t_bunny_configuration	*_bunny_read_dabsic(const char			*code,
					    t_bunny_configuration	*config)
{
  SmallConf		*conf = (SmallConf*)config;
  ssize_t		i;
  bool			cmode = SmallConf::create_mode;

  i = 0;
  SmallConf::create_mode = true;
  conf->construct = SmallConf::MAP;
  if (dabsic_read_inside_scope(code, i, *conf, *conf) != BD_OK)
    {
      SmallConf::create_mode = cmode;
      return (NULL);
    }
  SmallConf::create_mode = cmode;
  scream_log_if("%s code, %p config -> %p", code, config, config);
  return (config);
}

