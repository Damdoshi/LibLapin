// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

static void		restore_list(std::stringstream			&ss,
				     SmallConf				&conf,
				     size_t				indent)
{
  size_t		i, j;

  for (i = 0; i < conf.Size(); ++i)
    {
      for (j = 0; i != 0 && j < indent; ++j)
	ss << " ";
      if (conf[i].Size())
	{
	  ss << "(";
	  restore_list(ss, conf[i], indent + 2);
	  ss << ")" << std::endl;
	}
      else
	writevalue(ss, conf[i]);
      if (i + 1 < conf.Size())
	ss << std::endl;
    }
}

char			*_bunny_write_lisp(const t_bunny_configuration	*config)
{
  std::stringstream	ss;
  char			*ret;

  restore_list(ss, *(SmallConf*)config, 0);
  if ((ret = (char*)bunny_malloc(sizeof(*ret) * (ss.str().size() + 1))) == NULL)
    scream_error_if(return (NULL), bunny_errno, "%p -> %s", "ressource,configuration", config, ret);
  strcpy(ret, ss.str().c_str());
  scream_log_if("%p -> %s", "ressource,configuration", config, ret);
  return (ret);
}
