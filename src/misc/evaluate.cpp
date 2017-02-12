// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin Library

#include		"lapin_private.h"

static double		ternary(const char			*operation,
				ssize_t				&i,
				t_bunny_configuration		*env);

static double		operand(const char			*operation,
				ssize_t				&i,
				t_bunny_configuration		*env)
{
  char			*end;
  double		value;

  skipspace(operation, i);
  if (operation[i] == '(')
    {
      skipspace(operation, i);
      value = ternary(operation, i, env);
      skipspace(operation, i);
      if (operation[i] == ')')
	{
	  i += 1;
	  skipspace(operation, i);
	}
      return (value);
    }
  if (isdigit(operation[i]) ||
      ((operation[i] == '+' || operation[i] == '-') && isdigit(operation[i])))
    {
      value = strtod(&operation[i], &end);
      skipspace(operation, i);
      i = end - operation;
      return (value);
    }
  // get variable from env...
  return (-42);
}

static double		test(const char				*operation,
			     ssize_t				&i,
			     t_bunny_configuration		*env)
{
  double		first;

  skipspace(operation, i);
  first = operand(operation, i, env);
  skipspace(operation, i);
  if (strncmp(&operation[i], ">=", 2) == 0)
    return (first >= test(operation, ++i, env));
  if (strncmp(&operation[i], "<=", 2) == 0)
    return (first <= test(operation, ++i, env));
  if (operation[i] == '>')
    return (first > test(operation, ++i, env));
  if (operation[i] == '<')
    return (first < test(operation, ++i, env));
  if (strncmp(&operation[i], "==", 2) == 0)
    return ((int)fabs(first - test(operation, ++i, env)) == 0);
  if (strncmp(&operation[i], "!=", 2) == 0)
    return ((int)fabs(first - test(operation, ++i, env)) != 0);
  return (first);
}

static double		mul_div_mod(const char			*operation,
				    ssize_t			&i,
				    t_bunny_configuration	*env)
{
  double		first;

  skipspace(operation, i);
  first = test(operation, i, env);
  skipspace(operation, i);
  if (operation[i] == '*')
    return (first * mul_div_mod(operation, ++i, env));
  if (operation[i] == '/')
    return (first / mul_div_mod(operation, ++i, env));
  if (operation[i] == '%')
    return ((int)first % (int)mul_div_mod(operation, ++i, env));
  return (first);
}

static double		add_sub(const char			*operation,
				ssize_t				&i,
				t_bunny_configuration		*env)
{
  double		first;

  skipspace(operation, i);
  first = mul_div_mod(operation, i, env);
  skipspace(operation, i);
  if (operation[i] == '+')
    return (first + add_sub(operation, ++i, env));
  if (operation[i] == '-')
    return (first - add_sub(operation, ++i, env));
  return (first);
}

static double		ternary(const char			*operation,
				ssize_t				&i,
				t_bunny_configuration		*env)
{
  double		first, second, third;

  skipspace(operation, i);
  first = add_sub(operation, i, env);
  skipspace(operation, i);
  if (operation[i] == '?')
    {
      skipspace(operation, ++i);
      second = add_sub(operation, i, env);
      skipspace(operation, i);
      if ((int)first != 0)
	return (second);
      if (operation[i] != ':')
	return (0);
      skipspace(operation, ++i);
      third = add_sub(operation, i, env);
      skipspace(operation, i);
      return (third);
    }
  return (first);
}

double			bunny_evaluate(const char		*operation,
				       t_bunny_configuration	*env)
{
  ssize_t		i;

  i = 0;
  return (ternary(operation, i, env));
}

