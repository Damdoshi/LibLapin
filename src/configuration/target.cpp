// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
//
// Lapin library

#include		<stdarg.h>
#include		"lapin_private.h"

bool			bunny_configuration_target(t_bunny_configuration	*_f,
						   t_bunny_configuration	*_t)
{
  SmallConf		*f = (SmallConf*)_f;
  SmallConf		*t = (SmallConf*)_t;

  f->last_type = SmallConf::RAWSTRING;
  f->have_value = true;
  f->original_value = t->address;
  return (true);
}


bool			bunny_configuration_targetf(t_bunny_configuration	*_f,
						    const char			*pattern,
						    ...)
{
  char			buffer[4096];
  va_list		lst;
  t_bunny_configuration	*cnf;

  va_start(lst, pattern);
  if ((vsnprintf(buffer, sizeof(buffer), pattern, lst)) >= (int)sizeof(buffer))
    return (false);
  if (bunny_configuration_getf_node(_f, &cnf, buffer) == false)
    return (false);
  return (bunny_configuration_target(_f, cnf));
}
