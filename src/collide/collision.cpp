// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include	"lapin_private.h"

bool		bunny_collision(const t_bunny_collision		*a,
				const t_bunny_accurate_position	*posa,
				double				rota,

				const t_bunny_collision		*b,
				const t_bunny_accurate_position	*posb,
				double				rotb)
{
  t_bunny_collision abis = *a;
  t_bunny_collision bbis = *b;

  if (fabs(rota) > 0.01)
    bunny_turn_collision(&abis, rota);
  if (posa)
    bunny_move_collision(&abis, *posa);

  if (fabs(rotb) > 0.01)
    bunny_turn_collision(&bbis, rotb);
  if (posb)
    bunny_move_collision(&bbis, *posb);
  return (bunny_collide(&abis, &bbis));
}

bool		bunny_collision_nbr(const t_bunny_collision	*a,
				    size_t			lena,
				    const t_bunny_accurate_position *posa,
				    double			rota,

				    const t_bunny_collision	*b,
				    size_t			lenb,
				    const t_bunny_accurate_position *posb,
				    double			rotb)
{
  size_t	i, j;

  for (i = 0; i < lena; ++i)
    for (j = 0; j < lenb; ++j)
      if (bunny_collision(&a[i], posa, rota, &b[j], posb, rotb))
	return (true);
  return (false);
}

