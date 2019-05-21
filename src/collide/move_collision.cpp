// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include	"lapin_private.h"

void		bunny_move_collision(t_bunny_collision		*a,
				     t_bunny_accurate_position	move)
{
  switch (a->type)
    {
    case BCT_DOT:
      a->dot.coord.x += move.x;
      a->dot.coord.y += move.y;
      break ;
    case BCT_CIRCLE:
      a->circle.coord.x += move.x;
      a->circle.coord.y += move.y;
      break ;
    case BCT_LINE:
      a->line.coord[0].x += move.x;
      a->line.coord[0].y += move.y;
      a->line.coord[1].x += move.x;
      a->line.coord[1].y += move.y;
      break ;
    case BCT_TRIANGLE:
      a->triangle.coord[0].x += move.x;
      a->triangle.coord[0].y += move.y;
      a->triangle.coord[1].x += move.x;
      a->triangle.coord[1].y += move.y;
      a->triangle.coord[2].x += move.x;
      a->triangle.coord[2].y += move.y;
      break ;
    case BCT_RECTANGLE:
      a->rectangular.coord[0].x += move.x;
      a->rectangular.coord[0].y += move.y;
      break ;
    case BCT_QUAD:
      a->quad.coord[0].x += move.x;
      a->quad.coord[0].y += move.y;
      a->quad.coord[1].x += move.x;
      a->quad.coord[1].y += move.y;
      a->quad.coord[2].x += move.x;
      a->quad.coord[2].y += move.y;
      a->quad.coord[3].x += move.x;
      a->quad.coord[3].y += move.y;
      break ;
    case BCT_EQUATION:
      a->equation.coord[0].x += move.x;
      a->equation.coord[0].y += move.y;
      break ;
    default:
      break ;
    }
}
