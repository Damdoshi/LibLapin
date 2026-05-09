// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"


/**
 * @doc
 * @doc-symbol bunny_perror
 * @doc-kind function
 * @doc-module error
 * @doc-order 160
 * @doc-since 0
 * @doc-until latest
 * @doc-level 20
 *
 * @doc-lang en
 * @brief Prints a prefix and the current bunny_errno description on stderr.
 * @param str Optional prefix. NULL or an empty string prints only the error description.
 * @see bunny_errno, bunny_strerror
 *
 * @doc-lang fr
 * @brief Affiche un préfixe et la description de bunny_errno sur stderr.
 * @param str Préfixe optionnel. NULL ou une chaîne vide affiche seulement la description de l’erreur.
 * @see bunny_errno, bunny_strerror
 */
void			bunny_perror(const char		*str)
{
  if (!str || !*str)
    fprintf(stderr, "%s\n", bunny_strerror(bunny_errno));
  else
    fprintf(stderr, "%s: %s\n", str, bunny_strerror(bunny_errno));
}

