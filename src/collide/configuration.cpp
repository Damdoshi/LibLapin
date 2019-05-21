// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

t_bunny_decision	bunny_collision_configuration(const char		*field,
						      t_bunny_collision		*col,
						      t_bunny_configuration	*cnf)
{
  const char		*types[] = {
    "Dot",
    "Circle",
    "Line",
    "Triangle",
    "Rectangle",
    "Quad",
    "Equation"
  };
  t_bunny_temporary_data tmp;
  t_bunny_configuration	*nod;
  int			i, j;

  // Check the node exists
  if (bunny_configuration_getf_node(cnf, &nod, field) == false)
    return (BD_NOT_FOUND);

  // For each node
  for (i = 0; bunny_configuration_getf_node(cnf, &nod, "%s[%d]", field, i); ++i)
    {
      bunny_configuration_getf_string(nod, &tmp.string, "Type");
      for (j = 0; j < NBRCELL(types); ++j)
	if (strcmp(types[j], tmp.string) == 0)
	  break ;
      if (j == NBRCELL(types))
	return (BD_ERROR); //
      switch ((col[i].type = (t_bunny_collision_type)j))
	{
	default:
	case LAST_COLLISION_TYPE:
	  return (BD_ERROR); // Impossible
	case BCT_DOT:
	  bunny_configuration_getf_double(nod, &col[i].dot.coord.x, "Position[0]");
	  bunny_configuration_getf_double(nod, &col[i].dot.coord.y, "Position[1]");
	  break ;
	case BCT_CIRCLE:
	  bunny_configuration_getf_double(nod, &col[i].circle.coord.x, "Position[0]");
	  bunny_configuration_getf_double(nod, &col[i].circle.coord.y, "Position[1]");
	  bunny_configuration_getf_double(nod, &col[i].circle.radius, "Radius");
	  break ;
	case BCT_LINE:
	  bunny_configuration_getf_double(nod, &col[i].line.coord[0].x, "From[0]");
	  bunny_configuration_getf_double(nod, &col[i].line.coord[0].y, "From[1]");
	  bunny_configuration_getf_double(nod, &col[i].line.coord[1].x, "To[0]");
	  bunny_configuration_getf_double(nod, &col[i].line.coord[1].y, "To[1]");
	  break ;
	case BCT_TRIANGLE:
	  bunny_configuration_getf_double(nod, &col[i].triangle.coord[0].x, "Coordinates[0][0]");
	  bunny_configuration_getf_double(nod, &col[i].triangle.coord[0].y, "Coordinates[0][1]");
	  bunny_configuration_getf_double(nod, &col[i].triangle.coord[1].x, "Coordinates[1][0]");
	  bunny_configuration_getf_double(nod, &col[i].triangle.coord[1].y, "Coordinates[1][1]");
	  bunny_configuration_getf_double(nod, &col[i].triangle.coord[2].x, "Coordinates[2][0]");
	  bunny_configuration_getf_double(nod, &col[i].triangle.coord[2].y, "Coordinates[2][1]");
	  break ;
	case BCT_RECTANGLE:
	  bunny_configuration_getf_double(nod, &col[i].rectangular.coord[0].x, "Position[0]");
	  bunny_configuration_getf_double(nod, &col[i].rectangular.coord[0].y, "Position[1]");
	  bunny_configuration_getf_double(nod, &col[i].rectangular.coord[1].x, "Size[0]");
	  bunny_configuration_getf_double(nod, &col[i].rectangular.coord[1].y, "Size[1]");
	  break ;
	case BCT_QUAD:
	  bunny_configuration_getf_double(nod, &col[i].quad.coord[0].x, "Coordinates[0][0]");
	  bunny_configuration_getf_double(nod, &col[i].quad.coord[0].y, "Coordinates[0][1]");
	  bunny_configuration_getf_double(nod, &col[i].quad.coord[1].x, "Coordinates[1][0]");
	  bunny_configuration_getf_double(nod, &col[i].quad.coord[1].y, "Coordinates[1][1]");
	  bunny_configuration_getf_double(nod, &col[i].quad.coord[2].x, "Coordinates[2][0]");
	  bunny_configuration_getf_double(nod, &col[i].quad.coord[2].y, "Coordinates[2][1]");
	  bunny_configuration_getf_double(nod, &col[i].quad.coord[3].x, "Coordinates[3][0]");
	  bunny_configuration_getf_double(nod, &col[i].quad.coord[3].y, "Coordinates[3][1]");
	  break ;
	case BCT_EQUATION:
	  bunny_configuration_getf_double(nod, &col[i].equation.coord[0].x, "Position[0]");
	  bunny_configuration_getf_double(nod, &col[i].equation.coord[0].y, "Position[1]");
	  bunny_configuration_getf_double(nod, &col[i].equation.coord[1].x, "Size[0]");
	  bunny_configuration_getf_double(nod, &col[i].equation.coord[1].y, "Size[1]");
	  bunny_configuration_getf_double(nod, &col[i].equation.a, "A");
	  bunny_configuration_getf_double(nod, &col[i].equation.b, "B");
	  bunny_configuration_getf_double(nod, &col[i].equation.c, "C");
	  bunny_configuration_getf_bool(nod, &col[i].equation.origin_at_center, "OriginAtCenter");
	  bunny_configuration_getf_bool(nod, &col[i].equation.flipx, "FlipX");
	  bunny_configuration_getf_bool(nod, &col[i].equation.flipy, "FlipY");
	  break ;
	}
    }
  return (BD_OK);
}

