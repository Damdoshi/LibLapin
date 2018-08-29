// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include	"lapin_private.h"

typedef void	(*t_restore)(std::ostream			&ss,
			     Function				&func,
			     SmallConf				&conf,
			     size_t				indent);
extern t_restore gl_restore[Function::LAST_COMMAND];
void		restore_scope(std::ostream			&ss,
			      Function				&func,
			      SmallConf				&conf,
			      size_t				indent);

// // // // // // // // // // // // // // // // // // // // // // // //

void		restore_instruction(std::ostream		&ss,
				    Function			&func,
				    SmallConf			&conf,
				    size_t			indent)
{
  size_t	i;

  (void)conf;
  for (i = 0; i < indent; ++i)
    ss << " ";
  restore_expression(ss, *func.value.expression, true);
  ss << std::endl;
}

void		restore_while(std::ostream			&ss,
			      Function				&func,
			      SmallConf				&conf,
			      size_t				indent)
{
  size_t	i;

  for (i = 0; i < indent; ++i)
    ss << " ";
  ss << "While ";
  restore_instruction(ss, func, conf, indent);

  restore_scope(ss, func, conf, indent + 2);

  for (i = 0; i < indent; ++i)
    ss << " ";
  ss << "WEnd" << std::endl;
}

void		restore_repeat(std::ostream			&ss,
			       Function				&func,
			       SmallConf			&conf,
			       size_t				indent)
{
  size_t	i;

  for (i = 0; i < indent; ++i)
    ss << " ";
  ss << "Repeat" << std::endl;

  restore_scope(ss, func, conf, indent + 2);

  for (i = 0; i < indent; ++i)
    ss << " ";
  ss << "Until ";
  restore_expression(ss, *func.value.expression, true);
  ss << std::endl;
}

void		restore_with(std::ostream			&ss,
			     Function				&func,
			     SmallConf				&conf,
			     size_t				indent)
{
  size_t	i;

  for (i = 0; i < indent; ++i)
    ss << " ";
  ss << "With ";

  // Uncomment when address (dabsic pointer) will be accepted data types.
  // restore_expression(ss, *func.value.expression, true);
  writevalue(ss, func.value);
  ss << std::endl;

  restore_scope(ss, func, conf, indent + 2);

  for (i = 0; i < indent; ++i)
    ss << " ";
  ss << "EndWith" << std::endl;
}

void		restore_do(std::ostream				&ss,
			   Function				&func,
			   SmallConf				&conf,
			   size_t				indent)
{
  size_t	i;

  for (i = 0; i < indent; ++i)
    ss << " ";
  ss << "Do" << std::endl;

  restore_scope(ss, func, conf, indent + 2);

  for (i = 0; i < indent; ++i)
    ss << " ";
  ss << "AgainIf ";
  restore_expression(ss, *func.value.expression, true);
  ss << std::endl;
}

void		restore_for(std::ostream			&ss,
			    Function				&func,
			    SmallConf				&conf,
			    size_t				indent)
{
  size_t	i;

  for (i = 0; i < indent; ++i)
    ss << " ";
  ss << "For ";
  restore_expression(ss, *func.value.expression, true);
  ss << " To ";
  restore_expression(ss, *func.additionnal_values[0].expression, true);
  ss << " Step ";
  restore_expression(ss, *func.additionnal_values[1].expression, true);
  ss << std::endl;

  restore_scope(ss, func, conf, indent + 2);

  for (i = 0; i < indent; ++i)
    ss << " ";
  ss << "Next" << std::endl;
}

void		restore_if(std::ostream				&ss,
			   Function				&func,
			   SmallConf				&conf,
			   size_t				indent)
{
  size_t	i;

  for (i = 0; i < indent; ++i)
    ss << " ";
  ss << "If ";
  restore_expression(ss, *func.value.expression, true);
  if (func.nbr_lines == 1)
    {
      ss << " Then" << std::endl;
      gl_restore[func.lines[0].command](ss, func.lines[0], conf, indent + 2);
    }
  else
    {
      ss << std::endl;
      restore_scope(ss, func, conf, indent + 2);
      for (i = 0; i < indent; ++i)
	ss << " ";
      ss << "EndIf" << std::endl;
    }
}

void		restore_select(std::ostream			&ss,
			       Function				&func,
			       SmallConf			&conf,
			       size_t				indent)
{
  size_t	i;
  size_t	j;

  for (i = 0; i < indent; ++i)
    ss << " ";
  ss << "Select ";
  restore_expression(ss, *func.value.expression, true);
  ss << std::endl;

  for (j = 0; j < func.nbr_lines; ++j)
    {
      for (i = 0; i < indent + 1; ++i)
	ss << " ";
      ss << "Case ";
      restore_expression(ss, *func.lines[j].value.expression, true);
      ss << std::endl;
      restore_scope(ss, func.lines[j], conf, indent + 2);
    }

  for (i = 0; i < indent; ++i)
    ss << " ";
  ss << "EndSelect" << std::endl;
}

void		restore_else_if(std::ostream			&ss,
				Function			&func,
				SmallConf			&conf,
				size_t				indent)
{
  size_t	i;

  for (i = 0; i < indent - 2; ++i)
    ss << " ";
  ss << "Else If ";
  restore_expression(ss, *func.value.expression, true);
  if (func.nbr_lines == 1)
    {
      ss << " Then" << std::endl;
      gl_restore[func.lines[0].command](ss, func.lines[0], conf, indent + 2);
    }
  else
    restore_scope(ss, func, conf, indent);
}

void		restore_else(std::ostream			&ss,
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

void		restore_print(std::ostream			&ss,
			      Function				&func,
			      SmallConf				&conf,
			      size_t				indent)
{
  size_t	i;

  (void)conf;
  for (i = 0; i < indent; ++i)
    ss << " ";
  if (func.command == Function::PRINT)
    ss << "$";
  else
    ss << "!";
  for (i = 0; i < func.value.Size(); )
    {
      restore_expression(ss, *func.value[i].expression, true);
      if (++i < func.value.Size())
	ss << ", ";
    }
  ss << std::endl;
}

void		restore_break(std::ostream			&ss,
			      Function				&func,
			      SmallConf				&conf,
			      size_t				indent)
{
  size_t	i;

  (void)func;
  (void)conf;
  for (i = 0; i < indent; ++i)
    ss << " ";
  ss << "Break" << std::endl;
}

void		restore_brake(std::ostream			&ss,
			      Function				&func,
			      SmallConf				&conf,
			      size_t				indent)
{
  size_t	i;

  (void)func;
  (void)conf;
  for (i = 0; i < indent; ++i)
    ss << " ";
  ss << "Brake" << std::endl;
}

void		restore_continue(std::ostream			&ss,
				 Function			&func,
				 SmallConf			&conf,
				 size_t				indent)
{
  size_t	i;

  (void)func;
  (void)conf;
  for (i = 0; i < indent; ++i)
    ss << " ";
  ss << "Continue" << std::endl;
}

void		restore_return(std::ostream			&ss,
			       Function				&func,
			       SmallConf			&conf,
			       size_t				indent)
{
  size_t	i;

  (void)func;
  (void)conf;
  for (i = 0; i < indent; ++i)
    ss << " ";
  if (func.value.expression)
    {
      ss << "Return ";
      restore_expression(ss, *func.value.expression, true);
      ss << std::endl;
    }
  else
    ss << "Leave" << std::endl;
}

t_restore	gl_restore[Function::LAST_COMMAND] =
  {
    &restore_instruction,
    &restore_if,
    &restore_else_if,
    &restore_else,
    &restore_print,
    &restore_print,
    &restore_while,
    &restore_for,
    &restore_repeat,
    &restore_do,
    &restore_break,
    &restore_continue,
    &restore_return,
    &restore_brake,
    &restore_with,
    &restore_select
  };

void		restore_scope(std::ostream			&ss,
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


void		restore_function(std::ostream			&ss,
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

  restore_function(ss, *(SmallConf*)config, 0);
  if ((ret = (char*)bunny_malloc(sizeof(*ret) * (ss.str().size() + 1))) == NULL)
    scream_error_if(return (NULL), bunny_errno, "%p -> %s", "ressource,configuration", config, ret);
  strcpy(ret, ss.str().c_str());
  scream_log_if("%p -> %s", "ressource,configuration", config, ret);
  return (ret);
}

