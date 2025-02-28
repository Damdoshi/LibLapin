// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
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
    &dabsic_compute_link,
    &dabsic_compute_with,
    &dabsic_compute_select,
    &dabsic_compute_build,
    &dabsic_compute_delete
  };

t_compute_result	dabsic_compute_build(Function		&func,
					     Function		&mainnod,
					     bool		dry,
					     SmallConf		*root,
					     SmallConf		*local,
					     SmallConf		*artif,
					     SmallConf		*variables)
{
  const char		*res;
  bool			cmode;

  (void)mainnod;
  if (dry)
    return (CR_OK);
  if (func.lines.size() < 1)
    return (CR_ERROR);
  if (func.additionnal_values[0].GetString(&res, root, local, artif, variables))
    return (CR_ERROR);
  cmode = SmallConf::create_mode;
  SmallConf::create_mode = true;
  t_bunny_configuration	*newnod;

  if (bunny_configuration_getf_node(local, &newnod, "%s", res) == false)
    {
      SmallConf::create_mode = cmode;
      return (CR_ERROR);
    }
  SmallConf::create_mode = cmode;
  if (func.lines.size() == 1)
    return (CR_OK);

  if (func.lines.size() > 2)
    return (CR_ERROR);
  SmallConf::RecursiveAssign(*((SmallConf*)newnod), func.additionnal_values[1]);
  // *((SmallConf*)newnod) = func.additionnal_values[1];
  return (CR_OK);
}

t_compute_result	dabsic_compute_delete(Function		&func,
					      Function		&mainnod,
					      bool		dry,
					      SmallConf		*root,
					      SmallConf		*local,
					      SmallConf		*artif,
					      SmallConf		*variables)
{
  const char		*res;

  (void)mainnod;
  if (dry)
    return (CR_OK);
  if (func.lines.size() != 1)
    return (CR_ERROR);
  if (func.additionnal_values[0].GetString(&res, root, local, artif, variables))
    return (CR_ERROR);
  t_bunny_configuration	*newnod;

  //// Il faudrait peut etre plutot déplacer dans []..Trash le noeud
  // afin de pas segfault si quelqu'un travaille sur un truc avec
  if (bunny_configuration_getf_node(local, &newnod, "%s", res) == false)
    return (CR_OK);
  bunny_delete_configuration(newnod);
  return (CR_OK);
}

t_compute_result	dabsic_compute_select(Function		&func,
					      Function		&mainnod,
					      bool		dry,
					      SmallConf		*root,
					      SmallConf		*local,
					      SmallConf		*artif,
					      SmallConf		*variables)
{
  t_compute_result	ret;
  SmallConf		&loc = *local; // Quelle idée de merde.
  size_t		i;
  int			cmode;
  int			selected;

  if (expr_compute(func.value, dry, root, local, artif, variables) == false)
    return (CR_ERROR);
  cmode = SmallConf::create_mode;
  if (local)
    {
      SmallConf::create_mode = true;
      loc["Is"] = func.value; // Mais quelle idée de merde.
    }

  for (i = 0; i < func.nbr_lines; ++i)
    {
      if (expr_compute
	  (func.lines[i].value, dry, root, local, artif, variables)
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
	    (func.lines[i], mainnod, dry, root, local, artif, variables);
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
					     SmallConf		*variables)
{
  (void)func;
  (void)mainnod;
  (void)dry;
  (void)root;
  (void)local;
  (void)artif;
  (void)variables;
  return (CR_BREAK);
}

t_compute_result	dabsic_compute_continue(Function	&func,
						Function	&mainnod,
						bool		dry,
						SmallConf	*root,
						SmallConf	*local,
						SmallConf	*artif,
						SmallConf	*variables)
{
  (void)func;
  (void)mainnod;
  (void)dry;
  (void)root;
  (void)local;
  (void)artif;
  (void)variables;
  return (CR_CONTINUE);
}

t_compute_result	dabsic_compute_brake(Function		&func,
					     Function		&mainnod,
					     bool		dry,
					     SmallConf		*root,
					     SmallConf		*local,
					     SmallConf		*artif,
					     SmallConf		*variables)
{
  (void)func;
  (void)mainnod;
  (void)dry;
  (void)root;
  (void)local;
  (void)artif;
  (void)variables;
  return (CR_OK);
}

t_compute_result	dabsic_compute_link(Function		&func,
					    Function		&mainnod,
					    bool		dry,
					    SmallConf		*root,
					    SmallConf		*local,
					    SmallConf		*artif,
					    SmallConf		*variables)
{
  if (dry)
    return (CR_OK);
  static t_bunny_value_type lt_to_bvt[4] = { // Last type to Bunny value type
    BVT_INTEGER, BVT_DOUBLE, BVT_STRING, BVT_STRING
  };
  SmallConf		&parameters = (*mainnod.parent_node)[".prototype"];
  t_bunny_prototype	*proto;
  t_bunny_value		retval;
  t_bunny_value		*dyvariables;
  size_t		i;
  size_t		nbvariables;

  (void)func;
  (void)root;
  (void)local;
  (void)artif;

  if (variables)
    nbvariables = variables->NbrChild();
  else
    nbvariables = 0;

  if (mainnod.prototype == NULL)
    {
      if ((mainnod.prototype = (t_bunny_prototype*)bunny_malloc
	   (sizeof(*mainnod.prototype)
	    + sizeof(mainnod.prototype->parameters) * nbvariables)) == NULL)
	return (CR_ERROR);
      proto = mainnod.prototype;
      proto->name = mainnod.parent_node->name.c_str();
      proto->function_ptr = bunny_plugin_get_self_function(proto->name);
      proto->return_value = lt_to_bvt[mainnod.parent_node->last_type];
      proto->nbr_parameters = parameters.Size();
    }
  else
    proto = mainnod.prototype;

  dyvariables = (t_bunny_value*)bunny_alloca(proto->nbr_parameters * sizeof(*dyvariables));
  for (i = 0; i < proto->nbr_parameters; ++i)
    {
      if (variables[i].last_type == SmallConf::STRING)
	proto->parameters[i] = BVT_STRING;
      else if (parameters[i].last_type == SmallConf::INTEGER)
	proto->parameters[i] = BVT_INTEGER;
      else if (parameters[i].last_type == SmallConf::DOUBLE)
	proto->parameters[i] = BVT_DOUBLE;

      switch (proto->parameters[i])
	{
	case BVT_INTEGER:
	  int tmp;
	  (*variables)[parameters.name].GetInt(&tmp);
	  dyvariables[i].integer = tmp;
	  break ;
	case BVT_DOUBLE:
	  (*variables)[parameters.name].GetDouble(&dyvariables[i].real);
	  break ;
	case BVT_STRING:
	  (*variables)[parameters.name].GetString(&dyvariables[i].string);
	  break ;
	default:
	  // No pointer type.
	  break ;
	}
    }
  _real_call(proto, &retval, proto->nbr_parameters, dyvariables);

  switch (mainnod.prototype->return_value)
    {
    case BVT_STRING:
      mainnod.result.SetString(retval.string);
      break ;
    case BVT_DOUBLE:
      mainnod.result.SetDouble(retval.real);
      break ;
    case BVT_INTEGER:
      mainnod.result.SetInt(retval.integer);
      break ;
    default:
      if (mainnod.parent_node->have_value)
	fprintf(stderr, "Return used in a void function\n");
      mainnod.result.SetString("");
    }
  bunny_freea((void*)dyvariables);
  return (CR_RETURN);
}

t_compute_result	dabsic_compute_return(Function		&func,
					      Function		&mainnod,
					      bool		dry,
					      SmallConf		*root,
					      SmallConf		*local,
					      SmallConf		*artif,
					      SmallConf		*variables)
{
  (void)func;
  (void)mainnod;
  (void)dry;
  if (func.value.expression)
    {
      if (expr_compute(func.value, dry, root, local, artif, variables) == false)
	return (CR_ERROR);
    }
  SmallConf::RecursiveAssign(mainnod.result, func.value);
  return (CR_RETURN);
}

t_compute_result	dabsic_compute_instruction(Function	&func,
						   Function	&mainnod,
						   bool		dry,
						   SmallConf	*root,
						   SmallConf	*local,
						   SmallConf	*artif,
						   SmallConf	*variables)
{
  (void)mainnod;
  if (expr_compute(func.value, dry, root, local, artif, variables) == false)
    return (CR_ERROR);
  SmallConf::RecursiveAssign(mainnod.result, func.value);
  return (CR_OK);
}

t_compute_result	dabsic_compute_if(Function		&func,
					  Function		&mainnod,
					  bool			dry,
					  SmallConf		*root,
					  SmallConf		*local,
					  SmallConf		*artif,
					  SmallConf		*variables)
{
  int			res;

  if (func.value.GetInt(&res, root, local, artif, variables) == false)
    return (CR_ERROR);

  if (res)
    return (dabsic_compute_scope(func, mainnod, dry, root, local, artif, variables));
  if (func.nbr_lines == 0)
    return (CR_OK);
  Function		*x = &func.lines[func.nbr_lines - 1];

  if (x->command == Function::ELSE_IF)
    return (dabsic_compute_if(*x, mainnod, dry, root, local, artif, variables));
  if (x->command == Function::ELSE)
    return (dabsic_compute_scope(*x, mainnod, dry, root, local, artif, variables));
  return (CR_OK);
}

t_compute_result	dabsic_compute_while(Function		&func,
					     Function		&mainnod,
					     bool		dry,
					     SmallConf		*root,
					     SmallConf		*local,
					     SmallConf		*artif,
					     SmallConf		*variables)
{
  int			res = 1;
  t_compute_result	ret;

  while (res)
    {
      if (func.value.GetInt(&res, root, local, artif, variables) == false)
	return (CR_ERROR);
      if (res)
	if ((ret = dabsic_compute_scope
	     (func, mainnod, dry, root, local, artif, variables)) != CR_OK)
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
					      SmallConf		*variables)
{
  t_compute_result	ret;
  int			res;

  do
    {
      if ((ret = dabsic_compute_scope
	   (func, mainnod, dry, root, local, artif, variables)) != CR_OK)
	{
	  if (ret == CR_BREAK)
	    return (CR_OK);
	  if (ret == CR_RETURN)
	    return (ret);
	}
      if (func.value.GetInt(&res, root, local, artif, variables) == false)
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
					  SmallConf		*variables)
{
  t_compute_result	ret;
  int			res;

  do
    {
      if ((ret = dabsic_compute_scope
	   (func, mainnod, dry, root, local, artif, variables)) != CR_OK)
	{
	  if (ret == CR_BREAK)
	    return (CR_OK);
	  if (ret == CR_RETURN)
	    return (ret);
	}
      if (func.value.GetInt(&res, root, local, artif, variables) == false)
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
					   SmallConf		*variables)
{
  t_compute_result	ret;
  int			res = 1;

  if (expr_compute(func.value, dry, root, local, artif, variables) == false)
    return (CR_ERROR);

  while (res)
    {
      if (func.additionnal_values[0].GetInt
	  (&res, root, local, artif, variables) == false)
	return (CR_ERROR);
      if (res)
	{
	  if ((ret = dabsic_compute_scope
	       (func, mainnod, dry, root, local, artif, variables)) != CR_OK)
	    {
	      if (ret == CR_BREAK)
		return (CR_OK);
	      if (ret == CR_RETURN)
		return (ret);
	    }
	  if (expr_compute
	      (func.additionnal_values[1], dry, root, local, artif, variables) == false)
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
						    SmallConf	*variables)
{
  (void)func;
  (void)mainnod;
  (void)dry;
  (void)root;
  (void)local;
  (void)artif;
  (void)variables;
  return (CR_OK);
}

t_compute_result	dabsic_compute_with(Function		&func,
					    Function		&mainnod,
					    bool		dry,
					    SmallConf		*root,
					    SmallConf		*local,
					    SmallConf		*artif,
					    SmallConf		*variables)
{
  SmallConf		*newartif;

  // Should be a complete expression returning an address,
  // but currently, there is no real address type...
  if ((newartif = expr_get_variable
       (func.value, dry, root, local, artif, variables)) == NULL)
    scream_error_if
      (return (CR_ERROR), BE_BAD_ADDRESS,
       "Undefined variable or unresolvable address %s "
       "from context %s on line %s:%d",
       "ressource,configuration,syntax",
       func.value.original_value.c_str(),
       artif->address.c_str(),
       func.file.c_str(), func.line);
  return (dabsic_compute_scope(func, mainnod, dry, root, local, newartif, variables));
}

t_compute_result	dabsic_compute_print(Function		&func,
					     Function		&mainnod,
					     bool		dry,
					     SmallConf		*root,
					     SmallConf		*local,
					     SmallConf		*artif,
					     SmallConf		*variables)
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

      if (expr_compute(cnf, dry, root, local, artif, variables) == false)
	return (CR_ERROR);
      if (cnf.last_type == SmallConf::INTEGER)
	*out << cnf.converted_2;
      else if (cnf.last_type == SmallConf::DOUBLE)
	*out << cnf.converted;
      else if (cnf.last_type == SmallConf::STRING)
	*out << cnf.original_value;
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
					     SmallConf		*variables)
{
  //std::stack<SmallConf*> artificial_context;
  t_compute_result	ret;
  size_t		i;

  for (i = 0; i < func.nbr_lines; ++i)
    {
      if ((ret = gl_dabsic_compute[func.lines[i].command]
	   (func.lines[i], mainnod, dry, root, local, artif, variables)) != CR_OK)
	return (ret);
    }
  return (CR_OK);
}

bool	 		dabsic_compute(SmallConf		&func,
				       bool			dry,
				       SmallConf		*root,
				       SmallConf		*artif,
				       SmallConf		*variables)
{
  if (func.function == NULL)
    scream_error_if
      (return (false), BE_SYNTAX_ERROR,
       "Node %s is not a function on line %d",
       "ressource,configuration,syntax",
       func.address.c_str(), func.line
       );

  if ((variables = test_and_set_prototype(func, variables)) == NULL)
    return (false);
  if (dabsic_compute_scope
      (*func.function, *func.function, dry,
       root,
       func.father, // Le contexte de déclaration dla fonction (class, struct, node)
       artif, // Le contexte imposé
       variables) == CR_ERROR) // Les variables locales et paramètres
    {
      func.Remove(variables->name);
      return (false);
    }
  func.Remove(variables->name);
  SmallConf::RecursiveAssign(func, func.function->result);
  return (true);
}

