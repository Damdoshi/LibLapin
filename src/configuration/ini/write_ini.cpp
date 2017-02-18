// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

char			*_bunny_write_ini(const t_bunny_configuration		*config)
{
  SmallConf		&conf = *(SmallConf*)config;
  std::map<std::string, SmallConf*>::const_iterator scope, field, index;
  std::stringstream	ss;
  char			*ret;

  if (conf.Access("default"))
    {
      SmallConf		&def = conf["default"];

      for (field = def.Begin(); field != def.End(); ++field)
	{
	  ss << field->first << "=";
	  for (index = field->second->Begin(); index != field->second->End(); )
	    {
	      writevalue(ss, *index->second);
	      if (++index != field->second->End())
		ss << ",";
	    }
	  ss << std::endl;
	}
    }
  
  for (scope = conf.Begin(); scope != conf.End(); ++scope)
    if (scope->first != "default")
      {
	ss << std::endl << "[" << scope->first << "]" << std::endl;
	for (field = scope->second->Begin(); field != scope->second->End(); ++field)
	  {
	    ss << field->first << "=";
	    for (index = field->second->Begin(); index != field->second->End(); )
	      {
		if (index->second->last_type == SmallConf::DOUBLE)
		  ss << index->second->converted;
		else if (index->second->last_type == SmallConf::INTEGER)
		  ss << index->second->converted_2;
		else if (index->second->last_type == SmallConf::STRING)
		  writestring(ss, index->second->original_value);
		else
		  ss << index->second->original_value;

		if (++index != field->second->End())
		  ss << ",";
	      }
	    ss << std::endl;
	  }
      }
  if ((ret = (char*)bunny_malloc(sizeof(*ret) * (ss.str().size() + 1))) == NULL)
    return (NULL);
  strcpy(ret, ss.str().c_str());
  return (ret);
}

