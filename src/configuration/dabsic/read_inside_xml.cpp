// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

Decision		dabsic_read_inside_xml(const char		*code,
					       ssize_t			&i,
					       SmallConf		&conf,
					       SmallConf		&root)
{
  xml_read_between_markup(code, i, conf, root);
  return (BD_OK);
}

