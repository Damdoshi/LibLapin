// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

void			dabsic_field_value(std::stringstream			&ss,
					   SmallConf				&conf,
					   ssize_t				indent);
void			restore_dabsic(std::stringstream			&ss,
				       SmallConf				&conf,
				       ssize_t					indent);

void			dabsic_array(std::stringstream				&ss,
				     SmallConf					&conf,
				     ssize_t					indent)
{
  ssize_t		i;

  for (i = 0; i < (ssize_t)conf.Size(); ++i)
    {
      if (conf[i].Begin() != conf[i].End())
	{
	  ss << "[" << conf[i].name;
	  dabsic_field_value(ss, conf[i], indent + 2);
	  restore_dabsic(ss, conf[i], indent + 2);
	  for (i = 0; i < indent; ++i)
	    ss << " ";
	  ss << "]" << std::endl;
	}
      else if (conf[i].Size())
	{
	  ss << "[Data";
	  dabsic_array(ss, conf, indent + 2);
	  for (i = 0; i < indent; ++i)
	    ss << " ";
	  ss << "]";
	}
      else
	writevalue(ss, conf[i]);
    }
}

void			dabsic_field_value(std::stringstream			&ss,
					   SmallConf				&conf,
					   ssize_t				indent)
{
  ssize_t		i;
  
  if (conf.have_value)
    {
      ss << " = ";
      writevalue(ss, conf);
    }
  else if (conf.Size())
    {
      ss << " = [Data" << std::endl;
      dabsic_array(ss, conf, indent + 2);
      ss << std::endl;
      for (i = 0; i < indent; ++i)
	ss << " ";  
      ss << "]";
    }
  ss << std::endl;
}

void			restore_dabsic(std::stringstream			&ss,
				       SmallConf				&conf,
				       ssize_t					indent)
{
  std::map<std::string, SmallConf*>::iterator it;
  ssize_t		i;
  
  dabsic_field_value(ss, conf, indent);
  for (it = conf.Begin(); it != conf.End(); ++it)
    {
      for (i = 0; i < indent; ++i)
	ss << " ";
      if (it->second->Begin() == it->second->End())
	{
	  ss << it->second->name;
	  dabsic_field_value(ss, *it->second, indent + 2);
	}
      else
	{
	  ss << "[" << it->second->name;
	  restore_dabsic(ss, *it->second, indent + 2);
	  for (i = 0; i < indent; ++i)
	    ss << " ";
	  ss << "]" << std::endl;;
	}
    }
}

char			*_bunny_write_dabsic(const t_bunny_configuration	*config)
{
  std::stringstream	ss;
  char			*ret;

  restore_dabsic(ss, *(SmallConf*)config, 0);
  if ((ret = (char*)bunny_malloc(sizeof(*ret) * (ss.str().size() + 1))) == NULL)
    return (NULL);
  strcpy(ret, ss.str().c_str());
  return (ret);
}

