// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include	"lapin_private.h"

static void	turn(t_bunny_accurate_position			*p,
		     double					m)
{
  t_bunny_accurate_position n;
  double	angle = M_PI * m / 180.0;

  n.x = p->x * cos(angle) - p->y * sin(angle);
  n.y = p->x * sin(angle) + p->y * cos(angle);
  p->x = n.x;
  p->y = n.y;
}

void		bunny_turn_collision(t_bunny_collision		*a,
				     double			moment)
{
  switch (a->type)
    {
    case BCT_DOT:
      turn(&a->dot.coord, moment);
      break ;
    case BCT_CIRCLE:
      turn(&a->circle.coord, moment);
      break ;
    case BCT_LINE:
      turn(&a->line.coord[0], moment);
      turn(&a->line.coord[1], moment);
      break ;
    case BCT_TRIANGLE:
      turn(&a->triangle.coord[0], moment);
      turn(&a->triangle.coord[1], moment);
      turn(&a->triangle.coord[2], moment);
      break ;
    case BCT_RECTANGLE:
      {
	t_bunny_accurate_position siz = {
	  a->rectangular.coord[1].y,
	  a->rectangular.coord[1].y
	};

	a->type = BCT_QUAD;
	a->quad.coord[1].x = a->quad.coord[0].x + siz.x;
	a->quad.coord[1].y = a->quad.coord[0].y;
	a->quad.coord[2].x = a->quad.coord[0].x + siz.x;
	a->quad.coord[2].y = a->quad.coord[0].y + siz.y;
	a->quad.coord[3].x = a->quad.coord[0].x;
	a->quad.coord[3].y = a->quad.coord[0].y + siz.y;
      }
      [[fallthrought]];
    case BCT_QUAD:
      turn(&a->quad.coord[0], moment);
      turn(&a->quad.coord[1], moment);
      turn(&a->quad.coord[2], moment);
      turn(&a->quad.coord[3], moment);
      break ;
    case BCT_EQUATION:
      puts((std::string("Unsupported turn equation in ") +
	    std::string(__PRETTY_FUNCTION__)).c_str());
      break ;
    default:
      break ;
    }
}
