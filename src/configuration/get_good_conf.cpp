// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include			"lapin_private.h"

t_bunny_configuration		*_get_good_conf(const char		*file,
					       t_bunny_configuration	**conf)
{
  t_bunny_configuration		*ret;

  if (file == NULL)
    {
      if (conf == NULL || *conf == NULL)
	return (NULL);
      return (*conf);
    }
  t_bunny_configuration_type type = bunny_which_format(file);

  if (type == BC_CUSTOM)
    return (NULL);
  if (conf == NULL)
    {
      if ((ret = bunny_load_configuration(type, file, NULL)) == NULL)
	return (NULL);
      return (ret);
    }
  if ((ret = bunny_load_configuration(type, file, *conf)) == NULL)
    return (NULL);
  return (ret);
}

