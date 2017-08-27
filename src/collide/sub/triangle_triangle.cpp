// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include		"lapin_private.h"

bool			bunny_collision_triangle_triangle(const t_bunny_collision *a,
							  const t_bunny_collision *b)
{
  t_bunny_vertex_array	*arr = (t_bunny_vertex_array*)bunny_alloca(sizeof(arr->length) + 3 * sizeof(arr->vertex[0]));
  t_bunny_vertex_array	*brr = (t_bunny_vertex_array*)bunny_alloca(sizeof(brr->length) + 3 * sizeof(brr->vertex[0]));
  const t_bunny_triangle_collision *atri = &a->triangle;
  const t_bunny_triangle_collision *btri = &b->triangle;
  t_bunny_line_collision tmp;
  size_t		i;
  
  tmp.type = BCT_LINE;
  tmp.intermediate_points = 2;

  for (i = 0, arr->length = brr->length = 3; i < arr->length; ++i)
    {
      arr->vertex[i].pos.x = atri->coord[i].x;
      arr->vertex[i].pos.y = atri->coord[i].y;
      brr->vertex[i].pos.x = btri->coord[i].x;
      brr->vertex[i].pos.y = btri->coord[i].y;
    }

  // A triangle, B set of lines
  tmp.coord[0] = btri->coord[0];
  tmp.coord[1] = btri->coord[1];
  if (bunny_collision_triangle_line(a, (t_bunny_collision*)&tmp))
    goto collide;

  tmp.coord[0] = btri->coord[1];
  tmp.coord[1] = btri->coord[2];
  if (bunny_collision_triangle_line(a, (t_bunny_collision*)&tmp))
    goto collide;

  tmp.coord[0] = btri->coord[2];
  tmp.coord[1] = btri->coord[0];
  if (bunny_collision_triangle_line(b, (t_bunny_collision*)&tmp))
    goto collide;

  // B triangle, A set of lines
  tmp.coord[0] = atri->coord[0];
  tmp.coord[1] = atri->coord[1];
  if (bunny_collision_triangle_line(b, (t_bunny_collision*)&tmp))
    goto collide;

  tmp.coord[0] = atri->coord[1];
  tmp.coord[1] = atri->coord[2];
  if (bunny_collision_triangle_line(b, (t_bunny_collision*)&tmp))
    goto collide;

  tmp.coord[0] = atri->coord[2];
  tmp.coord[1] = atri->coord[0];
  if (bunny_collision_triangle_line(b, (t_bunny_collision*)&tmp))
    goto collide;

  // Is B in A?
  if (bunny_triangle_collision_dot(arr, &brr->vertex[0].pos))
    goto collide;
  // Is A in B?
  if (bunny_triangle_collision_dot(brr, &arr->vertex[0].pos))
    goto collide;

  bunny_freea(arr);
  bunny_freea(brr);
  return (false);

 collide:
  bunny_freea(arr);
  bunny_freea(brr);
  return (true);
}
