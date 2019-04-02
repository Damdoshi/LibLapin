// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

static bool		is_short_and_litterals(SmallConf		&conf)
{
  if (conf.Size() > 4)
    return (false);
  for (size_t i = 0; i < conf.Size(); ++i)
    if (conf[i].Size() != 0 || conf[i].NbrChild() != 0)
      return (false);
  return (true);
}

static void		restore_value(std::ostream			&ss,
				      SmallConf				&conf,
				      ssize_t				ind)
{
  ssize_t		i;

  if (conf.sequence)
    {
      ss << "[Sequence" << std::endl;
      restore_sequence(ss, conf, ind + 2);
      for (i = 0; i < ind; ++i)
	ss << " ";
      ss << "]";
    }
  else if (conf.function)
    {
      ss << "[Function" << std::endl;
      restore_function(ss, conf, ind + 2);
      for (i = 0; i < ind; ++i)
	ss << " ";
      ss << "]";
    }
  else if (conf.expression && conf.expression->optor_family != -1)
    restore_expression(ss, *conf.expression, true);
  else if (conf.have_value)
    writevalue(ss, conf);
}

static void		restore_dabsic(std::ostream			&ss,
				       SmallConf			&conf,
				       ssize_t				indent);

static bool		got_real_field(SmallConf			&conf)
{
  std::map<std::string, SmallConf*>::iterator it;

  for (it = conf.Begin(); it != conf.End(); ++it)
    if (it->second->name[0] != '.')
      return (true);
  return (false);
}

static void		restore_prototype(std::ostream			&ss,
					  SmallConf			&conf)
{
  ssize_t		i;

  if (conf.Access(".parameters"))
    {
      SmallConf		&params = conf[".parameters"];

      ss << "(";
      for (i = 0; i < (ssize_t)params.Size(); ++i)
	{
	  if (params[i].last_type == SmallConf::STRING)
	    ss << "string ";
	  else if (params[i].last_type == SmallConf::INTEGER)
	    ss << "integer ";
	  else if (params[i].last_type == SmallConf::DOUBLE)
	    ss << "real ";
	  ss << params[i].name;
	  if (params[i].expression)
	    {
	      ss << " = ";
	      restore_expression(ss, *params[i].expression, true);
	    }
	  if (i + 1 < (ssize_t)params.Size())
	    ss << ", ";
	}
      ss << ")";
      if (conf.last_type != SmallConf::NOTYPE)
	{
	  ss << ":";
	  if (conf.last_type == SmallConf::STRING)
	    ss << "string";
	  else if (conf.last_type == SmallConf::INTEGER)
	    ss << "integer";
	  else if (conf.last_type == SmallConf::DOUBLE)
	    ss << "real";
	}
    }

  if (conf.is_const >= SmallConf::LOCAL_POLITIC)
    ss << " const";
  if (conf.is_const > SmallConf::LOCAL_POLITIC)
    ss << "!";

  if (conf.is_solid >= SmallConf::LOCAL_POLITIC)
    ss << " solid";
  if (conf.is_solid > SmallConf::LOCAL_POLITIC)
    ss << "!";

  if (conf.is_eternal >= SmallConf::LOCAL_POLITIC)
    ss << " eternal";
  if (conf.is_eternal > SmallConf::LOCAL_POLITIC)
    ss << "!";
}

static void		dabsic_array(std::ostream			&ss,
				     SmallConf				&conf,
				     ssize_t				indent,
				     bool				shortform)
{
  ssize_t		i, j;

  restore_prototype(ss, conf);
  if (conf.have_value || conf.expression)
    {
      ss <<  " = ";
      restore_value(ss, conf, indent + 2);
      ss << std::endl;
    }
  else if (!shortform)
    ss << std::endl;
  for (i = 0; i < (ssize_t)conf.Size(); ++i)
    {
      if (conf[i].name[0] == '.')
	continue ;
      if (shortform == false)
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
	  dabsic_array(ss, conf[i], indent + 2, false);
	  for (j = 0; j < indent; ++j)
	    ss << " ";
	  ss << "}";
	}
      else if (conf[i].given_name)
	{
	  ss << "[" << conf[i].name;
	  restore_value(ss, conf[i], indent + 2);
	  ss << "]";
	}
      else
	restore_value(ss, conf[i], indent + 2);
      if (i + 1 < (ssize_t)conf.Size())
	ss << ",";
      if (shortform == false)
	ss << std::endl;
      else
	ss << " ";
    }
}

static void		restore_dabsic(std::ostream			&ss,
				       SmallConf			&conf,
				       ssize_t				indent)
{
  std::map<std::string, SmallConf*>::iterator it;
  ssize_t		i;

  restore_prototype(ss, conf);
  if (conf.have_value || conf.Size() > 0 || conf.expression || conf.function)
    {
      ss <<  " = ";
      if (conf.Size() > 0)
	{
	  if (is_short_and_litterals(conf))
	    {
	      dabsic_array(ss, conf, indent + 2, true);
	      ss << std::endl;
	    }
	  else
	    {
	      ss << "{";
	      dabsic_array(ss, conf, indent + 2, false);
	      for (i = 0; i < indent; ++i)
		ss << " ";
	      ss << "}" << std::endl;
	    }
	}
      else
	restore_value(ss, conf, indent);
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
	  if (is_short_and_litterals(*it->second))
	    {
	      ss << it->second->name << " = ";
	      dabsic_array(ss, *it->second, indent + 2, true);
	      ss << std::endl;
	    }
	  else
	    {
	      ss << "{" << it->second->name;
	      dabsic_array(ss, *it->second, indent + 2, false);
	      for (i = 0; i < indent; ++i)
		ss << " ";
	      ss << "}" << std::endl;
	    }
	}
      else
	{
	  ss << it->second->name;
	  restore_prototype(ss, *it->second);
	  if (it->second->have_value
	      || it->second->Size()
	      || it->second->expression
	      || it->second->function
	      || it->second->sequence)
	    {
	      ss << " = ";
	      if (it->second->Size())
		restore_value(ss, (*it->second)[0], indent);
	      else
		restore_value(ss, (*it->second), indent);
	    }
	}
      ss << std::endl;
    }
}

char			*_bunny_write_dabsic(const t_bunny_configuration *config)
{
  std::stringstream	ss;
  char			*ret;

  restore_dabsic(ss, *(SmallConf*)config, 0);
  if ((ret = (char*)bunny_malloc(sizeof(*ret) * (ss.str().size() + 1))) == NULL)
    scream_error_if(return (NULL), bunny_errno, "%p -> %s", "ressource,configuration", config, ret);
  strcpy(ret, ss.str().c_str());
  scream_log_if("%p -> %s", "ressource,configuration", config, ret);
  return (ret);
}

