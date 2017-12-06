// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

void			restore_expression(std::stringstream		&ss,
					   Expression			&expr,
					   bool				complete)
{
  size_t		i;

  if (expr.val.have_value && expr.operand.size() == 0)
    writevalue(ss, expr.val);
  for (i = 0; i < expr.operand.size(); ++i)
    {
      if (i != 0)
	{
	  ss << " "
	     << Expression::OperatorToken
	    [expr.optor_family][expr.operand[i]->optor][0]
	     << " ";
	}
      if (expr.operand[i]->val.have_value
	  && (expr.operand[i]->operand.size() == 0
	      || complete == false
	      )
	  )
	writevalue(ss, expr.operand[i]->val);
      else if (expr.optor_family > expr.operand[i]->optor_family)
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
