// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

t_bunny_decision	bunny_color_configuration(const char			*field,
						  t_bunny_color			*col,
						  t_bunny_configuration		*cnf)
{
  t_bunny_configuration	*nod;
  const char		*str;
  char			*end;
  int			tmp;

  if (bunny_configuration_getf_node(cnf, &nod, field) == false)
    return (BD_NOT_FOUND);
  switch (bunny_configuration_get_nbr_case(nod))
    {
    // case 1:
    case 0:
      if (bunny_configuration_getf_string(nod, &str, ".") == false)
	return (BD_ERROR);
      // HTML style color
      if (*str == '#')
	{
	  tmp = strtol(&str[1], &end, 16) | BLACK;
	  if (*end)
	    return (BD_ERROR);
	  col->full = tmp;
	  break ;
	}
      // Single gray level
      if (bunny_configuration_getf_int(nod, &tmp, ".") == false)
	return (BD_ERROR);
      tmp &= 255;
      col->argb[RED_CMP] = col->argb[BLUE_CMP] = col->argb[GREEN_CMP] = tmp;
      col->argb[ALPHA_CMP] = 255;
      break ;

    case 2:
      if (bunny_configuration_getf_int(nod, &tmp, "[0]") == false)
	return (BD_ERROR);
      tmp &= 255;
      col->argb[RED_CMP] = col->argb[BLUE_CMP] = col->argb[GREEN_CMP] = tmp;
      if (bunny_configuration_getf_int(nod, &tmp, "[1]") == false)
	return (BD_ERROR);
      tmp &= 255;
      col->argb[ALPHA_CMP] = tmp;
      break ;

    case 3:
      if (bunny_configuration_getf_int(nod, &tmp, "[0]") == false)
	return (BD_ERROR);
      col->argb[RED_CMP] = tmp & 255;
      if (bunny_configuration_getf_int(nod, &tmp, "[1]") == false)
	return (BD_ERROR);
      col->argb[GREEN_CMP] = tmp & 255;
      if (bunny_configuration_getf_int(nod, &tmp, "[2]") == false)
	return (BD_ERROR);
      col->argb[BLUE_CMP] = tmp & 255;
      col->argb[ALPHA_CMP] = 255;
      break ;

    case 4:
      if (bunny_configuration_getf_int(nod, &tmp, "[0]") == false)
       	return (BD_ERROR);
      col->argb[RED_CMP] = tmp & 255;
      if (bunny_configuration_getf_int(nod, &tmp, "[1]") == false)
	return (BD_ERROR);
      col->argb[GREEN_CMP] = tmp & 255;
      if (bunny_configuration_getf_int(nod, &tmp, "[2]") == false)
	return (BD_ERROR);
      col->argb[BLUE_CMP] = tmp & 255;
      if (bunny_configuration_getf_int(nod, &tmp, "[3]") == false)
	return (BD_ERROR);
      col->argb[ALPHA_CMP] = tmp & 255;
      break ;

    default:
      return (BD_ERROR);
    }
  return (BD_OK);
}

t_bunny_decision	bunny_color_bind_configuration(const char		*field,
						       t_bunny_color		*col,
						       t_bunny_configuration	*cnf)
{
  t_bunny_decision	dec;
  int			i;

  if ((dec = bunny_color_configuration(field, col, cnf)) == BD_ERROR)
    return (dec);
  for (i = 0; i < 4; ++i)
    {
      bunny_configuration_setf_int(cnf, (int)(col->argb[i] & 0xFF), "%s[%d]", field, i);
      bunny_configuration_bindf_char(cnf, (char*)&col->argb[i], "%s[%d]", field, i);
    }
  return (BD_OK);
}
