// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include	"lapin_private.h"

t_bunny_decision bunny_position_configuration(const char			*field,
					      t_bunny_position			*pos,
					      t_bunny_configuration		*cnf)
{
  t_bunny_configuration *nod;

  if (bunny_configuration_getf_node(cnf, &nod, field) == false)
    return (BD_NOT_FOUND);
  if (bunny_configuration_getf_int(nod, &pos->x, "[0]") == false)
    return (BD_ERROR);
  if (bunny_configuration_getf_int(nod, &pos->y, "[1]") == false)
    return (BD_ERROR);
  return (BD_OK);
}

t_bunny_decision bunny_accurate_position_configuration(const char		*field,
						       t_bunny_accurate_position *pos,
						       t_bunny_configuration	*cnf)
{
  t_bunny_configuration *nod;

  if (bunny_configuration_getf_node(cnf, &nod, field) == false)
    return (BD_NOT_FOUND);
  if (bunny_configuration_getf_double(nod, &pos->x, "[0]") == false)
    return (BD_ERROR);
  if (bunny_configuration_getf_double(nod, &pos->y, "[1]") == false)
    return (BD_ERROR);
  return (BD_OK);
}

