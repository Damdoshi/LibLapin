// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin Library

#include		"lapin_private.h"

#define			PATTERN		"%s operation, %p environment -> %f"

static double		ternary(const char			*operation,
				ssize_t				&i,
				t_bunny_configuration		*env,
				bool				&bad);

static double		operand(const char			*operation,
				ssize_t				&i,
				t_bunny_configuration		*env,
				bool				&bad)
{
  t_bunny_configuration	*cnf;
  char			*end;
  double		value;

  skipspace(operation, i);
  if (readtext(operation, i, "("))
    {
      skipspace(operation, i);
      value = ternary(operation, i, env, bad);
      if (bad)
	return (nan(""));
      skipspace(operation, i);
      if (operation[i] == ')')
	{
	  i += 1;
	  skipspace(operation, i);
	  return (value);
	}
      bad = true;
      scream_error_if
	(return (nan("")), BE_SYNTAX_ERROR, PATTERN " (Token ')' was expected)",
	 "misc", operation, env, nan(""));
    }
  if (isdigit(operation[i]) ||
      ((operation[i] == '+' || operation[i] == '-') && isdigit(operation[i])))
    {
      value = strtod(&operation[i], &end);
      skipspace(operation, i);
      i = end - operation;
      return (value);
    }

  // Get variable
  if ((cnf = bunny_configuration_resolve_address(&env, 1, operation, i)) == NULL)
    {
      bad = true;
      scream_error_if
	(return (nan("")), BE_SYNTAX_ERROR,
	 PATTERN " (Variable %10s... not found)",
	 "misc", operation, env, nan(""), &operation[i]);
    }
  if (bunny_configuration_get_double(cnf, &value) == false)
    {
      bad = true;
      scream_error_if
	(return (nan("")), BE_SYNTAX_ERROR,
	 PATTERN " (Variable %10s is not a number)",
	 "misc", operation, env, nan(""), &operation[i]);
    }
  return (value);
}

static double		test(const char				*operation,
			     ssize_t				&i,
			     t_bunny_configuration		*env,
			     bool				&bad)
{
  double		first;

  skipspace(operation, i);
  first = operand(operation, i, env, bad);
  if (bad)
    return (nan(""));
  skipspace(operation, i);
  if (strncmp(&operation[i], ">=", 2) == 0)
    return (first >= test(operation, ++i, env, bad));
  if (strncmp(&operation[i], "<=", 2) == 0)
    return (first <= test(operation, ++i, env, bad));
  if (operation[i] == '>')
    return (first > test(operation, ++i, env, bad));
  if (operation[i] == '<')
    return (first < test(operation, ++i, env, bad));
  if (strncmp(&operation[i], "==", 2) == 0)
    return ((int)fabs(first - test(operation, ++i, env, bad)) == 0);
  if (strncmp(&operation[i], "!=", 2) == 0)
    return ((int)fabs(first - test(operation, ++i, env, bad)) != 0);
  return (first);
}

static double		mul_div_mod(const char			*operation,
				    ssize_t			&i,
				    t_bunny_configuration	*env,
				    bool			&bad)
{
  double		first;

  skipspace(operation, i);
  first = test(operation, i, env, bad);
  skipspace(operation, i);
  if (operation[i] == '*')
    return (first * mul_div_mod(operation, ++i, env, bad));
  if (operation[i] == '/')
    return (first / mul_div_mod(operation, ++i, env, bad));
  if (operation[i] == '%')
    return ((int)first % (int)mul_div_mod(operation, ++i, env, bad));
  return (first);
}

static double		add_sub(const char			*operation,
				ssize_t				&i,
				t_bunny_configuration		*env,
				bool				&bad)
{
  double		first;

  skipspace(operation, i);
  first = mul_div_mod(operation, i, env, bad);
  skipspace(operation, i);
  if (operation[i] == '+')
    return (first + add_sub(operation, ++i, env, bad));
  if (operation[i] == '-')
    return (first - add_sub(operation, ++i, env, bad));
  return (first);
}

static double		ternary(const char			*operation,
				ssize_t				&i,
				t_bunny_configuration		*env,
				bool				&bad)
{
  double		first, second, third;

  skipspace(operation, i);
  first = add_sub(operation, i, env, bad);
  if (bad)
    return (nan(""));
  skipspace(operation, i);
  if (operation[i] == '?')
    {
      skipspace(operation, ++i);
      second = add_sub(operation, i, env, bad);
      if (bad)
	return (nan(""));
      skipspace(operation, i);
      if (operation[i] != ':')
	{
	  bad = true;
	  scream_error_if(return (nan("")), BE_SYNTAX_ERROR,
			  PATTERN " (Token ':' was expected in ternary)",
			  "misc", operation, env, nan(""));
	}
      if ((int)first != 0)
	return (second);
      skipspace(operation, ++i);
      third = add_sub(operation, i, env, bad);
      if (bad)
	return (nan(""));
      skipspace(operation, i);
      return (third);
    }
  return (first);
}

double			bunny_evaluate(const char		*operation,
				       t_bunny_configuration	*env)
{
  ssize_t		i;
  double		res;
  bool			bad;

  i = 0;
  bad = false;
  res = (ternary(operation, i, env, bad));
  if (bad)
    scream_error_if
      (return (nan("")), BE_SYNTAX_ERROR, PATTERN, "misc", operation, env, nan(""));

  skipspace(operation, i);
  if (operation[i] != '\0')
    scream_error_if
      (return (nan("")), BE_SYNTAX_ERROR, PATTERN " (End of string not reached)",
       "misc", operation, env, nan(""));
  scream_log_if(PATTERN, "misc", operation, env, res);
  return (res);
}

