// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include		"lapin_private.h"

static bool		_bunny_collide(const t_bunny_collision		*a,
				       const t_bunny_collision		*b)
{
  switch (a->type)
    {
    case BCT_DOT:
      switch (b->type)
	{
	case BCT_DOT:
	  return (bunny_collision_dot_dot(a, b));
	case BCT_CIRCLE:
	  return (bunny_collision_circle_dot(b, a));
	case BCT_LINE:
	  return (bunny_collision_line_dot(b, a));
	case BCT_TRIANGLE:
	  return (bunny_collision_triangle_dot(b, a));
	case BCT_RECTANGLE:
	  return (bunny_collision_rectangle_dot(b, a));
	case BCT_QUAD:
	  return (bunny_collision_quad_dot(b, a));
	case BCT_EQUATION:
	  return (bunny_collision_equation_dot(&b->equation, &a->dot).radian >= 0);
	case LAST_COLLISION_TYPE:
	  return (false);
	}
    case BCT_CIRCLE:
      switch (b->type)
	{
	case BCT_DOT:
	  return (bunny_collision_circle_dot(a, b));
	case BCT_CIRCLE:
	  return (bunny_collision_circle_circle(b, a));
	case BCT_LINE:
	  return (bunny_collision_line_circle(b, a));
	case BCT_TRIANGLE:
	  return (bunny_collision_triangle_circle(b, a));
	case BCT_RECTANGLE:
	  return (bunny_collision_rectangle_circle(b, a));
	case BCT_QUAD:
	  return (bunny_collision_quad_circle(b, a));
	case BCT_EQUATION:
	  return (bunny_collision_equation_circle(b, a));
	case LAST_COLLISION_TYPE:
	  return (false);
	}
    case BCT_LINE:
      switch (b->type)
	{
	case BCT_DOT:
	  return (bunny_collision_line_dot(a, b));
	case BCT_CIRCLE:
	  return (bunny_collision_line_circle(a, b));
	case BCT_LINE:
	  return (bunny_collision_line_line(a, b));
	case BCT_TRIANGLE:
	  return (bunny_collision_triangle_line(b, a));
	case BCT_RECTANGLE:
	  return (bunny_collision_rectangle_line(b, a));
	case BCT_QUAD:
	  return (bunny_collision_quad_line(b, a));
	case BCT_EQUATION:
	  return (bunny_collision_equation_line(b, a));
	case LAST_COLLISION_TYPE:
	  return (false);
	}
    case BCT_TRIANGLE:
      switch (b->type)
	{
	case BCT_DOT:
	  return (bunny_collision_triangle_dot(a, b));
	case BCT_CIRCLE:
	  return (bunny_collision_triangle_circle(a, b));
	case BCT_LINE:
	  return (bunny_collision_triangle_line(a, b));
	case BCT_TRIANGLE:
	  return (bunny_collision_triangle_triangle(a, b));
	case BCT_RECTANGLE:
	  return (bunny_collision_rectangle_triangle(b, a));
	case BCT_QUAD:
	  return (bunny_collision_quad_triangle(b, a));
	case BCT_EQUATION:
	  return (bunny_collision_equation_triangle(b, a));
	case LAST_COLLISION_TYPE:
	  return (false);
	}
    case BCT_RECTANGLE:
      switch (b->type)
	{
	case BCT_DOT:
	  return (bunny_collision_rectangle_dot(a, b));
	case BCT_CIRCLE:
	  return (bunny_collision_rectangle_circle(a, b));
	case BCT_LINE:
	  return (bunny_collision_rectangle_line(a, b));
	case BCT_TRIANGLE:
	  return (bunny_collision_rectangle_triangle(a, b));
	case BCT_RECTANGLE:
	  return (bunny_collision_rectangle_rectangle(a, b));
	case BCT_QUAD:
	  return (bunny_collision_quad_rectangle(b, a));
	case BCT_EQUATION:
	  return (bunny_collision_equation_rectangle(b, a));
	case LAST_COLLISION_TYPE:
	  return (false);
	}
    case BCT_QUAD:
      switch (b->type)
	{
	case BCT_DOT:
	  return (bunny_collision_quad_dot(a, b));
	case BCT_CIRCLE:
	  return (bunny_collision_quad_circle(a, b));
	case BCT_LINE:
	  return (bunny_collision_quad_line(a, b));
	case BCT_TRIANGLE:
	  return (bunny_collision_quad_triangle(a, b));
	case BCT_RECTANGLE:
	  return (bunny_collision_quad_rectangle(a, b));
	case BCT_QUAD:
	  return (bunny_collision_quad_quad(a, b));
	case BCT_EQUATION:
	  return (bunny_collision_equation_quad(b, a));
	case LAST_COLLISION_TYPE:
	  return (false);
	}
    case BCT_EQUATION:
      switch (b->type)
	{
	case BCT_DOT:
	  return (bunny_collision_equation_dot(&a->equation, &b->dot).radian >= 0);
	case BCT_CIRCLE:
	  return (bunny_collision_equation_circle(a, b));
	case BCT_LINE:
	  return (bunny_collision_equation_line(a, b));
	case BCT_TRIANGLE:
	  return (bunny_collision_equation_triangle(a, b));
	case BCT_RECTANGLE:
	  return (bunny_collision_equation_rectangle(a, b));
	case BCT_QUAD:
	  return (bunny_collision_equation_quad(a, b));
	case BCT_EQUATION:
	  return (bunny_collision_equation_equation(a, b));
	case LAST_COLLISION_TYPE:
	  return (false);
	}
    case LAST_COLLISION_TYPE:
      return (false);
    }
  return (false);
}

bool		bunny_collide(const t_bunny_collision		*a,
			      const t_bunny_collision		*b)
{
  bool		ret;

  ret = _bunny_collide(a, b);
  scream_log_if("%p a, %p b -> %s", a, b, ret ? "true" : "false");
  return (ret);
}

