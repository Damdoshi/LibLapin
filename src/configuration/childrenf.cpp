// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include	"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_configuration_childrenf
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 640
 * @doc-since 0
 * @doc-until latest
 * @doc-level advanced
 *
 * @doc-lang en
 * @brief Counts named children below a node selected by a formatted address.
 * @param c Configuration tree to inspect.
 * @param pat Printf-like address pattern.
 * @param ... Values consumed by $Spat@.
 * @return-success Returns the number of children, or $C-1@ on error.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Compte les enfants nommés sous un nœud sélectionné par adresse formatée.
 * @param c Configuration tree to inspect.
 * @param pat Printf-like address pattern.
 * @param ... Values consumed by $Spat@.
 * @return-success Renvoie le nombre d’enfants, ou $C-1@ en cas d’erreur.
 * @log "configuration"
 */
ssize_t		bunny_configuration_childrenf(const t_bunny_configuration	*cnf,
					      const char			*pat,
					      ...)
{
  t_bunny_configuration *got;
  char		buffer[1024 * 4];
  va_list	lst;
  bool		cmode;

  cmode = SmallConf::create_mode;
  SmallConf::create_mode = false;

  va_start(lst, pat);
  vsnprintf(&buffer[0], sizeof(buffer), pat, lst);
  if ((got = bunny_configuration_go_get_node((t_bunny_configuration*)cnf, &buffer[0])) == NULL)
    {
      SmallConf::create_mode = cmode;
      return (-1);
    }
  SmallConf::create_mode = cmode;
  return (bunny_configuration_get_nbr_child(got));
}

