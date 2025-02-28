// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		<string.h>
#include		"lapin_private.h"

Decision		dabsic_read_inside_array(const char		*code,
						 ssize_t		&i,
						 SmallConf		&conf,
						 SmallConf		&root)
{
  Decision		ret;
  int			iteration;

  dabsic_read_separator(code, i);
  if (readtext(code, i, "="))
    {
      dabsic_read_separator(code, i);
      if (expr_read_expression(code, i, conf, Expression::BEOF_TERNARY) == BD_ERROR)
	return (BD_ERROR);
      dabsic_read_separator(code, i);
    }
  dabsic_read_separator(code, i);
  if (code[i] == '}' || code[i] == ']')
    return (BD_OK);

  // Exploitation de la taille afin de s'adapter aux éventuels @push
  // SAUF QUE CA PETE TOUT QUAND ON EST PAS DANS UN PUSH
  // Donc, on reserve ca aux cas ou on push
  if (SmallConf::just_pushed > 0)
    {
      iteration = conf.array.size();
      SmallConf::just_pushed -= 1;
    }
  else
    {
      conf.array.clear();
      iteration = 0;
    }

  conf.construct = SmallConf::ARRAY;
  do
    {
      SmallConf		&newconf = conf[iteration++];

      dabsic_read_separator(code, i);
      if ((ret = dabsic_read_sequence(code, i, newconf, root)) == BD_ERROR)
	return (BD_ERROR);
      if (ret == BD_OK)
       	goto Bottom;

      if ((ret = dabsic_read_function(code, i, newconf, root)) == BD_ERROR)
	return (BD_ERROR);
      if (ret == BD_OK)
	goto Bottom;

      if ((ret = dabsic_read_xml(code, i, newconf, root)) == BD_ERROR)
	return (BD_ERROR);
      if (ret == BD_OK)
	goto Bottom;

      if ((ret = dabsic_read_csv(code, i, newconf, root)) == BD_ERROR)
	return (BD_ERROR);
      if (ret == BD_OK)
	goto Bottom;

      if ((ret = dabsic_read_array(code, i, newconf, root)) == BD_ERROR)
	return (BD_ERROR);
      if (ret == BD_OK)
	goto Bottom;

      if ((ret = dabsic_read_scope(code, i, newconf, root)) == BD_ERROR)
	return (BD_ERROR);
      if (ret == BD_OK)
	goto Bottom;

      if (code[i] == '@')
	{
	  if ((ret = _bunny_handle_directive
	       (code, i, &newconf, &root, dabsic_read_separator,
		Expression::BEOF_TERNARY)) == BD_OK)
	    {
	      dabsic_read_separator(code, i);
	      goto Bottom;
	    }
	  else if (ret == BD_ERROR)
	    return (ret);
	}

      if (expr_read_expression
	  (code, i, newconf, Expression::BEOF_TERNARY) == BD_ERROR)
	return (BD_ERROR);

    Bottom:
      dabsic_read_separator(code, i);
    }
  while (readtext(code, i, ","));
  dabsic_read_separator(code, i);
  if (conf.Access(".prototype"))
    if (dabsic_functionize(conf, conf) == false)
      return (BD_ERROR);
  return (BD_OK);
}

