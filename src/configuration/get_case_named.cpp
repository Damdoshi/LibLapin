// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include	"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_configuration_get_case_named
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 655
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Searches an indexed array for a case whose name matches a formatted string.
 * @param cnf Configuration node to inspect.
 * @param out Output node pointer.
 * @param pat Printf-like name pattern.
 * @param ... Values consumed by $Spat@.
 * @return-success Returns $Ctrue@ and stores the matching case.
 * @return-failure Returns $Cfalse@ when no case matches.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Recherche dans un tableau indexé une case dont le nom correspond à une chaîne formatée.
 * @param cnf Configuration node to inspect.
 * @param out Output node pointer.
 * @param pat Printf-like name pattern.
 * @param ... Values consumed by $Spat@.
 * @return-success Renvoie $Ctrue@ et stocke la case correspondante.
 * @return-failure Renvoie $Cfalse@ si aucune case ne correspond.
 * @log "configuration"
 */
bool		bunny_configuration_get_case_named(t_bunny_configuration	*cnf,
						   t_bunny_configuration	**data,
						   const char			*pat,
						   ...)
{
  t_bunny_configuration *nod;
  char		buffer[1024 * 4];
  va_list	lst;

  va_start(lst, pat);
  vsnprintf(&buffer[0], sizeof(buffer), pat, lst);

  for (int i = 0; bunny_configuration_getf_node(cnf, &nod, "[%d]", i); ++i)
    if (!strcmp(bunny_configuration_get_name(nod), &buffer[0]))
      {
	if (data)
	  *data = nod;
	return (true);
      }
  return (false);
}

