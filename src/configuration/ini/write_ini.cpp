// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

char			*_bunny_write_ini(const t_bunny_configuration		*config)
{
  SmallConf		&conf = *(SmallConf*)config;
  std::map<std::string, SmallConf*>::const_iterator scope;
  std::stringstream	ss;
  size_t		index;
  char			*ret;

  for (scope = conf.Begin(); scope != conf.End(); ++scope)
    if (scope->second->NbrChild() == 0)
      {
	ss << scope->first << "=";
	if (scope->second->Size() == 0)
	  {
	    if (scope->second->expression)
	      {
		ss << "$";
		restore_expression(ss, *scope->second->expression, true);
	      }
	    else
	      writevalue(ss, (*scope->second));
	  }
	else
	  for (index = 0; index != scope->second->Size(); )
	    {
	      if ((*scope->second)[index].NbrChild() == 0)
		{
		  if ((*scope->second)[index].expression)
		    {
		      ss << "$";
		      restore_expression
			(ss, *(*scope->second)[index].expression, true);
		    }
		  else
		    writevalue(ss, (*scope->second)[index]);
		}
	      else
		ss << "&" << bunny_configuration_get_address((const void*)&(*scope->second)[index]);
	      if (++index != scope->second->Size())
		ss << ",";
	    }
	ss << std::endl;
      }

  for (scope = conf.Begin(); scope != conf.End(); ++scope)
    if (scope->second->NbrChild() == 0)
      {
	for (index = 0; index != scope->second->Size(); ++index)
	  if ((*scope->second)[index].NbrChild() != 0)
	    {
	      ss << std::endl << "["
		 << bunny_configuration_get_address((const void*)&(*scope->second)[index])
		 << "]" << std::endl;
	      if ((ret = _bunny_write_ini((const void*)&((*scope->second)[index]))) == NULL)
		return (NULL);
	      ss << ret;
	      bunny_free(ret);
	    }
      }
    else
      {
	ss << std::endl << "[" << bunny_configuration_get_address(scope->second) << "]" << std::endl;
	if ((ret = _bunny_write_ini(scope->second)) == NULL)
	  return (NULL);
	ss << ret;
	bunny_free(ret);
      }
  if ((ret = bunny_strndup(ss.str().c_str(), ss.str().size() + 1)) == NULL)
    scream_error_if(return (NULL), bunny_errno, "%p -> %s", "ressource,configuration", config, ret);
  scream_log_if("%p -> %s", "ressource,configuration", config, ret);
  return (ret);
}

