// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include	"lapin_private.h"

t_bunny_decision bunny_position_configuration(const char			*field,
					      t_bunny_position			*pos,
					      t_bunny_configuration		*cnf)
{
  if (bunny_configuration_getf_int(cnf, &pos->x, "%s[0]", field) == false)
    return (BD_ERROR);
  if (bunny_configuration_getf_int(cnf, &pos->y, "%s[1]", field) == false)
    return (BD_ERROR);
  return (BD_OK);
}

t_bunny_decision bunny_position_bind_configuration(const char			*field,
						   t_bunny_position		*pos,
						   t_bunny_configuration	*cnf)
{
  if (bunny_configuration_bindf_int(cnf, &pos->x, "%s[0]", field) == false)
    return (BD_ERROR);
  if (bunny_configuration_bindf_int(cnf, &pos->y, "%s[1]", field) == false)
    return (BD_ERROR);
  return (BD_OK);
}

t_bunny_decision bunny_accurate_position_configuration(const char		*field,
						       t_bunny_accurate_position *pos,
						       t_bunny_configuration	*cnf)
{
  if (bunny_configuration_getf_double(cnf, &pos->x, "%s[0]", field) == false)
    return (BD_ERROR);
  if (bunny_configuration_getf_double(cnf, &pos->y, "%s[1]", field) == false)
    return (BD_ERROR);
  return (BD_OK);
}

t_bunny_decision bunny_accurate_position_bind_configuration(const char		*field,
							    t_bunny_accurate_position *pos,
							    t_bunny_configuration *cnf)
{
  if (bunny_configuration_bindf_double(cnf, &pos->x, "%s[0]", field) == false)
    return (BD_ERROR);
  if (bunny_configuration_bindf_double(cnf, &pos->y, "%s[1]", field) == false)
    return (BD_ERROR);
  return (BD_OK);
}

