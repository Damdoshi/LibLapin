// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

void			restore_expression(std::ostream		&ss,
					   Expression		&expr,
					   bool			complete)
{
  size_t		i, j;

  if ((expr.is_const && complete == false) || expr.optor_family == -1)
    {
      writevalue(ss, expr.val);
      return ;
    }
  if (expr.optor_family == Expression::LAST_OPERATOR_FAMILY)
    {
      ss << expr.val.name;
      ss << "(";
      if (expr.type_cast == Expression::NO_CAST)
	for (j = 0; j < expr.operand.size(); ++j)
	  {
	    if (expr.operand[j] != NULL)
	      {
		if (expr.operand[j]->val.name != "")
		  ss << expr.operand[j]->val.name << " = ";
		restore_expression(ss, *expr.operand[j], true);
	      }
	    if (j + 1 < expr.operand.size())
	      ss << ", ";
	  }
      else
	restore_expression(ss, *expr.operand[0], complete);
      ss << ")";
      return ;
    }
  for (i = 0; i < expr.operand.size(); ++i)
    {
      if (i != 0)
	{
	  ss << " "
	     << Expression::OperatorToken
	    [expr.optor_family][expr.operand[i]->optor][0]
	     << " ";
	}
      if (expr.optor_family > expr.operand[i]->optor_family
	  && expr.operand[i]->optor_family != Expression::LAST_OPERATOR_FAMILY
	  && expr.operand[i]->optor_family != -1)
	{
	  ss << "(";
	  restore_expression(ss, *expr.operand[i], complete);
	  ss << ")";
	}
      else
	restore_expression(ss, *expr.operand[i], complete);
    }
}

char			*_bunny_write_expression_prec(const
						      t_bunny_configuration *cnf)
{
  SmallConf		*config = (SmallConf*)cnf;
  std::stringstream	ss;
  char			*ret;

  if (config->expression == NULL)
    return (NULL);
  restore_expression(ss, *config->expression, false);
  if ((ret = (char*)bunny_malloc(sizeof(*ret) * (ss.str().size() + 1))) == NULL)
    scream_error_if
      (return (NULL), bunny_errno, "%p -> %s", "ressource,configuraton", config, ret);
  strcpy(ret, ss.str().c_str());
  scream_log_if("%p -> %s", "ressource,configuration", config, ret);
  return (ret);
}

char			*_bunny_write_expression(const t_bunny_configuration *cnf)
{
  SmallConf		*config = (SmallConf*)cnf;
  std::stringstream	ss;
  char			*ret;

  if (config->expression == NULL)
    return (NULL);
  restore_expression(ss, *config->expression, true);
  if ((ret = (char*)bunny_malloc(sizeof(*ret) * (ss.str().size() + 1))) == NULL)
    scream_error_if
      (return (NULL), bunny_errno, "%p -> %s", "ressource,configuration", config, ret);
  strcpy(ret, ss.str().c_str());
  scream_log_if("%p -> %s", "ressource,configuration", config, ret);
  return (ret);
}
