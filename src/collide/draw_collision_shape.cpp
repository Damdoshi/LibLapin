/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2018
**
** Bibliotheque Lapin
*/

#include		"lapin_private.h"

static void		draw_dot(t_bunny_buffer					*tar,
				 const t_bunny_accurate_position		*pos,
				 unsigned int					col)
{
  t_bunny_position	line[2];
  unsigned int		c[2];

  c[0] = col;
  c[1] = col;
  line[0].x = pos->x - 10;
  line[0].y = pos->y;
  line[1].x = pos->x + 10;
  line[1].y = pos->y;
  bunny_set_line(tar, &line[0], &c[0]);

  line[0].x = pos->x;
  line[0].y = pos->y - 10;
  line[1].x = pos->x;
  line[1].y = pos->y + 10;
  bunny_set_line(tar, &line[0], &c[0]);
}

static void		draw_circle(t_bunny_buffer				*tar,
				    const t_bunny_accurate_position		*x,
				    double					rad,
				    unsigned int				col)
{
  t_bunny_accurate_position out;
  t_bunny_position	pos;
  t_bunny_position	siz;
  int			i;

  draw_dot(tar, x, col);
  for (i = 0; _get_point_on_circle(x, rad, i, &out); ++i)
    draw_dot(tar, &out, col);

  pos.x = x->x;
  pos.y = x->y;
  siz.x = rad;
  siz.y = rad;
  bunny_set_circle(tar, pos, siz, col);
}

static void		draw_line(t_bunny_buffer				*tar,
				  const t_bunny_accurate_position		*pos,
				  double					ip,
				  unsigned int					col)
{
  t_bunny_accurate_position cof;
  t_bunny_accurate_position tmp;
  t_bunny_position	siz = { 10, 10 };
  t_bunny_position	t[2];
  unsigned int		c[2];
  int			i;

  c[0] = col;
  c[1] = col;
  t[0].x = pos[0].x;
  t[0].y = pos[0].y;
  t[1].x = pos[1].x;
  t[1].y = pos[1].y;
  bunny_set_line(tar, &t[0], &c[0]);
  bunny_set_circle(tar, t[0], siz, c[0]);

  cof.x = (pos[1].x - pos[0].x) / (ip + 1);
  cof.y = (pos[1].y - pos[0].y) / (ip + 1);

  tmp = *pos;
  for (i = 0; i < ip + 2; ++i)
    {
      draw_dot(tar, &tmp, col);
      tmp.x += cof.x;
      tmp.y += cof.y;
    }
}

static void		draw_triangle(t_bunny_buffer				*tar,
				      const t_bunny_accurate_position		*pos,
				      unsigned int				col)
{
  t_bunny_position	tmp[2];
  unsigned int		c[2];

  c[0] = c[1] = col;

  tmp[0].x = pos[0].x;
  tmp[0].y = pos[0].y;
  tmp[1].x = pos[1].x;
  tmp[1].y = pos[1].y;
  bunny_set_line(tar, &tmp[0], &c[0]);

  tmp[0].x = pos[1].x;
  tmp[0].y = pos[1].y;
  tmp[1].x = pos[2].x;
  tmp[1].y = pos[2].y;
  bunny_set_line(tar, &tmp[0], &c[0]);

  tmp[0].x = pos[0].x;
  tmp[0].y = pos[0].y;
  tmp[1].x = pos[2].x;
  tmp[1].y = pos[2].y;
  bunny_set_line(tar, &tmp[0], &c[0]);
}

static void		draw_rectangle(t_bunny_buffer				*tar,
				       const t_bunny_accurate_position		*pos,
				       const t_bunny_accurate_position		*siz,
				       unsigned int				col)
{
  t_bunny_position	tmp[2];
  unsigned int		c[2];

  c[0] = c[1] = col;

  tmp[0].x = pos[0].x;
  tmp[0].y = pos[0].y;
  tmp[1].x = pos[0].x + siz[0].x;
  tmp[1].y = pos[0].y;
  bunny_set_line(tar, &tmp[0], &c[0]);

  tmp[0].x = pos[0].x;
  tmp[0].y = pos[0].y + siz[0].y;
  tmp[1].x = pos[0].x + siz[0].x;
  tmp[1].y = pos[0].y + siz[0].y;
  bunny_set_line(tar, &tmp[0], &c[0]);

  tmp[0].x = pos[0].x;
  tmp[0].y = pos[0].y;
  tmp[1].x = pos[0].x;;
  tmp[1].y = pos[0].y + siz[0].y;
  bunny_set_line(tar, &tmp[0], &c[0]);

  tmp[0].x = pos[0].x + siz[0].x;
  tmp[0].y = pos[0].y;
  tmp[1].x = pos[0].x + siz[0].x;
  tmp[1].y = pos[0].y + siz[0].y;
  bunny_set_line(tar, &tmp[0], &c[0]);
}

static void		draw_quad(t_bunny_buffer				*tar,
				  const t_bunny_accurate_position		*pos,
				  unsigned int					col)
{
  t_bunny_position	tmp[2];
  unsigned int		c[2];

  c[0] = c[1] = col;

  tmp[0].x = pos[0].x;
  tmp[0].y = pos[0].y;
  tmp[1].x = pos[1].x;
  tmp[1].y = pos[1].y;
  bunny_set_line(tar, &tmp[0], &c[0]);

  tmp[0].x = pos[1].x;
  tmp[0].y = pos[1].y;
  tmp[1].x = pos[2].x;
  tmp[1].y = pos[2].y;
  bunny_set_line(tar, &tmp[0], &c[0]);

  tmp[0].x = pos[2].x;
  tmp[0].y = pos[2].y;
  tmp[1].x = pos[3].x;
  tmp[1].y = pos[3].y;
  bunny_set_line(tar, &tmp[0], &c[0]);

  tmp[0].x = pos[0].x;
  tmp[0].y = pos[0].y;
  tmp[1].x = pos[3].x;
  tmp[1].y = pos[3].y;
  bunny_set_line(tar, &tmp[0], &c[0]);
}

static void		draw_equation(t_bunny_buffer				*tar,
				      const t_bunny_equation_collision		*equ,
				      unsigned int				col)
{
  static const unsigned int color[4] = {RED, RED, BLUE, BLUE};
  t_bunny_accurate_area area;
  t_bunny_position	ori[2];
  t_bunny_accurate_position orix;
  int			beg;
  int			end;

  area.x = equ->coord[0].x;
  area.y = equ->coord[0].y;
  area.w = equ->coord[1].x;
  area.h = equ->coord[1].y;
  draw_rectangle(tar, &equ->coord[0], &equ->coord[1], col);

  if (equ->origin_at_center)
    {
      beg = -equ->coord[1].x / 2;
      end = -beg;

      ori[0].x = equ->coord[0].x + equ->coord[1].x / 2;
      ori[0].y = equ->coord[0].y + equ->coord[1].y / 2;

      ori[1].y = ori[0].y;
      if (equ->flipx)
	ori[1].x = ori[0].x - equ->coord[1].x / 4;
      else
	ori[1].x = ori[0].x + equ->coord[1].x / 4;
      bunny_set_line(tar, &ori[0], &color[0]);

      ori[1].x = ori[0].x;
      if (equ->flipy)
	ori[1].y = ori[0].y - equ->coord[1].y / 4;
      else
	ori[1].y = ori[0].y + equ->coord[1].y / 4;
      bunny_set_line(tar, &ori[0], &color[2]);

      orix.x = ori[0].x;
      orix.y = ori[0].y;
      draw_dot(tar, &orix, GREEN);
    }
  else
    {
      beg = 0;
      end = equ->coord[1].x;

      if (equ->flipx)
	{
	  if (equ->flipy)
	    {
	      ori[0].x = equ->coord[0].x + equ->coord[1].x;
	      ori[0].y = equ->coord[0].y + equ->coord[1].x;

	      ori[1].x = ori[0].x - equ->coord[1].x / 4;
	      ori[1].y = ori[0].y;
	      bunny_set_line(tar, &ori[0], &color[0]);

	      ori[1].x = ori[0].x;
	      ori[1].y = ori[1].y - equ->coord[1].y / 4;
	      bunny_set_line(tar, &ori[0], &color[2]);

	      orix.x = ori[0].x;
	      orix.y = ori[0].y;
	      draw_dot(tar, &orix, GREEN);
	    }
	  else
	    {
	      ori[0].x = equ->coord[0].x + equ->coord[1].x;
	      ori[0].y = equ->coord[0].y;

	      ori[1].x = ori[0].x - equ->coord[1].x / 4;
	      ori[1].y = ori[0].y;
	      bunny_set_line(tar, &ori[0], &color[0]);

	      ori[1].x = ori[0].x;
	      ori[1].y = ori[0].y + equ->coord[1].y / 4;
	      bunny_set_line(tar, &ori[0], &color[2]);

	      orix.x = ori[0].x;
	      orix.y = ori[0].y;
	      draw_dot(tar, &orix, GREEN);
	    }
	}
      else
	{
	  if (equ->flipy)
	    {
	      ori[0].x = equ->coord[0].x;
	      ori[0].y = equ->coord[0].y + equ->coord[1].y;

	      ori[1].x = ori[0].x + equ->coord[1].x / 4;
	      ori[1].y = ori[0].y;
	      bunny_set_line(tar, &ori[0], &color[0]);

	      ori[1].x = ori[0].x;
	      ori[1].y = ori[0].y - equ->coord[1].y / 4;
	      bunny_set_line(tar, &ori[0], &color[2]);

	      orix.x = ori[0].x;
	      orix.y = ori[0].y;
	      draw_dot(tar, &orix, GREEN);
	    }
	  else
	    {
	      ori[0].x = equ->coord[0].x;
	      ori[0].y = equ->coord[0].y;

	      ori[1].x = ori[0].x + equ->coord[1].x / 4;
	      ori[1].y = ori[0].y;
	      bunny_set_line(tar, &ori[0], &color[0]);

	      ori[1].x = ori[0].x;
	      ori[1].y = ori[0].y + equ->coord[1].y / 4;
	      bunny_set_line(tar, &ori[0], &color[2]);

	      orix.x = ori[0].x;
	      orix.y = ori[0].y;
	      draw_dot(tar, &orix, GREEN);
	    }
	}
    }

  while (beg != end)
    {
      t_bunny_accurate_position	pos;

      pos.x = (beg / equ->coord[1].x) * equ->amplitude.x;
      pos.y = (pos.x * pos.x * equ->a + pos.x * equ->b + equ->c)
	* (equ->coord[1].y / equ->amplitude.y);

      if (equ->origin_at_center)
	{
	  if (equ->flipx)
	    pos.x = end + equ->coord[0].x - beg;
	  else
	    pos.x = beg + equ->coord[0].x + equ->coord[1].x / 2;
	  if (equ->flipy)
	    pos.y *= -1;
	  pos.y = pos.y + equ->coord[0].y + equ->coord[1].y / 2;
	}
      else
	{
	  if (equ->flipx)
	    pos.x = end + equ->coord[0].x - beg;
	  else
	    pos.x = beg + equ->coord[0].x;
	  if (equ->flipy)
	    {
	      pos.y *= -1;
	      pos.y += equ->coord[0].y + equ->coord[1].y;
	    }
	  else
	    pos.y += equ->coord[0].y;
	}
      if (bunny_rectangular_collision_dot(&area, &pos))
	{
	  t_bunny_position tmp[2];
	  unsigned int cols[2];

	  cols[0] = GRAY(128);
	  cols[1] = ALPHA_GRAY(0, 128);
	  tmp[0].x = pos.x;
	  tmp[0].y = pos.y;
	  tmp[1].x = pos.x;
	  if (equ->flipy)
	    tmp[1].y = equ->coord[0].y;
	  else
	    tmp[1].y = equ->coord[0].y + equ->coord[1].y;
	  bunny_set_line(tar, &tmp[0], &cols[0]);
	}

      if (beg < end)
	beg += 1;
      else
	beg -= 1;
    }
}

void			bunny_draw_collision_shape(t_bunny_buffer		*tar,
						   const t_bunny_collision	*x,
						   unsigned int			col)
{
  switch (x->type)
    {
    case BCT_DOT:
      draw_dot(tar, &x->dot.coord, col);
      break ;
    case BCT_CIRCLE:
      draw_circle(tar, &x->circle.coord, x->circle.radius, col);
      break ;
    case BCT_LINE:
      draw_line(tar, &x->line.coord[0], x->line.intermediate_points, col);
      break ;
    case BCT_TRIANGLE:
      draw_triangle(tar, &x->triangle.coord[0], col);
      break ;
    case BCT_RECTANGLE:
      draw_rectangle(tar, &x->rectangular.coord[0], &x->rectangular.coord[1], col);
      break ;
    case BCT_QUAD:
      draw_quad(tar, &x->quad.coord[0], col);
      break ;
    case BCT_EQUATION:
      draw_equation(tar, &x->equation, col);
      break ;
    default:
      break ;
    }
}

void			bunny_set_collision_shape(t_bunny_buffer		*tar,
						  const t_bunny_collision	*x,
						  t_bunny_position		pos,
						  unsigned int			col)
{
  t_bunny_collision	c = *x;

  bunny_move_collision(&c, t_bunny_accurate_position{(double)pos.x, (double)pos.y});
  bunny_draw_collision_shape(tar, &c, col);
}

