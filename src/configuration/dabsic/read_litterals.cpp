// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

Decision		dabsic_read_litterals(const char		*code,
					      ssize_t			&i,
					      SmallConf			&conf,
					      SmallConf			&root,
					      bool			shrink)
{

  (void)root;
  if (conf.construct == SmallConf::ARRAY && 0)
    {
      dabsic_read_separator(code, i);
      if (expr_read_expression(code, i, conf, Expression::BEOF_TERNARY) == BD_ERROR)
	return (BD_ERROR);
      dabsic_read_separator(code, i);
    }

  int			iteration = 0;

  if (SmallConf::just_pushed > 0)
    {
      iteration = conf.array.size();
      SmallConf::just_pushed -= 1;
    }
  else
    conf.array.clear();

  do
    {
      dabsic_read_separator(code, i);
      if (expr_read_expression(code, i, conf[iteration++], Expression::BEOF_TERNARY) == BD_ERROR)
	return (BD_ERROR);
      dabsic_read_separator(code, i);
    }
  while (readtext(code, i, ","));
  if (shrink)
    shrink_single_element_array(conf);
  dabsic_read_separator(code, i);
  return (BD_OK);
}

