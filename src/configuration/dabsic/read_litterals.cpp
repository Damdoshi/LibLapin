// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

Decision		dabsic_read_litterals(const char		*code,
					      ssize_t			&i,
					      SmallConf			&conf,
					      SmallConf			&root)
{

  (void)root;
  if (conf.construct == SmallConf::ARRAY)
    {
      dabsic_read_separator(code, i);
      if (expr_read_expression(code, i, conf, Expression::BEOF_TERNARY) == BD_ERROR)
	return (BD_ERROR);
      dabsic_read_separator(code, i);
    }
  do
    {
      dabsic_read_separator(code, i);
      if (expr_read_expression(code, i, conf[conf.Size()], Expression::BEOF_TERNARY) == BD_ERROR)
	return (BD_ERROR);
      dabsic_read_separator(code, i);
    }
  while (readtext(code, i, ","));
  shrink_single_element_array(conf);
  dabsic_read_separator(code, i);
  return (BD_OK);
}

