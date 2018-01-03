// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		<iostream>
#include		"lapin_private.h"

t_dabsic_compute	gl_dabsic_compute[Function::LAST_COMMAND] =
  {
    &dabsic_compute_instruction,
    &dabsic_compute_if,
    &dabsic_compute_no_execution,
    &dabsic_compute_no_execution,
    &dabsic_compute_print,
    &dabsic_compute_print,
    &dabsic_compute_while,
    &dabsic_compute_for,
    &dabsic_compute_repeat,
    &dabsic_compute_do,
    &dabsic_compute_break,
    &dabsic_compute_continue,
    &dabsic_compute_return,
    &dabsic_compute_brake,
    &dabsic_compute_with,
    &dabsic_compute_select
  };

t_compute_result	dabsic_compute_select(Function		&func,
					      Function		&mainnod,
					      bool		dry,
					      SmallConf		*root,
					      SmallConf		*local,
					      SmallConf		*artif,
					      SmallConf		*params)
{
  t_compute_result	ret;
  SmallConf		&loc = *local;
  size_t		i;
  int			cmode;
  int			selected;

  if (expr_compute(func.value, NULL, dry, root, local, artif, params) == false)
    return (CR_ERROR);
  cmode = SmallConf::create_mode;
  if (local)
    {
      SmallConf::create_mode = true;
      loc["Is"] = func.value;
    }

  for (i = 0; i < func.nbr_lines; ++i)
    {
      if (expr_compute
	  (func.lines[i].value, NULL, dry, root, local, artif, params)
	  == false)
	{
	  if (local)
	    delete &loc["Is"];
	  SmallConf::create_mode = cmode;
	  return (CR_ERROR);
	}

      if (func.lines[i].value.expression->operand.size() <= 1)
	selected = (func.value == func.lines[i].value);
      else
	{
	  if (func.lines[i].value.GetInt
	      (&selected, NULL, NULL, NULL, NULL) == false)
	    scream_error_if
	      (return (CR_ERROR), BE_SYNTAX_ERROR,
	       "An integer or an expression returning an integer was expected "
	       "as select case statement on line %s:%d",
	       "ressource,configuration,syntax",
	       func.file.c_str(), func.line);
	}
      if (selected)
	{
	  ret = dabsic_compute_scope
	    (func.lines[i], mainnod, dry, root, local, artif, params);
	  if (local)
	    delete &loc["Is"];
	  SmallConf::create_mode = cmode;
	  return (ret);
	}
    }
  if (local)
    delete &loc["Is"];
  SmallConf::create_mode = cmode;
  return (CR_OK);
}

t_compute_result	dabsic_compute_break(Function		&func,
					     Function		&mainnod,
					     bool		dry,
					     SmallConf		*root,
					     SmallConf		*local,
					     SmallConf		*artif,
					     SmallConf		*params)
{
  (void)func;
  (void)mainnod;
  (void)dry;
  (void)root;
  (void)local;
  (void)artif;
  (void)params;
  return (CR_BREAK);
}

t_compute_result	dabsic_compute_continue(Function	&func,
						Function	&mainnod,
						bool		dry,
						SmallConf	*root,
						SmallConf	*local,
						SmallConf	*artif,
						SmallConf	*params)
{
  (void)func;
  (void)mainnod;
  (void)dry;
  (void)root;
  (void)local;
  (void)artif;
  (void)params;
  return (CR_CONTINUE);
}

t_compute_result	dabsic_compute_brake(Function		&func,
					     Function		&mainnod,
					     bool		dry,
					     SmallConf		*root,
					     SmallConf		*local,
					     SmallConf		*artif,
					     SmallConf		*params)
{
  (void)func;
  (void)mainnod;
  (void)dry;
  (void)root;
  (void)local;
  (void)artif;
  (void)params;
  return (CR_OK);
}

t_compute_result	dabsic_compute_return(Function		&func,
					      Function		&mainnod,
					      bool		dry,
					      SmallConf		*root,
					      SmallConf		*local,
					      SmallConf		*artif,
					      SmallConf		*params)
{
  (void)func;
  (void)mainnod;
  (void)dry;
  (void)root;
  (void)local;
  (void)artif;
  (void)params;
  if (func.value.expression)
    {
      if (expr_compute(func.value, NULL, dry, root, local, artif, params) == false)
	return (CR_ERROR);
      mainnod.result = func.value;
    }
  return (CR_RETURN);
}

t_compute_result	dabsic_compute_instruction(Function	&func,
						   Function	&mainnod,
						   bool		dry,
						   SmallConf	*root,
						   SmallConf	*local,
						   SmallConf	*artif,
						   SmallConf	*params)
{
  (void)mainnod;
  if (expr_compute(func.value, NULL, dry, root, local, artif, params) == false)
    return (CR_ERROR);
  return (CR_OK);
}

t_compute_result	dabsic_compute_if(Function		&func,
					  Function		&mainnod,
					  bool			dry,
					  SmallConf		*root,
					  SmallConf		*local,
					  SmallConf		*artif,
					  SmallConf		*params)
{
  int			res;

  if (func.value.GetInt(&res, root, local, artif, params) == false)
    return (CR_ERROR);

  if (res)
    return (dabsic_compute_scope(func, mainnod, dry, root, local, artif, params));
  if (func.nbr_lines == 0)
    return (CR_OK);
  Function		*x = &func.lines[func.nbr_lines - 1];

  if (x->command == Function::ELSE_IF)
    return (dabsic_compute_if(*x, mainnod, dry, root, local, artif, params));
  if (x->command == Function::ELSE)
    return (dabsic_compute_scope(*x, mainnod, dry, root, local, artif, params));
  return (CR_OK);
}

t_compute_result	dabsic_compute_while(Function		&func,
					     Function		&mainnod,
					     bool		dry,
					     SmallConf		*root,
					     SmallConf		*local,
					     SmallConf		*artif,
					     SmallConf		*params)
{
  int			res = 1;
  t_compute_result	ret;

  while (res)
    {
      if (func.value.GetInt(&res, root, local, artif, params) == false)
	return (CR_ERROR);
      if (res)
	if ((ret = dabsic_compute_scope
	     (func, mainnod, dry, root, local, artif, params)) != CR_OK)
	  {
	    if (ret == CR_BREAK)
	      return (CR_OK);
	    if (ret == CR_RETURN)
	      return (ret);
	  }
    }
  return (CR_OK);
}

t_compute_result	dabsic_compute_repeat(Function		&func,
					      Function		&mainnod,
					      bool		dry,
					      SmallConf		*root,
					      SmallConf		*local,
					      SmallConf		*artif,
					      SmallConf		*params)
{
  t_compute_result	ret;
  int			res;

  do
    {
      if ((ret = dabsic_compute_scope
	   (func, mainnod, dry, root, local, artif, params)) != CR_OK)
	{
	  if (ret == CR_BREAK)
	    return (CR_OK);
	  if (ret == CR_RETURN)
	    return (ret);
	}
      if (func.value.GetInt(&res, root, local, artif, params) == false)
	return (CR_ERROR);
    }
  while (!res);
  return (CR_OK);
}

t_compute_result	dabsic_compute_do(Function		&func,
					  Function		&mainnod,
					  bool			dry,
					  SmallConf		*root,
					  SmallConf		*local,
					  SmallConf		*artif,
					  SmallConf		*params)
{
  t_compute_result	ret;
  int			res;

  do
    {
      if ((ret = dabsic_compute_scope
	   (func, mainnod, dry, root, local, artif, params)) != CR_OK)
	{
	  if (ret == CR_BREAK)
	    return (CR_OK);
	  if (ret == CR_RETURN)
	    return (ret);
	}
      if (func.value.GetInt(&res, root, local, artif, params) == false)
	return (CR_ERROR);
    }
  while (res);
  return (CR_OK);
}

t_compute_result	dabsic_compute_for(Function		&func,
					   Function		&mainnod,
					   bool			dry,
					   SmallConf		*root,
					   SmallConf		*local,
					   SmallConf		*artif,
					   SmallConf		*params)
{
  t_compute_result	ret;
  int			res = 1;

  if (expr_compute(func.value, NULL, dry, root, local, artif, params) == false)
    return (CR_ERROR);

  while (res)
    {
      if (func.additionnal_values[0].GetInt
	  (&res, root, local, artif, params) == false)
	return (CR_ERROR);
      if (res)
	{
	  if ((ret = dabsic_compute_scope
	       (func, mainnod, dry, root, local, artif, params)) != CR_OK)
	    {
	      if (ret == CR_BREAK)
		return (CR_OK);
	      if (ret == CR_RETURN)
		return (ret);
	    }
	  if (expr_compute
	      (func.additionnal_values[1], NULL, dry, root, local, artif, params) == false)
	    return (CR_ERROR);
	}
    }
  return (CR_OK);
}

t_compute_result	dabsic_compute_no_execution(Function	&func,
						    Function	&mainnod,
						    bool	dry,
						    SmallConf	*root,
						    SmallConf	*local,
						    SmallConf	*artif,
						    SmallConf	*params)
{
  (void)func;
  (void)mainnod;
  (void)dry;
  (void)root;
  (void)local;
  (void)artif;
  (void)params;
  return (CR_OK);
}

t_compute_result	dabsic_compute_with(Function		&func,
					    Function		&mainnod,
					    bool		dry,
					    SmallConf		*root,
					    SmallConf		*local,
					    SmallConf		*artif,
					    SmallConf		*params)
{
  SmallConf		*newartif;

  // Should be a complete expression returning an address,
  // but currently, there is no real address type...
  if ((newartif = expr_get_variable
       (func.value, dry, root, local, artif, params)) == NULL)
    scream_error_if
      (return (CR_ERROR), BE_BAD_ADDRESS,
       "Undefined variable or unresolvable address %s "
       "from context %s on line %s:%d",
       "ressource,configuration,syntax",
       func.value.original_value.c_str(),
       artif->address.c_str(),
       func.file.c_str(), func.line);
  return (dabsic_compute_scope(func, mainnod, dry, root, local, newartif, params));
}

t_compute_result	dabsic_compute_print(Function		&func,
					     Function		&mainnod,
					     bool		dry,
					     SmallConf		*root,
					     SmallConf		*local,
					     SmallConf		*artif,
					     SmallConf		*params)
{
  std::ostream		*out;
  size_t		i;

  (void)mainnod;
  if (func.command == Function::PRINT)
    out = &std::cout;
  else
    out = &std::cerr;
  for (i = 0; i < func.value.Size(); ++i)
    {
      SmallConf		&cnf = func.value[i];
      int		a;
      double		b;
      const char	*c;

      if (expr_compute(cnf, NULL, dry, root, local, artif, params) == false)
	return (CR_ERROR);
      if (cnf.last_type == SmallConf::INTEGER)
	{
	  if (cnf.GetInt(&a, root, local, artif, params))
	    *out << a;
	}
      else if (cnf.last_type == SmallConf::DOUBLE)
	{
	  if (cnf.GetDouble(&b, root, local, artif, params))
	    *out << b;
	}
      else if (cnf.last_type == SmallConf::STRING)
	{
	  if (cnf.GetString(&c, root, local, artif, params))
	    *out << c;
	}
    }
  *out << std::endl;
  return (CR_OK);
}

t_compute_result	dabsic_compute_scope(Function		&func,
					     Function		&mainnod,
					     bool		dry,
					     SmallConf		*root,
					     SmallConf		*local,
					     SmallConf		*artif,
					     SmallConf		*params)
{
  //std::stack<SmallConf*> artificial_context;
  t_compute_result	ret;
  size_t		i;

  for (i = 0; i < func.nbr_lines; ++i)
    {
      if ((ret = gl_dabsic_compute[func.lines[i].command]
	   (func.lines[i], mainnod, dry, root, local, artif, params)) != CR_OK)
	return (ret);
    }
  return (CR_OK);
}

// REMOVE PROTOTYPE!

bool			dabsic_compute(SmallConf		&func,
				       SmallConf		*prototype,
				       bool			dry,
				       SmallConf		*root,
				       SmallConf		*artif,
				       SmallConf		*params)
{
  size_t		i;

  if (func.function == NULL)
    scream_error_if
      (return (false), BE_SYNTAX_ERROR,
       "Node %s is not a function on line %d",
       "ressource,configuration,syntax",
       func.name.c_str(), func.line
       );
  if (prototype)
    {
      if (params == NULL)
	scream_error_if
	  (return (false), BE_SYNTAX_ERROR,
	   "Missing parameters for function or expression %s on line %d",
	   "ressource,configuration,syntax",
	   func.name.c_str(), func.line
	   );
      for (i = 0; i < prototype->Size(); ++i)
	{
	  if (params->Access((*prototype)[i].name) == false)
	    {
	      if ((*prototype)[i].have_value)
		(*params)[(*prototype)[i].name] = (*prototype)[i];
	      else
		scream_error_if
		  (return (false), BE_SYNTAX_ERROR,
		   "Missing parameters for function or expression %s on line %d",
		   "ressource,configuration,syntax",
		   func.name.c_str(), func.line
		   );
	    }
	}
    }
  if (dabsic_compute_scope
      (*func.function, *func.function, dry, root,
       &func.function->local_variables, artif, params) == CR_ERROR)
    return (false);
  func = func.function->result;
  return (true);
}

