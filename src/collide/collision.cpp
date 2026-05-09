// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include	"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_collision
 * @doc-kind function
 * @doc-module collide
 * @doc-order 560
 * @doc-since 0
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Tests two collision shapes after applying optional translation and rotation.
 * @param a First shape.
 * @param posa Optional translation applied to a.
 * @param rota Rotation applied to a.
 * @param b Second shape.
 * @param posb Optional translation applied to b.
 * @param rotb Rotation applied to b.
 * @return-success Returns true if the transformed shapes collide.
 * @return-failure Returns false otherwise.
 * @see bunny_collide, bunny_move_collision, bunny_turn_collision
 *
 * @doc-lang fr
 * @brief Teste deux formes de collision après application optionnelle d’une translation et d’une rotation.
 * @param a Première forme.
 * @param posa Translation optionnelle appliquée à a.
 * @param rota Rotation appliquée à a.
 * @param b Seconde forme.
 * @param posb Translation optionnelle appliquée à b.
 * @param rotb Rotation appliquée à b.
 * @return-success Renvoie true si les formes transformées entrent en collision.
 * @return-failure Renvoie false sinon.
 * @see bunny_collide, bunny_move_collision, bunny_turn_collision
 */
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



/**
 * @doc
 * @doc-symbol bunny_collision_nbr
 * @doc-kind function
 * @doc-module collide
 * @doc-order 580
 * @doc-since 0
 * @doc-until latest
 * @doc-level 30
 *
 * @doc-lang en
 * @brief Counts collisions between two arrays of shapes.
 * @param a First array of shapes.
 * @param lena Number of shapes in a.
 * @param posa Optional translation applied to shapes in a.
 * @param rota Rotation applied to shapes in a.
 * @param b Second array of shapes.
 * @param lenb Number of shapes in b.
 * @param posb Optional translation applied to shapes in b.
 * @param rotb Rotation applied to shapes in b.
 * @param couple Optional output array receiving shape names.
 * @param couple_len Capacity of couple.
 * @return-success Returns the number of collisions found or written.
 * @see bunny_collision
 *
 * @doc-lang fr
 * @brief Compte les collisions entre deux tableaux de formes.
 * @param a Premier tableau de formes.
 * @param lena Nombre de formes dans a.
 * @param posa Translation optionnelle appliquée aux formes de a.
 * @param rota Rotation appliquée aux formes de a.
 * @param b Second tableau de formes.
 * @param lenb Nombre de formes dans b.
 * @param posb Translation optionnelle appliquée aux formes de b.
 * @param rotb Rotation appliquée aux formes de b.
 * @param couple Tableau de sortie optionnel recevant les noms des formes.
 * @param couple_len Capacité de couple.
 * @return-success Renvoie le nombre de collisions trouvées ou écrites.
 * @see bunny_collision
 */
int		bunny_collision_nbr(const t_bunny_collision	*a,
				    size_t			lena,
				    const t_bunny_accurate_position *posa,
				    double			rota,

				    const t_bunny_collision	*b,
				    size_t			lenb,
				    const t_bunny_accurate_position *posb,
				    double			rotb,

				    t_bunny_string_couple	*couple,
				    size_t			len)
{
  size_t	i, j, k;

  k = 0;
  for (i = 0; i < lena; ++i)
    for (j = 0; j < lenb; ++j)
      if (bunny_collision(&a[i], posa, rota, &b[j], posb, rotb))
	{
	  if (len == 0)
	    return (1);
	  couple[k].first = a[i].identity.name;
	  couple[k].second = b[j].identity.name;
	  if ((k += 1) >= len)
	    return (k);
	}
  return (k);
}

