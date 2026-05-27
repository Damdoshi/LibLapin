// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_stick
 * @doc-kind function
 * @doc-module misc
 * @doc-order 245
 * @doc-since 12
 * @doc-until latest
 * @doc-level beginner
 *
 * @doc-lang en
 * @brief Joins a NULL-terminated array of strings with a separator.
 * @param tab Strings to join.
 * @param glue Separator inserted between strings.
 * @param no_last If true, the last array entry is ignored.
 * @return-success Returns a newly allocated joined string.
 * @return-failure Returns NULL on allocation failure.
 * @see bunny_split
 *
 * @doc-lang fr
 * @brief Joint un tableau de chaînes terminé par NULL avec un séparateur.
 * @param tab Chaînes à joindre.
 * @param glue Séparateur inséré entre les chaînes.
 * @param no_last Si true, la dernière entrée du tableau est ignorée.
 * @return-success Renvoie une chaîne jointe nouvellement allouée.
 * @return-failure Renvoie NULL en cas d'échec d'allocation.
 * @see bunny_split
 */
char			*bunny_stick(const char * const		*tab,
				     const char			*glue,
				     bool			no_last)
{
  char			*data;
  size_t		len;
  size_t		wt;
  size_t		i;

  for (i = 0, len = 0; tab[i]; ++i)
    len += strlen(tab[i]);
  len += strlen(glue) * (i - no_last ? 1 : 0) + 1;
  if ((data = (char*)bunny_malloc(sizeof(*data) * len)) == NULL)
    return (NULL);
  for (i = 0, wt = 0; tab[i]; ++i)
    {
      wt += snprintf(&data[wt], len, "%s", tab[i]);
      if (tab[i + 1] != NULL || no_last == false)
	wt += snprintf(&data[wt], len, "%s", glue);
    }
  return (data);
}

