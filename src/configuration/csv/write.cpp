// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

char			*_bunny_write_csv(const t_bunny_configuration	*config)
{
  std::stringstream	ss;
  SmallConf		&conf = *(SmallConf*)config;
  size_t		i, j;
  char			*ret;

  for (j = 0; j < conf.Size(); ++j)
    {
      for (i = 0; i < conf[j].Size(); ++i)
	{
	  if (conf[j][i].have_value)
	    writevalue(ss, conf[j][i]);
	  if (i + 1 < conf[j].Size())
	    ss << ";";
	}
      ss << std::endl;
    }
  if ((ret = (char*)bunny_malloc(sizeof(*ret) * (ss.str().size() + 1))) == NULL)
    scream_error_if
      (return (NULL), ENOMEM, "%p -> %p", "ressource,configuration", config, ret);
  strcpy(ret, ss.str().c_str());
  scream_log_if("%p -> %p", "ressource,configuration", config, ret);
  return (ret);
}

