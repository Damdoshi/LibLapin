// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"

char			*_bunny_write_ini(const t_bunny_configuration		*config)
{
  SmallConf		&conf = *(SmallConf*)config;
  std::map<std::string, SmallConf*>::const_iterator scope, field;
  std::stringstream	ss;
  size_t		index;
  char			*ret;

  if (conf.Access("@"))
    {
      SmallConf		&def = conf["@"];

      for (field = def.Begin(); field != def.End(); ++field)
	{
	  ss << field->first << "=";
	  for (index = 0; index != field->second->Size(); )
	    {
	      writevalue(ss, (*field->second)[index]);
	      if (++index != field->second->Size())
		ss << ",";
	    }
	  ss << std::endl;
	}
    }
  
  for (scope = conf.Begin(); scope != conf.End(); ++scope)
    if (scope->first != "@")
      {
	ss << std::endl << "[" << scope->first << "]" << std::endl;
	for (field = scope->second->Begin(); field != scope->second->End(); ++field)
	  {
	    ss << field->first << "=";
	    for (index = 0; index != field->second->Size(); )
	      {
		writevalue(ss, (*field->second)[index]);
		if (++index != field->second->Size())
		  ss << ",";
	      }
	    ss << std::endl;
	  }
      }
  if ((ret = (char*)bunny_malloc(sizeof(*ret) * (ss.str().size() + 1))) == NULL)
    scream_error_if(return (NULL), bunny_errno, "%p -> %s", config, ret);
  strcpy(ret, ss.str().c_str());
  scream_log_if("%p -> %s", config, ret);
  return (ret);
}

