// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		<iostream>
#include		<string.h>
#include		"lapin_private.h"

static int		get_operator_priority(const char	*code,
					      ssize_t		&index,
					      int		&optor,
					      bool		check,
					      int		exp)
{
  int			family;
  size_t		longest;
  int			format;
  int			i, j, k;

  family = -1;
  longest = 0;
  for (i = 0; i < NBRCELL
	 (Expression::OperatorToken);
       ++i)
    for (j = 0; j < NBRCELL
	   (Expression::OperatorToken[i]);
	 ++j)
      for (k = 0; k < NBRCELL
	     (Expression::OperatorToken[i][j])
	     && Expression::OperatorToken[i][j][k] != "";
	   ++k)
	{
	  if (strncmp
	      (Expression::OperatorToken[i][j][k].c_str(),
	       &code[index],
	       Expression::OperatorToken[i][j][k].size())
	      == 0
	      && Expression::OperatorToken[i][j][k].size() > longest)
	    {
	      longest = Expression::OperatorToken[i][j][k].size();
	      family = i;
	      optor = j;
	      format = k;
	    }
	}
  if (check == false && family != -1 && family == exp)
    readtext(code, index, Expression::OperatorToken[family][optor][format].c_str());
  return (family);
}

Expression		*expr_read_operator(const char	*code,
					    ssize_t	&i,
					    size_t	ope)
{
  Expression		*current;
  Expression		*son;
  int			optor;

  if (ope == Expression::LAST_OPERATOR_FAMILY)
    return (expr_read_operand(code, i));

  expr_read_separator(code, i);

  if ((son = expr_read_operator(code, i, ope + 1)) == NULL)
    return (NULL);

  expr_read_separator(code, i);

  if (get_operator_priority(code, i, optor, true, ope) != (int)ope)
    return (son);

  current = new Expression;
  current->line = whichline(code, i);
  current->optor_family = ope;
  current->operand.push_back(son);
  while (get_operator_priority(code, i, optor, false, ope) == (int)ope)
    {
      expr_read_separator(code, i);
      if ((son = expr_read_operator(code, i, ope + 1)) == NULL)
	{
	  delete current;
	  return (NULL);
	}
      expr_read_separator(code, i);
      son->optor = optor;
      current->operand.push_back(son);
    }

  expr_precompute(*current);
  return (current);
}

