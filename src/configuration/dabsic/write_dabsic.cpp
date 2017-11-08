// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

static void		restore_dabsic(std::stringstream			&ss,
				       SmallConf				&conf,
				       ssize_t					indent);

static bool		got_real_field(SmallConf				&conf)
{
  std::map<std::string, SmallConf*>::iterator it;

  for (it = conf.Begin(); it != conf.End(); ++it)
    if (it->second->name[0] != '.')
      return (true);
  return (false);
}

static void		restore_prototype(std::stringstream			&ss,
					  SmallConf				&conf)
{
  ssize_t		i;

  if (conf.Access(".parameters") == false)
    return ;
  SmallConf		&params = conf[".parameters"];

  ss << "(";
  for (i = 0; i < (ssize_t)params.Size(); ++i)
    {
      ss << params[i].original_value;
      if (i + 1 < (ssize_t)params.Size())
	ss << ", ";
    }
  ss << ")";
}

static void		dabsic_array(std::stringstream				&ss,
				     SmallConf					&conf,
				     ssize_t					indent)
{
  ssize_t		i, j;

  restore_prototype(ss, conf);
  if (conf.have_value)
    {
      ss <<  " = ";
      writevalue(ss, conf);
      ss << std::endl;
    }
  else
    ss << std::endl;
  for (i = 0; i < (ssize_t)conf.Size(); ++i)
    {
      if (conf[i].name[0] == '.')
	continue ;
      for (j = 0; j < indent; ++j)
	ss << " ";
      if (got_real_field(conf[i]))
	{
	  ss << "[";
	  if (conf[i].given_name)
	    ss << conf[i].name;
	  restore_dabsic(ss, conf[i], indent + 2);
	  for (j = 0; j < indent; ++j)
	    ss << " ";
	  ss << "]";
	}
      else if (conf[i].Size() > 0)
	{
	  ss << "{";
	  if (conf[i].given_name)
	    ss << conf[i].name;
	  dabsic_array(ss, conf[i], indent + 2);
	  for (j = 0; j < indent; ++j)
	    ss << " ";
	  ss << "}";
	}
      else if (conf[i].given_name)
	{
	  ss << "[" << conf[i].name;
	  writevalue(ss, conf[i]);
	  ss << "]";
	}
      else
	writevalue(ss, conf[i]);
      if (i + 1 < (ssize_t)conf.Size())
	ss << "," << std::endl;
      else
	ss << std::endl;
    }
}

static void		restore_dabsic(std::stringstream			&ss,
				       SmallConf				&conf,
				       ssize_t					indent)
{
  std::map<std::string, SmallConf*>::iterator it;
  ssize_t		i;

  restore_prototype(ss, conf);
  if (conf.have_value || conf.Size() > 0)
    {
      ss <<  " = ";
      if (conf.Size() > 0)
	{
	  ss << "[Data";
	  dabsic_array(ss, conf, indent + 2);
	  for (i = 0; i < indent; ++i)
	    ss << " ";
	  ss << "]" << std::endl;
	}
      else
	writevalue(ss, conf);
      ss << std::endl;
    }
  else
    ss << std::endl;
  for (it = conf.Begin(); it != conf.End(); ++it)
    {
      if (it->second->name[0] == '.')
	continue ;
      for (i = 0; i < indent; ++i)
	ss << " ";
      if (got_real_field(*it->second))
	{
	  ss << "[" << it->second->name;
	  restore_dabsic(ss, *it->second, indent + 2);
	  for (i = 0; i < indent; ++i)
	    ss << " ";
	  ss << "]" << std::endl;
	}
      else if (it->second->Size() > 0)
	{
	  ss << "{" << it->second->name;
	  dabsic_array(ss, *it->second, indent + 2);
	  for (i = 0; i < indent; ++i)
	    ss << " ";
	  ss << "}" << std::endl;
	}
      else
	{
	  ss << it->second->name;
	  restore_prototype(ss, *it->second);
	  if (it->second->have_value || it->second->Size())
	    {
	      ss << " = ";
	      if (it->second->Size())
		writevalue(ss, (*it->second)[0]);
	      else
		writevalue(ss, (*it->second));
	    }
	}
      ss << std::endl;
    }
}

char			*_bunny_write_dabsic(const t_bunny_configuration	*config)
{
  std::stringstream	ss;
  char			*ret;

  restore_dabsic(ss, *(SmallConf*)config, 0);
  if ((ret = (char*)bunny_malloc(sizeof(*ret) * (ss.str().size() + 1))) == NULL)
    scream_error_if(return (NULL), bunny_errno, "%p -> %s", config, ret);
  strcpy(ret, ss.str().c_str());
  scream_log_if("%p -> %s", config, ret);
  return (ret);
}

