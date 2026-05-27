// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include	"lapin_private.h"

/**
 * @doc
 * @doc-symbol bunny_configuration_linkf
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 810
 * @doc-since 0
 * @doc-until latest
 * @doc-level expert
 *
 * @doc-lang en
 * @brief Creates a formatted link from a configuration node to another part of the tree.
 * @param c Configuration tree to modify.
 * @param fmt Printf-like address pattern.
 * @param ... Values consumed by $Sfmt@.
 * @return-success Returns $Ctrue@ on success.
 * @return-failure Returns $Cfalse@ on error.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Crée un lien formaté depuis un nœud de configuration vers une autre partie de l’arbre.
 * @param c Configuration tree to modify.
 * @param fmt Printf-like address pattern.
 * @param ... Values consumed by $Sfmt@.
 * @return-success Renvoie $Ctrue@ en cas de succès.
 * @return-failure Renvoie $Cfalse@ en cas d’erreur.
 * @log "configuration"
 */
bool		bunny_configuration_linkf(t_bunny_configuration	*cnf,
					  const char		*pat,
					  ...)
{
  char		buffer[1024 * 4];
  t_bunny_configuration *got;
  va_list	lst;
  bool		cmode;

  cmode = SmallConf::create_mode;
  SmallConf::create_mode = true;

  va_start(lst, pat);
  vsnprintf(&buffer[0], sizeof(buffer), pat, lst);
  if ((got = bunny_configuration_go_get_node(cnf, &buffer[0])) == NULL)
    {
      SmallConf::create_mode = cmode;
      return (false);
    }
  ((SmallConf*)got)->Link((SmallConf*)cnf);
  SmallConf::create_mode = cmode;
  return (true);
}

/**
 * @doc
 * @doc-symbol bunny_configuration_link
 * @doc-kind function
 * @doc-module configuration
 * @doc-order 811
 * @doc-since 0
 * @doc-until latest
 * @doc-level expert
 *
 * @doc-lang en
 * @brief Links a configuration node to another one.
 * @param dst Destination node becoming a link.
 * @param ori Original node targeted by the link.
 * @return-success The destination node becomes linked to the origin.
 * @log "configuration"
 *
 * @doc-lang fr
 * @brief Lie un nœud de configuration à un autre.
 * @param dst Destination node becoming a link.
 * @param ori Original node targeted by the link.
 * @return-success Le nœud destination devient lié à l’origine.
 * @log "configuration"
 */
void		bunny_configuration_link(t_bunny_configuration	*dst,
					 t_bunny_configuration	*ori)
{
  SmallConf	*a = (SmallConf*)dst;
  SmallConf	*b = (SmallConf*)ori;

  b->Link(a);
}

