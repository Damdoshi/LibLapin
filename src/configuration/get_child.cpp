// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

#define			PATTERN		"%p conf, %s child -> %p"

t_bunny_configuration	*bunny_configuration_get_child(t_bunny_configuration	*conf,
						       const char		*child)
{
  SmallConf		*c = (SmallConf*)conf;
  t_bunny_configuration	*cnf = NULL;
  std::string		str = child;

  try
    {
      if ((cnf = ((t_bunny_configuration*)&(*c)[str])) == NULL)
	scream_error_if(return (cnf), bunny_errno, PATTERN, conf, child, cnf);
      scream_log_if(PATTERN, conf, child, cnf);
      return (cnf);
    }
  catch (...)
    {}
  scream_error_if(return (cnf), bunny_errno, PATTERN, conf, child, cnf);
  return (NULL);
}

