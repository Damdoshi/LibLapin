// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

static bool		expr_operator_follows(const char	*code,
				      ssize_t		i,
				      int		ope)
{
  int			optor;
  int			family;

  // Cas dominants des fichiers de donnees: la valeur est immediatement
  // terminee par la ligne, une virgule, un delimiteur fermant ou la fin.
  if (code[i] == '\0' || code[i] == '\n' || code[i] == '\r'
      || code[i] == ',' || code[i] == ')' || code[i] == ']'
      || code[i] == '}')
    return (false);

  family = expr_get_operator_priority(code, i, optor, true, ope);
  return (family >= ope && family < Expression::LAST_OPERATOR_FAMILY);
}

Decision		expr_read_expression(const char		*code,
					     ssize_t		&i,
					     SmallConf		&conf,
					     int		ope)
{
  ssize_t		start;

  delete conf.expression;
  conf.expression = NULL;

  // Une expression commence toujours par une operande. La lire d'abord permet
  // d'eviter toute la cascade de priorites lorsque cette operande est deja
  // suivie d'un terminateur. Si un operateur suit, on revient au parseur
  // complet sans changer sa semantique.
  start = i;
  if ((conf.expression = expr_read_operand(code, i)) == NULL)
    return (BD_ERROR);
  if (expr_operator_follows(code, i, ope))
    {
      delete conf.expression;
      conf.expression = NULL;
      i = start;
      if ((conf.expression = expr_read_operator(code, i, ope)) == NULL)
	return (BD_ERROR);
    }
  if (expr_precompute(conf) == false)
    {
      delete conf.expression;
      conf.expression = NULL;
      return (BD_ERROR);
    }
  if (conf.expression->is_const)
    conf = conf.expression->val;
  return (BD_OK);
}

t_bunny_configuration	*_bunny_read_expression(const char	*code,
						t_bunny_configuration *config)
{
  SmallConf		*conf = (SmallConf*)config;
  ssize_t		i;
  bool			cmode = SmallConf::create_mode;

  i = 0;
  SmallConf::create_mode = true;
  conf->construct = SmallConf::MAP;
  if (expr_read_expression(code, i, *conf, Expression::BEOF_ASSIGNATION) != BD_OK)
    {
      SmallConf::create_mode = cmode;
      return (NULL);
    }
  SmallConf::create_mode = cmode;
  scream_log_if
    ("%s code, %p config -> %p", "ressource,configuration", code, config, config);
  return (config);
}

