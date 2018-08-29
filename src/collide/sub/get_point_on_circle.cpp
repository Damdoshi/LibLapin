// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		<math.h>
#include		"lapin_private.h"

bool			_get_point_on_circle(const t_bunny_accurate_position *crd,
					     double		radius,
					     int		nbr,
					     t_bunny_accurate_position *out)
{
  static t_bunny_accurate_position pos[9];
  double		t;
  int			i;

  if (nbr >= 9)
    return (false);
  if (pos[0].x < 0.01)
    {
      for (i = 0, t = 0; i < 8; i += 1, t += M_PI / 4)
	{
	  pos[i].x = cos(t);
	  pos[i].y = sin(t);
	}
      pos[i].x = 0;
      pos[i].y = 0;
    }
  out->x = crd->x + pos[nbr].x * radius;
  out->y = crd->y + pos[nbr].y * radius;
  return (true);
}
