// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include	"lapin_private.h"

bool		bunny_collision(const t_bunny_collision		*a,
				const t_bunny_accurate_position	*posa,
				const t_bunny_collision		*b,
				const t_bunny_accurate_position	*posb)
{
  t_bunny_collision abis = *a;
  t_bunny_collision bbis = *b;

  if (posa)
    bunny_move_collision(&abis, *posa);
  if (posb)
    bunny_move_collision(&bbis, *posb);
  return (bunny_collide(&abis, &bbis));
}

bool		bunny_collision_nbr(const t_bunny_collision	*a,
				    const t_bunny_accurate_position *posa,
				    size_t			lena,
				    const t_bunny_collision	*b,
				    const t_bunny_accurate_position *posb,
				    size_t			lenb)
{
  size_t	i, j;

  for (i = 0; i < lena; ++i)
    for (j = 0; j < lenb; ++j)
      if (bunny_collision(&a[i], posa, &b[j], posb))
	return (true);
  return (false);
}

