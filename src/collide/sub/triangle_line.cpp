// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include		"lapin_private.h"

bool			bunny_collision_triangle_line(const t_bunny_collision	*a,
						      const t_bunny_collision	*b)
{
  t_bunny_vertex_array	*arr = (t_bunny_vertex_array*)bunny_alloca(sizeof(arr->length) + 3 * sizeof(arr->vertex[0]));
  const t_bunny_triangle_collision *triangle = &a->triangle;
  const t_bunny_line_collision *line = &b->line;
  t_bunny_accurate_position quant;
  t_bunny_accurate_position tmp;
  size_t		i;

  for (i = 0, arr->length = 3; i < arr->length; ++i)
    {
      arr->vertex[i].pos.x = triangle->coord[i].x;
      arr->vertex[i].pos.y = triangle->coord[i].y;
    }
  quant.x = (line->coord[1].x - line->coord[0].x) / (line->intermediate_points + 1);
  quant.y = (line->coord[1].y - line->coord[0].y) / (line->intermediate_points + 1);
  for (i = 0; i < line->intermediate_points + 2; ++i)
    {
      tmp.x = i * quant.x + line->coord[0].x;
      tmp.y = i * quant.y + line->coord[0].y;
      if (bunny_triangle_collision_dot(arr, &tmp))
	{
	  bunny_freea(arr);
	  return (true);
	}
    }
  bunny_freea(arr);
  return (false);
}

