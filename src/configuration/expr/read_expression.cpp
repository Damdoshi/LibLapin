// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

Decision		expr_read_expression(const char		*code,
					     ssize_t		&i,
					     SmallConf		&conf,
					     int		ope)
{
  if ((conf.expression = expr_read_operator(code, i, ope)) == NULL)
    return (BD_ERROR);
  if (expr_precompute(conf) == false)
    return (BD_ERROR);
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

