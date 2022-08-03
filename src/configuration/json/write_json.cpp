// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<sstream>
#include		"lapin_private.h"

static void		restore_scope(std::stringstream		&ss,
				      SmallConf			&conf,
				      ssize_t			indent);

static void		restore_array(std::stringstream		&ss,
				      SmallConf			&conf,
				      ssize_t			indent)
{
  size_t		j;
  ssize_t		i;

  for (j = 0; j < conf.Size(); ++j)
    {
      for (i = 0; i < indent; ++i)
	ss << " ";
      if (conf[j].Size())
	{
	  ss << "[" << std::endl;
	  restore_array(ss, conf[j], indent + 2);
	  for (i = 0; i < indent; ++i)
	    ss << " ";
	  ss << "]";
	}
      else if (conf[j].NbrChild())
	{
	  ss << "{" << std::endl;
	  restore_scope(ss, conf[j], indent + 2);
	  for (i = 0; i < indent; ++i)
	    ss << " ";
	  ss << "}";
	}
      else if (conf[j].expression)
	restore_expression(ss, *conf[j].expression, true, true);
      else if (conf[j].have_value)
	writevalue(ss, conf[j], true, true);
      if (j + 1 < conf.Size())
	ss << ",";
      ss << std::endl;
    }
}

static void		restore_scope(std::stringstream		&ss,
				      SmallConf			&conf,
				      ssize_t			indent)
{
  std::map<std::string, SmallConf*>::iterator it;
  ssize_t		i;

  for (it = conf.Begin(); it != conf.End(); )
    {
      for (i = 0; i < indent; ++i)
	ss << " ";
      writestring(ss, it->first);
      if (it->second->Size())
	{
	  ss << ": [" << std::endl;
	  restore_array(ss, *it->second, indent + 2);
	  for (i = 0; i < indent; ++i)
	    ss << " ";
	  ss << "]";
	}
      else if (it->second->NbrChild())
	{
	  ss << ": {" << std::endl;
	  restore_scope(ss, *it->second, indent + 2);
	  for (i = 0; i < indent; ++i)
	    ss << " ";
	  ss << "}";
	}
      else if (it->second->expression)
	{
	  ss << ": ";
	  restore_expression(ss, *it->second->expression, true, true);
	}
      else if (it->second->have_value)
	{
	  ss << ": ";
	  writevalue(ss, *it->second, true);
	}
      else
	ss << ": null";
      if (++it != conf.End())
	ss << ",";
      ss << std::endl;
    }
}

char			*_bunny_write_json(const t_bunny_configuration	*config)
{
  SmallConf		&cnf = *(SmallConf*)config;
  std::stringstream	ss;
  char			*ret;

  if (cnf.Size())
    {
      ss << "[" << std::endl;
      restore_array(ss, cnf, 2);
      ss << "]" << std::endl;
    }
  else
    {
      ss << "{" << std::endl;
      restore_scope(ss, cnf, 2);
      ss << "}" << std::endl;
    }
  if ((ret = (char*)bunny_malloc(sizeof(*ret) * (ss.str().size() + 1))) == NULL)
    scream_error_if(return (NULL), bunny_errno, "%p -> %s", "ressource,configuration", config, ret);
  strcpy(ret, ss.str().c_str());
  scream_log_if("%p -> %s", "ressource,configuration", config, ret);
  return (ret);
}

