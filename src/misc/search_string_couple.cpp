// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2016
//
// Lapin library

#include		"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_search_string_couple
 * @doc-kind function
 * @doc-module misc
 * @doc-order 40
 * @doc-since 12
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Searches a string couple in an array.
 * @param couple Array to browse.
 * @param len Number of elements in couple.
 * @param a First string to match.
 * @param b Second string to match.
 * @return-success Returns a pointer to the matching couple.
 * @return-failure Returns NULL if no matching couple is found.
 * @see t_bunny_string_couple, gl_empty_string_couple
 *
 * @doc-lang fr
 * @brief Recherche un couple de chaînes dans un tableau.
 * @param couple Tableau à parcourir.
 * @param len Nombre d'éléments dans couple.
 * @param a Première chaîne à comparer.
 * @param b Seconde chaîne à comparer.
 * @return-success Renvoie un pointeur vers le couple correspondant.
 * @return-failure Renvoie NULL si aucun couple ne correspond.
 * @see t_bunny_string_couple, gl_empty_string_couple
 */
t_bunny_string_couple	*bunny_search_string_couple(t_bunny_string_couple	*couple,
						    size_t			len,
						    const char			*a,
						    const char			*b)
{
  size_t		i;

  for (i = 0; i < len; ++i)
    if (strcmp(couple[i].first, a) == 0 && strcmp(couple[i].second, b) == 0)
      return (&couple[i]);
  return (NULL);
}

