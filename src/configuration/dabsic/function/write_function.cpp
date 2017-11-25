// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include	"lapin_private.h"

typedef void	(*t_restore)(std::stringstream			&ss,
			     Function				&func,
			     SmallConf				&conf,
			     size_t				indent);
void		restore_scope(std::stringstream			&ss,
			      Function				&func,
			      SmallConf				&conf,
			      size_t				indent);

// // // // // // // // // // // // // // // // // // // // // // // //

void		restore_instruction(std::stringstream		&ss,
				    Function			&func,
				    SmallConf			&conf,
				    size_t			indent)
{
  (void)ss;
  (void)func;
  (void)conf;
  (void)indent;
  ss << " ";
  //ss << "EXPRESSION";
}

void		restore_if(std::stringstream			&ss,
			   Function				&func,
			   SmallConf				&conf,
			   size_t				indent)
{
  size_t	i;

  for (i = 0; i < indent; ++i)
    ss << " ";
  ss << "If ";
  restore_instruction(ss, func, conf, indent);
  ss << " Then" << std::endl;

  restore_scope(ss, func, conf, indent + 2);

  for (i = 0; i < indent; ++i)
    ss << " ";
  ss << "EndIf" << std::endl;
}

void		restore_else_if(std::stringstream		&ss,
				Function			&func,
				SmallConf			&conf,
				size_t				indent)
{
  size_t	i;

  for (i = 0; i < indent - 2; ++i)
    ss << " ";
  ss << "Else If ";
  restore_instruction(ss, func, conf, indent);
  ss << " Then" << std::endl;
  restore_scope(ss, func, conf, indent);
}

void		restore_else(std::stringstream			&ss,
			     Function				&func,
			     SmallConf				&conf,
			     size_t				indent)
{
  size_t	i;

  for (i = 0; i < indent - 2; ++i)
    ss << " ";
  ss << "Else" << std::endl;
  restore_scope(ss, func, conf, indent);
}

void		restore_print(std::stringstream			&ss,
			      Function				&func,
			      SmallConf				&conf,
			      size_t				indent)
{
  size_t	i;

  (void)conf;
  for (i = 0; i < indent; ++i)
    ss << " ";
  for (i = 0; i < func.value.Size(); )
    {
      writevalue(ss, func.value[i]);
      if (++i < func.value.Size())
	ss << ", ";
    }
  ss << std::endl;
}

t_restore	gl_restore[Function::LAST_COMMAND] =
  {
    &restore_instruction,
    &restore_if,
    &restore_else_if,
    &restore_else,
    &restore_print
  };

void		restore_scope(std::stringstream			&ss,
			      Function				&func,
			      SmallConf				&conf,
			      size_t				indent)
{
  std::map<std::string, SmallConf*>::iterator it;
  size_t	i;

  for (it = func.local_variables.Begin(); it != func.local_variables.End(); ++it)
    {
      for (i = 0; i < indent; ++i)
	ss << " ";
      if (it->second->last_type == SmallConf::STRING)
	ss << "string";
      else if (it->second->last_type == SmallConf::DOUBLE)
	ss << "real";
      else if (it->second->last_type == SmallConf::INTEGER)
	ss << "integer";
      else
	{}
      ss << " " << it->first;
      if (it->second->have_value)
	{
	  ss << " = ";
	  writevalue(ss, *it->second);
	}
      ss << std::endl;
    }

  for (i = 0; i < func.nbr_lines; ++i)
    gl_restore[func.lines[i].command](ss, func.lines[i], conf, indent);
}


void		restore_function(std::stringstream		&ss,
				 SmallConf			&conf,
				 size_t				indent)
{
  if (conf.function == NULL)
    return ;
  restore_scope(ss, *conf.function, conf, indent);
}

char
*_bunny_write_dabsic_function(const t_bunny_configuration	*config)
{
  std::stringstream	ss;
  char			*ret;

  restore_function(ss, *(SmallConf*)config, 2);
  if ((ret = (char*)bunny_malloc(sizeof(*ret) * (ss.str().size() + 1))) == NULL)
    scream_error_if(return (NULL), bunny_errno, "%p -> %s", config, ret);
  strcpy(ret, ss.str().c_str());
  scream_log_if("%p -> %s", config, ret);
  return (ret);
}

