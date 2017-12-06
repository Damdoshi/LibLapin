// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

static void		restore_properties(std::stringstream		&ss,
					   SmallConf			&conf)
{
  std::map<std::string, SmallConf*>::iterator it;
  size_t		i;

  if (conf.have_value)
    {
      ss << "=";
      writevalue(ss, conf);
    }
  for (it = conf.Begin(); it != conf.End(); ++it)
    {
      ss << " " << it->second->name;
      if (it->second->Size() > 0)
	{
	  ss << "=";
	  for (i = 0; i < it->second->Size(); ++i)
	    {
	      writevalue(ss, (*it->second)[i]);
	      if (i + 1 < it->second->Size())
		ss << ",";
	    }
	}
      else if (it->second->have_value)
	{
	  ss << "=";
	  writevalue(ss, *it->second);
	}
    }
}

static void		restore_markup(std::stringstream		&ss,
				       SmallConf			&conf,
				       size_t				indent)
{
  size_t		i, j;

  for (i = 0; i < conf.Size(); ++i)
    {
      for (j = 0; j < indent; ++j)
	ss << " ";
      if (conf[i].given_name == false)
	ss << conf[i].original_value << std::endl;
      else
	{
	  ss << "<" << conf[i].name;
	  restore_properties(ss, conf[i]);
	  if (conf[i].Size() == 0)
	    ss << " />" << std::endl;
	  else
	    {
	      ss << ">" << std::endl;
	      restore_markup(ss, conf[i], indent + 2);
	      for (j = 0; j < indent; ++j)
		ss << " ";
	      ss << "</" << conf[i].name << ">" << std::endl;
	    }
	}
    }
}

char			*_bunny_write_xml(const t_bunny_configuration	*config)
{
  std::stringstream	ss;
  char			*ret;

  restore_markup(ss, *(SmallConf*)config, 0);
  if ((ret = (char*)bunny_malloc(sizeof(*ret) * ss.str().size() + 1)) == NULL)
    scream_error_if
      (return(NULL), bunny_errno, "%p -> %s", "ressource,configuration",
       config, ret);
  strcpy(ret, ss.str().c_str());
  scream_log_if("%p -> %s", "ressource,configuration", config, ret);
  return (ret);
}

